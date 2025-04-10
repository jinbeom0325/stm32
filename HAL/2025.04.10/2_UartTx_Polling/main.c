#include "stm32f4xx_hal.h" // STM32 HAL 라이브러리 헤더 파일 포함

UART_HandleTypeDef huart2; // UART 핸들러 구조체 선언

// 함수 프로토타입
void uart_init(void); // UART 초기화 함수

// 전송할 메시지
char message[20] = "Hello from STM32\r\n";

// 메인 함수
int main()
{
	HAL_Init(); // HAL 라이브러리 초기화
	uart_init(); // UART 초기화

	while(1) // 무한 루프
	{
		HAL_UART_Transmit(&huart2, (uint8_t *)message, 20, 100); // UART를 통해 메시지 전송
		HAL_Delay(10);  // 10ms 지연
	}
}

// Systick 인터럽트 핸들러
void Systick_Handler(void)
{
	HAL_IncTick(); // HAL의 틱 타이머 증가
}

// UART 초기화 함수
void uart_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0}; // GPIO 초기화 구조체 선언

	// UART 핀 클럭 활성화
	__HAL_RCC_GPIOA_CLK_ENABLE(); // GPIOA 포트 클럭 활성화

	// UART 모듈 클럭 활성화
	__HAL_RCC_USART2_CLK_ENABLE(); // USART2 클럭 활성화

	// UART 핀 설정 (PA2: TX, PA3: RX)
	GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3; // PA2와 PA3 핀 설정
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; // UART 통신을 위한 AF 모드 설정
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2; // USART2의 대체 기능 핀 설정
	GPIO_InitStruct.Pull = GPIO_NOPULL; // 풀업, 풀다운 저항 사용 안 함
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH; // 핀 속도 설정

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); // GPIOA 포트를 위 설정으로 초기화

	// UART 모듈 설정
	huart2.Instance = USART2; // UART2 인스턴스 지정
	huart2.Init.BaudRate = 115200; // UART 통신 속도 설정 (115200bps)
	huart2.Init.WordLength = UART_WORDLENGTH_8B; // 데이터 길이 설정 (8비트)
	huart2.Init.StopBits = UART_STOPBITS_1; // 스톱 비트 설정 (1비트)
	huart2.Init.Parity = UART_PARITY_NONE; // 패리티 비트 설정 (없음)
	huart2.Init.Mode = UART_MODE_TX; // UART 모드 설정 (송신 모드)
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE; // 하드웨어 흐름 제어 비활성화
	huart2.Init.OverSampling = UART_OVERSAMPLING_16; // 오버샘플링 설정 (16배)

	HAL_UART_Init(&huart2); // UART 설정 초기화
}
