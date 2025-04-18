#include "stm32f4xx_hal.h" // STM32F4 시리즈용 HAL 라이브러리 포함

// 외부 파일(main.c 등)에서 정의된 ADC1 핸들 구조체를 참조
extern ADC_HandleTypeDef hadc1;

// DMA를 사용할 경우 필요한 핸들 구조체 선언 (ADC1용 DMA 핸들)
DMA_HandleTypeDef hdma_adc1;

// 내부적으로 사용할 연속 변환 초기화 함수 선언
static void adc_pa0_continous_conv_init(void);

// ===== ADC 일반 함수 =====

// ADC로부터 변환된 데이터를 읽어오는 함수
uint32_t pa0_adc_read(void)
{
    return HAL_ADC_GetValue(&hadc1); // ADC 변환 결과 반환
}

// ADC 초기화 및 변환 시작을 한 번에 수행하는 함수
void adc_init_start(void)
{
    adc_pa0_continous_conv_init(); // 연속 변환 모드로 초기화
    HAL_ADC_Start(&hadc1);         // ADC 변환 시작 (소프트웨어 트리거)
}

// ===== ADC 연속 변환 초기화 =====

// PA0 핀을 아날로그 입력으로 설정하고 연속 변환 모드로 ADC 설정
void adc_pa0_continous_conv_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0}; // GPIO 설정 구조체 초기화
    ADC_ChannelConfTypeDef sConfig = {0};   // ADC 채널 설정 구조체 초기화

    __HAL_RCC_GPIOA_CLK_ENABLE(); // GPIOA 클럭 활성화

    // PA0 핀을 아날로그 입력으로 설정
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); // 설정된 값으로 GPIO 초기화

    __HAL_RCC_ADC1_CLK_ENABLE(); // ADC1 클럭 활성화

    // ADC1 기본 설정
    hadc1.Instance = ADC1;                                  // 사용할 ADC 인스턴스 지정
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;   // ADC 클럭 분주
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;             // 12비트 분해능
    hadc1.Init.ContinuousConvMode = ENABLE;                 // 연속 변환 모드 활성화
    hadc1.Init.DiscontinuousConvMode = DISABLE;             // 분할 변환 비활성화
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE; // 외부 트리거 사용 안 함
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;       // 소프트웨어로 변환 시작
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;             // 변환 결과 오른쪽 정렬
    hadc1.Init.NbrOfConversion = 1;                          // 변환 채널 수 1개
    hadc1.Init.DMAContinuousRequests = DISABLE;             // DMA 요청 비활성화
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;          // 변환 종료 조건: 단일 변환

    HAL_ADC_Init(&hadc1); // ADC 설정 적용

    // 채널 설정: PA0은 ADC_CHANNEL_0
    sConfig.Channel = ADC_CHANNEL_0;
    sConfig.Rank = 1; // 첫 번째 변환 순서
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES; // 샘플링 시간 설정

    HAL_ADC_ConfigChannel(&hadc1, &sConfig); // 채널 설정 적용
}

// ===== 단일 변환 모드 초기화 =====

// PA0을 단일 변환 모드로 설정
void adc_pa0_single_conv_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    ADC_ChannelConfTypeDef sConfig = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();

    // PA0 핀 설정 (아날로그 입력, 풀 없음)
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    __HAL_RCC_ADC1_CLK_ENABLE();

    // 단일 변환용 설정 (ContinuousConvMode 비활성화)
    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;

    HAL_ADC_Init(&hadc1);

    // 채널 설정 (ADC_CHANNEL_0)
    sConfig.Channel = ADC_CHANNEL_0;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;

    HAL_ADC_ConfigChannel(&hadc1, &sConfig);
}

// ===== 인터럽트 방식 초기화 =====

// ADC 변환 완료 시 인터럽트를 발생시키도록 설정
void adc_pa0_interrupt_init(void)
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

    // 연속 변환 + 인터럽트 설정
    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ContinuousConvMode = ENABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;

    HAL_ADC_Init(&hadc1);

    // 채널 설정
    sConfig.Channel = ADC_CHANNEL_0;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;

    HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    // ADC 인터럽트 우선순위 설정 및 활성화
    NVIC_SetPriority(ADC_IRQn, 0);
    NVIC_EnableIRQ(ADC_IRQn);
}

// ===== DMA 방식 초기화 =====

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

// ===== 인터럽트 핸들러 =====

// DMA2 스트림0 인터럽트 핸들러 (ADC1 DMA용)
void DMA2_Stream0_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_adc1); // HAL 라이브러리 기반 처리
}

// ADC 변환 완료 시 호출되는 인터럽트 핸들러
void ADC_IRQHandler(void)
{
    HAL_ADC_IRQHandler(&hadc1); // HAL 기반 ADC 인터럽트 처리
}
