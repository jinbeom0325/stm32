#include <stdio.h>                        // printf 사용을 위한 표준 입출력 라이브러리
#include "stm32f4xx_hal.h"               // STM32 HAL 드라이버 라이브러리 (핵심 HAL 기능 포함)
#include "uart.h"                        // UART 초기화 및 통신 함수 헤더
#include "adc.h"                         // ADC 관련 함수 헤더 (이 코드에서는 사용되지 않음)
#include "tim.h"                         // 타이머 관련 초기화 함수 헤더

// 메인 함수
int main()
{
    HAL_Init();                          // HAL 라이브러리 초기화 (시스템 클럭, SysTick 설정 등 내부 설정 수행)
    tim_timebase_init();                // 사용자 정의 타이머 초기화 함수 호출 (타이머를 주기적으로 동작하도록 설정)
    uart_init();                         // UART 초기화 함수 호출 (통신을 위한 UART 설정)

    while(1) // 무한 루프
    {
        // 메인 루프에서는 아무 동작 없음 (인터럽트 기반 처리이므로 기다리기만 함)
    }
}

// 타이머 주기 인터럽트 콜백 함수 (타이머가 설정된 주기마다 자동 호출됨)
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    printf("A second just elapsed ! \n\r");  // 1초마다 메시지를 UART를 통해 출력
}

// Systick 인터럽트 핸들러 (기본적으로 HAL 내부 타이머 관리용)
void Systick_Handler(void)
{
    HAL_IncTick();                       // HAL 내부의 시스템 시간(Tick)을 증가시켜 시간 함수 작동 (밀리초 단위)
}
