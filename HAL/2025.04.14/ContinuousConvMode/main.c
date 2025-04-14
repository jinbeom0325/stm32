#include <stdio.h>
#include "stm32f4xx_hal.h" // STM32 HAL 라이브러리 헤더 파일 포함
#include "uart.h"           // UART 관련 함수 선언 헤더 파일
#include "adc.h"            // ADC 관련 함수 선언 헤더 파일

uint32_t sensor_value;    // 센서 값을 저장할 변수

// 메인 함수
int main()
{
    HAL_Init();  // HAL 라이브러리 초기화 (STM32의 HAL API 사용을 위한 기본 설정)
    uart_init(); // UART 초기화 (UART 통신을 위한 설정)

    adc_init_start(); // ADC 초기화 (PA0 핀을 통해 아날로그 값을 읽기 위한 초기화)

    while(1) // 무한 루프
    {
        sensor_value = pa0_adc_read(); // ADC 값을 읽어서 sensor_value에 저장 (PA0 핀의 아날로그 센서 값)

        // printf("printf is being used ! \r\n");  // 콘솔로 메시지를 출력

        HAL_Delay(10);  // 10ms 지연 (ADC 값 읽은 후 10ms 대기, ADC 샘플링 속도와 처리 시간을 고려)
    }
}

// Systick 인터럽트 핸들러
void Systick_Handler(void)
{
    HAL_IncTick();  // HAL의 틱 타이머 증가 (타이머 기반의 시간 추적을 위해 필요)
}
