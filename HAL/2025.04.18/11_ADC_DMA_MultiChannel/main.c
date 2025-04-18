#include <stdio.h>
#include "stm32f4xx_hal.h"  // STM32 HAL 라이브러리 헤더 파일 포함
#include "uart.h"            // UART 관련 함수 선언 헤더 파일
#include "adc.h"             // ADC 관련 함수 선언 헤더 파일

ADC_HandleTypeDef hadc1;     // ADC 핸들러 정의

uint32_t sensor_value[2];    // 센서 값을 저장할 배열 (DMA 전송으로 읽은 값이 저장됨)

// 메인 함수
int main()
{
    HAL_Init();            // HAL 라이브러리 초기화 (STM32의 HAL API 사용을 위한 기본 설정)
    uart_init();           // UART 초기화 (UART 통신을 위한 설정)
    adc_pa0pa4_dma_init();    // PA0 핀을 아날로그 입력으로 설정하고 ADC 초기화 (DMA 사용)

    // DMA를 사용하여 ADC 변환 시작 (sensor_value 배열에 변환된 값 저장)
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)sensor_value, 2);

    while(1)  // 무한 루프 (메인 루프)
    {
    	printf("Sensor 1 data : %d \n\r",(int)sensor_value[0]);
    	printf("Sensor 1 data : %d \n\r",(int)sensor_value[1]);

    }
}



// Systick 인터럽트 핸들러
void Systick_Handler(void)
{
    HAL_IncTick();  // HAL의 틱 타이머 증가 (타이머 기반의 시간 추적을 위해 필요)
}
