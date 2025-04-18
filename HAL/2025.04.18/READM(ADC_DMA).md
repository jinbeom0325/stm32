### 들어가기전 정리
- EXTI는 인터럽트를 발생시키는 역할 

- NVIC는 인터럽트 컨트롤러 즉 CPU가 처리하게 허용해주는 것
  
위 둘은 꼭 있어야 한다. 

- DMA는 직접 메모리 접근 CPU를 거치지 않고 주변장치(ADC) <-> 메모리 사이 데이터를 주고 받는 것 

- DMA는 NVIC없어도 동작은 가능하지만 다른 작업 등을 하려면 DMA완료 시점에 NVIC로 인터럽트를 받아야 한다. 

### 코드 흐름 
단계 | 함수 | 설명
--|--|--
1 | HAL_Init() | HAL 시스템 초기화
2 | uart_init() | UART 초기화
3 | adc_pa0_dma_init() | ADC + DMA 설정
4 | HAL_ADC_Start_DMA() | DMA 기반 ADC 시작
5 | while(1) | 센서값 UART 실시간 출력 (DMA가 자동으로 값 채워줌)

ADC+DMA가 자동으로 센서 값을 갱신 ,메인에 while문에서 값을 UART로 내보내는 구조 


```c
// DMA를 사용한 ADC 변환 설정
void adc_pa0_dma_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    ADC_ChannelConfTypeDef sConfig = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();

    // PA0 핀 설정
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    __HAL_RCC_ADC1_CLK_ENABLE();

    // 연속 변환 + DMA 설정
    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ContinuousConvMode = ENABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DMAContinuousRequests = ENABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;

    HAL_ADC_Init(&hadc1);

    // 채널 설정
    sConfig.Channel = ADC_CHANNEL_0;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;

    HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    __HAL_RCC_DMA2_CLK_ENABLE(); // DMA2 클럭 활성화

    // DMA 인터럽트 우선순위 및 활성화
    HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

    // DMA 설정
    hdma_adc1.Instance = DMA2_Stream0;
    hdma_adc1.Init.Channel = DMA_CHANNEL_0;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;             // ADC → 메모리
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;                 // 주변기기 주소 고정
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;                     // 메모리 주소 증가
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD; // 16비트 정렬
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_adc1.Init.Mode = DMA_CIRCULAR;                          // 순환 모드
    hdma_adc1.Init.Priority = DMA_PRIORITY_LOW;                  // 낮은 우선순위
    hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

    HAL_DMA_Init(&hdma_adc1); // DMA 초기화

    // DMA 핸들을 ADC 핸들과 연결
    __HAL_LINKDMA(&hadc1, DMA_Handle, hdma_adc1);
}
```
### 단일채널 멀티채널 차이
항목 | 기존 코드 (adc_pa0_dma_init()) | 멀티 채널 코드 (adc_pa0pa4_dma_init())
--|--|--
사용 핀 | PA0만 사용 | PA0, PA4 사용
ADC 변환 수 (NbrOfConversion) | 1 | 2
ScanConvMode | DISABLE | ENABLE
ADC 채널 설정 | 1번 채널만 설정 (CH0) | 2번 채널 설정 (CH0, CH4 순차적으로)
데이터 저장 순서 | 하나의 값만 저장 | 두 개의 값이 순서대로 저장 (CH0 → CH4)
DMA 전송 대상 메모리 배열 | uint16_t data[1]; | uint16_t data[2]; (채널 수만큼 배열 필요)
