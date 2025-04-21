#include "stm32f4xx_hal.h" // STM32 HAL 라이브러리 헤더 파일 포함

#define BTN_PORT GPIOC                   // 버튼이 연결된 포트 정의
#define BTN_PIN GPIO_PIN_13              // 버튼이 연결된 핀 정의 (PC13)

// GPIO 인터럽트 및 LED 출력 초기화 함수
void gpio_pc13_interrupt_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};      // GPIO 초기화 구조체 선언 및 초기화

    __HAL_RCC_GPIOC_CLK_ENABLE();                // GPIOC 포트 클럭 활성화 (버튼용)

    // 버튼 핀 (PC13) 설정 - 인터럽트 입력 모드
    GPIO_InitStruct.Pin = GPIO_PIN_13;           // 핀 번호 설정
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;  // 상승엣지(버튼 눌릴 때) 인터럽트
    GPIO_InitStruct.Pull = GPIO_NOPULL;          // 풀업/풀다운 없음
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // 속도는 낮음
    HAL_GPIO_Init(BTN_PORT, &GPIO_InitStruct);   // 설정 적용




    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);   // 우선순위 0 (가장 높음)
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);          // EXTI15_10 인터럽트 활성화
}


// EXTI 인터럽트 발생 시 호출되는 콜백 함수
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_13)
	{

	}

}

// EXTI 라인 15~10 범위 인터럽트 핸들러
void EXTI15_10_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);       // HAL이 제공하는 인터럽트 핸들러 호출
}

