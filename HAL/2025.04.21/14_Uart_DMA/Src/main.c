#include "stm32f4xx_hal.h" // STM32 HAL 라이브러리 헤더 파일 포함

UART_HandleTypeDef huart1; // UART1 핸들러 구조체 선언

DMA_HandleTypeDef hdma_usart1_rx; // UART1 수신용 DMA 핸들 구조체
DMA_HandleTypeDef hdma_usart1_tx; // UART1 송신용 DMA 핸들 구조체

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

    // 인터럽트 방식으로 송수신 시작 (DMA 이용)
    HAL_UART_Transmit_DMA(&huart1, tx_buffer, 10); // 비동기 송신 시작
    HAL_UART_Receive_DMA(&huart1, rx_buffer, 10);  // 비동기 수신 시작

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

    __HAL_RCC_GPIOA_CLK_ENABLE();     // GPIOA 클럭 활성화 (PA9, PA10 사용)
    __HAL_RCC_USART1_CLK_ENABLE();    // USART1 클럭 활성화
    __HAL_RCC_DMA2_CLK_ENABLE();      // DMA2 클럭 활성화

    // PA9 (TX), PA10 (RX) 핀을 UART 기능으로 설정
    GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;            // 대체 기능 모드, Push-Pull 출력
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;       // USART1의 대체 기능 번호
    GPIO_InitStruct.Pull = GPIO_NOPULL;                // 풀업/풀다운 없음
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH; // 고속 동작 설정
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);            // GPIOA 포트 초기화

    // UART 설정
    huart1.Instance = USART1;                         // UART1 인스턴스 선택
    huart1.Init.BaudRate = 115200;                    // 보레이트 설정
    huart1.Init.WordLength = UART_WORDLENGTH_8B;      // 데이터 비트 수 설정 (8비트)
    huart1.Init.StopBits = UART_STOPBITS_1;           // 스톱 비트 설정 (1비트)
    huart1.Init.Parity = UART_PARITY_NONE;            // 패리티 없음
    huart1.Init.Mode = UART_MODE_TX_RX;               // 송수신 모드
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;      // 하드웨어 흐름 제어 없음
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;  // 오버샘플링 설정
    HAL_UART_Init(&huart1);                           // UART 초기화

    // USART1 RX용 DMA 설정 (DMA2_Stream2, Channel 4)
    hdma_usart1_rx.Instance = DMA2_Stream2;                          // DMA 스트림 지정
    hdma_usart1_rx.Init.Channel = DMA_CHANNEL_4;                    // USART1 RX는 Channel 4
    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;           // 주변장치 → 메모리
    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;               // 주변장치 주소 고정
    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;                   // 메모리 주소 자동 증가
    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;  // 주변장치 데이터 정렬: 바이트
    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;     // 메모리 데이터 정렬: 바이트
    hdma_usart1_rx.Init.Mode = DMA_NORMAL;                          // 일반 모드
    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;                // 우선순위: 낮음
    hdma_usart1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;            // FIFO 모드 비활성화
    HAL_DMA_Init(&hdma_usart1_rx);                                  // DMA 초기화

    huart1.hdmarx = &hdma_usart1_rx; // UART에 DMA RX 연결

    // USART1 TX용 DMA 설정 (DMA2_Stream7, Channel 4)
    hdma_usart1_tx.Instance = DMA2_Stream7;                          // DMA 스트림 지정
    hdma_usart1_tx.Init.Channel = DMA_CHANNEL_4;                    // USART1 TX는 Channel 4
    hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;           // 메모리 → 주변장치
    hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;               // 주변장치 주소 고정
    hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;                   // 메모리 주소 자동 증가
    hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;  // 주변장치 데이터 정렬: 바이트
    hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;     // 메모리 데이터 정렬: 바이트
    hdma_usart1_tx.Init.Mode = DMA_NORMAL;                          // 일반 모드
    hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;                // 우선순위: 낮음
    hdma_usart1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;            // FIFO 모드 비활성화
    HAL_DMA_Init(&hdma_usart1_tx);                                  // DMA 초기화

    huart1.hdmatx = &hdma_usart1_tx; // UART에 DMA TX 연결

    // DMA 인터럽트 우선순위 설정 및 활성화
    HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);  // RX DMA 인터럽트 우선순위 설정
    HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);          // RX DMA 인터럽트 활성화

    HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 0, 0);  // TX DMA 인터럽트 우선순위 설정
    HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);          // TX DMA 인터럽트 활성화
}

// DMA2 스트림 2 인터럽트 핸들러 (USART1_RX)
void DMA2_Stream2_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_usart1_rx); // HAL DMA RX 인터럽트 처리 함수 호출
}

// DMA2 스트림 7 인터럽트 핸들러 (USART1_TX)
void DMA2_Stream7_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_usart1_tx); // HAL DMA TX 인터럽트 처리 함수 호출
}
