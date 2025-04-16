#include <stdio.h>                        // printf 사용을 위한 표준 입출력 라이브러리
#include "stm32f4xx_hal.h"               // STM32 HAL 드라이버 라이브러리
#include "uart.h"                        // UART 초기화 및 통신 함수 헤더
#include "adc.h"                         // ADC 관련 함수 헤더 (이 코드에서는 사용되지 않음)

#define BTN_PORT GPIOC                   // 버튼이 연결된 포트 정의
#define BTN_PIN GPIO_PIN_13              // 버튼이 연결된 핀 정의 (PC13)
#define LED_PORT GPIOA                   // LED가 연결된 포트 정의
#define LED_PIN GPIO_PIN_5               // LED가 연결된 핀 정의 (PA5)

void gpio_pc13_interrupt_init(void);     // PC13 인터럽트 초기화 함수 선언

// 메인 함수
int main()
{
    HAL_Init();                          // HAL 라이브러리 초기화 (시스템 설정 및 SysTick 설정 등)
    gpio_pc13_interrupt_init();          // 버튼 인터럽트 및 LED 설정 초기화

    while(1) // 무한 루프
    {
        // 메인 루프에서는 아무 동작 없음 (인터럽트 기반 처리)
    }
}

// Systick 인터럽트 핸들러
void Systick_Handler(void)
{
    HAL_IncTick();                       // HAL 내부 타이머 틱 증가 (밀리초 단위 시간 관리용)
}

// GPIO 인터럽트 및 LED 출력 초기화 함수
void gpio_pc13_interrupt_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};      // GPIO 초기화 구조체 선언 및 초기화

    __HAL_RCC_GPIOC_CLK_ENABLE();                // GPIOC 포트 클럭 활성화 (버튼용)
    __HAL_RCC_GPIOA_CLK_ENABLE();                // GPIOA 포트 클럭 활성화 (LED용)

    // 버튼 핀 (PC13) 설정 - 인터럽트 입력 모드
    GPIO_InitStruct.Pin = GPIO_PIN_13;           // 핀 번호 설정
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;  // 상승엣지(버튼 눌릴 때) 인터럽트
    GPIO_InitStruct.Pull = GPIO_NOPULL;          // 풀업/풀다운 없음
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // 속도는 낮음
    HAL_GPIO_Init(BTN_PORT, &GPIO_InitStruct);   // 설정 적용

    // LED 핀 (PA5) 설정 - 일반 출력 모드
    GPIO_InitStruct.Pin = LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  // Push-Pull 출력
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);

    // EXTI 인터럽트 우선순위 설정 및 활성화 (PC13은 EXTI15_10 라인 사용)
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);   // 우선순위 0 (가장 높음)
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);          // EXTI15_10 인터럽트 활성화
}

// EXTI 인터럽트 발생 시 호출되는 콜백 함수
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    // 인터럽트가 발생한 핀이 PC13이면 (안전하게 하려면 조건 추가 가능)
    HAL_GPIO_TogglePin(LED_PORT, LED_PIN);       // LED 상태 토글 (켜짐 ↔ 꺼짐)
    printf("Button pressed ! \n\r");             // UART로 메시지 출력
}

// EXTI 라인 15~10 범위 인터럽트 핸들러
void EXTI15_10_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);       // HAL이 제공하는 인터럽트 핸들러 호출
}
