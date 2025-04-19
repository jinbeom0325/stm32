#include "stm32f4xx_hal.h" // STM32 HAL 라이브러리 헤더 파일 포함

UART_HandleTypeDef huart1; // UART1 핸들러 구조체 선언
UART_HandleTypeDef huart2; // UART2 핸들러 구조체 선언

// 함수 프로토타입 선언
void uart1_init(void); // UART1 초기화 함수
void uart2_init(void); // UART2 초기화 함수

// 송수신 버퍼 및 카운터 변수 선언
uint8_t tx_buffer1[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; // UART1 송신 버퍼
uint8_t rx_buffer1[10];                                            // UART1 수신 버퍼

uint8_t tx_buffer2[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; // UART2 송신 버퍼
uint8_t rx_buffer2[10];                                            // UART2 수신 버퍼

uint32_t rx_counter1 = 0; // UART1 수신 완료 횟수 카운터
uint32_t tx_counter1 = 0; // UART1 송신 완료 횟수 카운터

uint32_t rx_counter2 = 0; // UART2 수신 완료 횟수 카운터
uint32_t tx_counter2 = 0; // UART2 송신 완료 횟수 카운터

// 송신 완료 콜백 함수 (인터럽트 송신 완료 시 자동 호출)
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        tx_counter1++; // UART1 송신 완료 횟수 증가
    }

    if (huart->Instance == USART2)
    {
        tx_counter2++; // UART2 송신 완료 횟수 증가
    }
}

// 수신 완료 콜백 함수 (인터럽트 수신 완료 시 자동 호출)
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        rx_counter1++; // UART1 수신 완료 횟수 증가
    }

    if (huart->Instance == USART2)
    {
        rx_counter2++; // UART2 수신 완료 횟수 증가
    }
}

// 메인 함수
int main()
{
    HAL_Init();      // HAL 라이브러리 초기화
    uart1_init();    // UART1 초기화
    uart2_init();    // UART2 초기화

    // 인터럽트 방식 비동기 송수신 시작
    HAL_UART_Transmit_IT(&huart1, tx_buffer1, 10); // UART1 데이터 비동기 송신
    HAL_UART_Receive_IT(&huart1, rx_buffer1, 10);  // UART1 데이터 비동기 수신

    HAL_UART_Transmit_IT(&huart2, tx_buffer2, 10); // UART2 데이터 비동기 송신
    HAL_UART_Receive_IT(&huart2, rx_buffer2, 10);  // UART2 데이터 비동기 수신

    while (1) // 무한 루프 - 주요 동작은 인터럽트로 처리됨
    {
        // 실시간 동작은 콜백 내부에서 수행되며, 메인 루프는 유휴 상태
    }
}

// SysTick 인터럽트 핸들러 (HAL의 시간 기반 함수용 타이머 인터럽트)
void SysTick_Handler(void)
{
    HAL_IncTick(); // HAL 내부 Tick 증가 (1ms 단위 시간 관리)
}

// UART1 초기화 함수
void uart1_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0}; // GPIO 설정용 구조체 초기화

    __HAL_RCC_GPIOA_CLK_ENABLE();    // GPIOA 클럭 활성화 (PA9, PA10 사용)
    __HAL_RCC_USART1_CLK_ENABLE();   // USART1 클럭 활성화

    // PA9 (TX), PA10 (RX) 핀 설정: 대체 기능, Push-Pull 출력, 고속, 풀업/풀다운 없음
    GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1; // UART1 대체 기능 설정
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);      // 설정 적용

    // UART1 통신 설정
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;                 // 통신 속도: 115200bps
    huart1.Init.WordLength = UART_WORDLENGTH_8B;   // 데이터 비트: 8비트
    huart1.Init.StopBits = UART_STOPBITS_1;        // 스톱 비트: 1비트
    huart1.Init.Parity = UART_PARITY_NONE;         // 패리티 없음
    huart1.Init.Mode = UART_MODE_TX_RX;            // 송신 + 수신 모드
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;   // 하드웨어 흐름 제어 없음
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&huart1);                        // UART1 초기화

    // UART1 인터럽트 설정 (우선순위 설정 및 활성화)
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
}

// UART2 초기화 함수
void uart2_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0}; // GPIO 설정용 구조체 초기화

    __HAL_RCC_GPIOA_CLK_ENABLE();    // GPIOA 클럭 활성화 (PA2, PA3 사용)
    __HAL_RCC_USART2_CLK_ENABLE();   // USART2 클럭 활성화

    // PA2 (TX), PA3 (RX) 핀 설정: 대체 기능, Push-Pull 출력, 고속, 풀업/풀다운 없음
    GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2; // UART2 대체 기능 설정
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);      // 설정 적용

    // UART2 통신 설정
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;                 // 통신 속도: 115200bps
    huart2.Init.WordLength = UART_WORDLENGTH_8B;   // 데이터 비트: 8비트
    huart2.Init.StopBits = UART_STOPBITS_1;        // 스톱 비트: 1비트
    huart2.Init.Parity = UART_PARITY_NONE;         // 패리티 없음
    huart2.Init.Mode = UART_MODE_TX_RX;            // 송신 + 수신 모드
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;   // 하드웨어 흐름 제어 없음
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&huart2);                        // UART2 초기화

    // UART2 인터럽트 설정 (우선순위 설정 및 활성화)
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
}

// USART1 인터럽트 핸들러 (HAL 내부 인터럽트 처리 호출)
void USART1_IRQHandler(void)
{
    HAL_UART_IRQHandler(&huart1); // UART1 인터럽트 처리
}

// USART2 인터럽트 핸들러 (HAL 내부 인터럽트 처리 호출)
void USART2_IRQHandler(void)
{
    HAL_UART_IRQHandler(&huart2); // UART2 인터럽트 처리
}
