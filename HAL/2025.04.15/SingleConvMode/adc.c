#include "stm32f4xx_hal.h" // STM32 HAL 라이브러리 헤더 파일 포함

 extern ADC_HandleTypeDef hadc1; // ADC1 핸들러 전역변수 사용

// PA0 핀을 아날로그 입력으로 설정하고 ADC 연속 변환 모드로 초기화하는 함수 선언
static void adc_pa0_continous_conv_init(void);

// PA0에서 ADC 값을 읽어오는 함수
uint32_t pa0_adc_read(void)
{
    return HAL_ADC_GetValue(&hadc1); // ADC1의 변환 값을 읽어 반환
}

// ADC 초기화 및 시작 함수
void adc_init_start(void)
{
    adc_pa0_continous_conv_init(); // PA0 핀을 아날로그 입력으로 설정하고 ADC를 초기화
    HAL_ADC_Start(&hadc1); // ADC 변환을 시작
}

// PA0 핀을 아날로그 입력으로 설정하고 ADC 모듈을 연속 변환 모드로 초기화하는 함수
void adc_pa0_continous_conv_init(void)
{
    // GPIO 설정 구조체와 ADC 채널 설정 구조체 초기화
    GPIO_InitTypeDef GPIO_InitStruct = {0};  // GPIO 설정 초기화
    ADC_ChannelConfTypeDef sConfig = {0};    // ADC 채널 설정 초기화

    // GPIOA 클럭 활성화
    __HAL_RCC_GPIOA_CLK_ENABLE(); // GPIOA 포트 클럭 활성화

    // PA0 핀을 아날로그 모드로 설정
    GPIO_InitStruct.Pin = GPIO_PIN_0; // PA0 핀
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; // 아날로그 모드로 설정
    GPIO_InitStruct.Pull = GPIO_NOPULL; // 풀업/풀다운 설정 없음
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); // 설정된 GPIO를 초기화

    // ADC1 클럭 활성화
    __HAL_RCC_ADC1_CLK_ENABLE(); // ADC1 클럭 활성화

    // ADC1 초기화
    hadc1.Instance = ADC1; // ADC1 인스턴스를 설정
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2; // ADC 클럭 분주기 설정 (PCLK/2)
    hadc1.Init.Resolution = ADC_RESOLUTION_12B; // ADC 해상도 12비트로 설정
    hadc1.Init.ContinuousConvMode = ENABLE; // 연속 변환 모드 활성화
    hadc1.Init.DiscontinuousConvMode = DISABLE; // 불연속 변환 모드 비활성화
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE; // 외부 트리거 없음
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START; // 소프트웨어 시작 모드
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT; // 데이터 정렬: 오른쪽 정렬
    hadc1.Init.NbrOfConversion = 1; // 한 채널만 변환
    hadc1.Init.DMAContinuousRequests = DISABLE; // DMA 연속 요청 비활성화
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV; // 단일 변환 완료 시 종료

    // ADC1 초기화 함수 호출
    HAL_ADC_Init(&hadc1); // ADC1 초기화

    // ADC 채널 0 설정 (PA0 핀)
    sConfig.Channel = ADC_CHANNEL_0; // ADC 채널 0 설정 (PA0 핀)
    sConfig.Rank = 1; // 첫 번째 순위에 채널을 설정
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES; // 샘플링 시간 설정 (480 사이클)

    // ADC 채널 설정
    HAL_ADC_ConfigChannel(&hadc1, &sConfig); // 채널 설정 함수 호출
}

// PA0 핀을 아날로그 입력으로 설정하고 ADC 모듈을 연속 변환 모드로 초기화하는 함수
void adc_pa0_single_conv_init(void)
{
    // GPIO 설정 구조체와 ADC 채널 설정 구조체 초기화
    GPIO_InitTypeDef GPIO_InitStruct = {0};  // GPIO 설정 초기화
    ADC_ChannelConfTypeDef sConfig = {0};    // ADC 채널 설정 초기화

    // GPIOA 클럭 활성화
    __HAL_RCC_GPIOA_CLK_ENABLE(); // GPIOA 포트 클럭 활성화

    // PA0 핀을 아날로그 모드로 설정
    GPIO_InitStruct.Pin = GPIO_PIN_0; // PA0 핀
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; // 아날로그 모드로 설정
    GPIO_InitStruct.Pull = GPIO_NOPULL; // 풀업/풀다운 설정 없음
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); // 설정된 GPIO를 초기화

    // ADC1 클럭 활성화
    __HAL_RCC_ADC1_CLK_ENABLE(); // ADC1 클럭 활성화

    // ADC1 초기화
    hadc1.Instance = ADC1; // ADC1 인스턴스를 설정
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2; // ADC 클럭 분주기 설정 (PCLK/2)
    hadc1.Init.Resolution = ADC_RESOLUTION_12B; // ADC 해상도 12비트로 설정
    hadc1.Init.ContinuousConvMode = DISABLE; // 연속 변환 모드 활성화
    hadc1.Init.DiscontinuousConvMode = DISABLE; // 불연속 변환 모드 비활성화
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE; // 외부 트리거 없음
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START; // 소프트웨어 시작 모드
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT; // 데이터 정렬: 오른쪽 정렬
    hadc1.Init.NbrOfConversion = 1; // 한 채널만 변환
    hadc1.Init.DMAContinuousRequests = DISABLE; // DMA 연속 요청 비활성화
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV; // 단일 변환 완료 시 종료

    // ADC1 초기화 함수 호출
    HAL_ADC_Init(&hadc1); // ADC1 초기화

    // ADC 채널 0 설정 (PA0 핀)
    sConfig.Channel = ADC_CHANNEL_0; // ADC 채널 0 설정 (PA0 핀)
    sConfig.Rank = 1; // 첫 번째 순위에 채널을 설정
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES; // 샘플링 시간 설정 (480 사이클)

    // ADC 채널 설정
    HAL_ADC_ConfigChannel(&hadc1, &sConfig); // 채널 설정 함수 호출
}
