#include "stm32f4xx_hal.h" // HAL 라이브러리 헤더파일 포함

// 핀 매핑 정의
#define BTN_PORT GPIOC        // 버튼 포트 : GPIOC
#define BTN_PIN GPIO_PIN_13   // 버튼 핀 : PC13
#define LED_PORT GPIOA        // LED 포트 : GPIOA
#define LED_PIN GPIO_PIN_5    // LED 핀 : PA5

// PC13 : User 버튼 (검정 버튼)
// PA5  : LED 핀 (보드에 달린 초록색 LED)

// 함수 프로토타입 선언
void pc13_btn_init(void);     // 버튼 초기화 함수
void pa5_led_init(void);      // LED 초기화 함수

uint8_t buttonStatus;         // 버튼 상태 저장 변수 (0 or 1)


int main()
{
	HAL_Init();               // HAL 라이브러리 초기화 (타이머, 인터럽트 등 내부 세팅)
	pc13_btn_init();         // 버튼 핀 초기화
	pa5_led_init();          // LED 핀 초기화


	while(1) // 무한 루프
	{
		// PC13 핀 상태 읽기
		buttonStatus = HAL_GPIO_ReadPin(BTN_PORT, BTN_PIN);

		// 읽어온 상태를 LED에 출력
		// 버튼 안누름(1) -> LED ON
		// 버튼 누름(0) -> LED OFF
		HAL_GPIO_WritePin(LED_PORT, LED_PIN, buttonStatus);
	}
}


// PC13 버튼 입력 초기화 함수
void pc13_btn_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};  // 구조체 초기화

	__HAL_RCC_GPIOC_CLK_ENABLE();            // GPIOC 클럭 활성화 (안하면 GPIO 동작 안함)

	GPIO_InitStruct.Pin = BTN_PIN;           // 설정할 핀 : PC13
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;  // 입력 모드 설정
	GPIO_InitStruct.Pull = GPIO_NOPULL;      // 풀업, 풀다운 없음 (외부 회로에 따라 설정)
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // 핀 속도 (입력은 크게 의미 없음)

	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);  // 설정 적용
}


// PA5 LED 출력 초기화 함수
void pa5_led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};  // 구조체 초기화

	__HAL_RCC_GPIOA_CLK_ENABLE();            // GPIOA 클럭 활성화

	GPIO_InitStruct.Pin = LED_PIN;           // 설정할 핀 : PA5
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // Push-Pull 출력 모드
	GPIO_InitStruct.Pull = GPIO_NOPULL;         // 풀업, 풀다운 없음
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // 출력 속도 낮음

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);  // 설정 적용
}


// SysTick 인터럽트 핸들러 (타이머 tick 증가용)
void Systick_Handler(void)
{
	HAL_IncTick(); // HAL 타이머 tick 증가
}
