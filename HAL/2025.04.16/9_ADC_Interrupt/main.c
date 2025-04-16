#include <stdio.h>
#include "stm32f4xx_hal.h" // STM32 HAL 라이브러리 헤더 파일 포함
#include "uart.h"           // UART 관련 함수 선언 헤더 파일
#include "adc.h"            // ADC 관련 함수 선언 헤더 파일

ADC_HandleTypeDef hadc1;

uint32_t sensor_value;    // 센서 값을 저장할 변수

// 메인 함수
int main()
{
    HAL_Init();  // HAL 라이브러리 초기화 (STM32의 HAL API 사용을 위한 기본 설정)
    uart_init(); // UART 초기화 (UART 통신을 위한 설정)
    adc_pa0_interrupt_init();

	HAL_ADC_Start(&hadc1);

    while(1) // 무한 루프
    {
        printf("The sensor value : %d	\n\r",(int)sensor_value);  // 콘솔로 메시지를 출력

    }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	//do something

	sensor_value = pa0_adc_read(); // ADC 값을 읽어서 sensor_value에 저장 (PA0 핀의 아날로그 센서 값)
	HAL_ADC_Start_IT(&hadc1);
}

//// Systick 인터럽트 핸들러
//void Systick_Handler(void)
//{
//    HAL_IncTick();  // HAL의 틱 타이머 증가 (타이머 기반의 시간 추적을 위해 필요)
//}
