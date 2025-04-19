#include "stm32f4xx_hal.h" // STM32 HAL 라이브러리 헤더 파일 포함

UART_HandleTypeDef huart1; // UART1 핸들러 구조체 선언

// 함수 프로토타입
void uart_init(void); // UART 초기화 함수

// 송수신 버퍼 및 카운터 변수 선언
uint8_t tx_buffer[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; // 송신 데이터
uint8_t rx_buffer[10];                                            // 수신 데이터 저장 버퍼

uint32_t rx_counter = 0; // 수신 완료 횟수 카운터
uint32_t tx_counter = 0; // 송신 완료 횟수 카운터

// 송신 완료 콜백 함수 (인터럽트 방식 사용 시 호출됨)
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    tx_counter++; // 송신 완료 횟수 증가
}

// 수신 완료 콜백 함수 (인터럽트 방식 사용 시 호출됨)
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    rx_counter++; // 수신 완료 횟수 증가
}

// 메인 함수
int main()
{
    HAL_Init();      // HAL 라이브러리 초기화
    uart_init();     // UART1 초기화

    // 인터럽트 방식으로 송수신 시작
    HAL_UART_Transmit_IT(&huart1, tx_buffer, 10); // 비동기 송신 시작
    HAL_UART_Receive_IT(&huart1, rx_buffer, 10);  // 비동기 수신 시작

    while (1) // 무한 루프 (메인 로직 없음, 인터럽트로 처리)
    {
    }
}

// SysTick 인터럽트 핸들러 (HAL 시간 관리용)
void SysTick_Handler(void)
{
    HAL_IncTick(); // HAL 내부 Tick 증가 (시간 관리용)
}

// UART1 초기화 함수
void uart_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0}; // GPIO 설정용 구조체

    // GPIOA 클럭 활성화 (PA9, PA10 사용)
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // USART1 클럭 활성화
    __HAL_RCC_USART1_CLK_ENABLE();

    // PA9 (TX), PA10 (RX) 핀을 UART 기능으로 설정
    GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;            // 대체 기능 모드, Push-Pull 출력
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;       // USART1의 대체 기능 번호
    GPIO_InitStruct.Pull = GPIO_NOPULL;                // 풀업/풀다운 없음
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH; // 고속 동작 설정
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);            // GPIOA 포트 초기화

    // UART 설정
    huart1.Instance = USART1;                       // UART1 사용
    huart1.Init.BaudRate = 115200;                  // 통신 속도: 115200 bps
    huart1.Init.WordLength = UART_WORDLENGTH_8B;    // 데이터 비트: 8비트
    huart1.Init.StopBits = UART_STOPBITS_1;         // 스톱 비트: 1비트
    huart1.Init.Parity = UART_PARITY_NONE;          // 패리티 없음
    huart1.Init.Mode = UART_MODE_TX_RX;             // 송신 + 수신 모드
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;    // 하드웨어 흐름 제어 없음
    huart1.Init.OverSampling = UART_OVERSAMPLING_16; // 오버샘플링 16배
    HAL_UART_Init(&huart1);                         // HAL을 통한 UART 초기화

    // USART1 인터럽트 우선순위 설정 및 활성화
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
}

// USART1 인터럽트 핸들러 (수신/송신 인터럽트 처리)
void USART1_IRQHandler(void)
{
    HAL_UART_IRQHandler(&huart1); // HAL 내부에서 인터럽트 처리
}
