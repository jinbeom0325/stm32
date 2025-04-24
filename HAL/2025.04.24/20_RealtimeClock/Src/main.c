#include "stm32f4xx_hal.h" // STM32 HAL 라이브러리 헤더 파일 포함
#include <stdio.h>


#define RTC_ASYNCH_PREDIV	0x7F //127
#define RTC_SYNCH_PREDIV	0xF9 //249

#define BK_FLAG				0x8888

UART_HandleTypeDef huart2; // UART 핸들러 구조체 선언

// 함수 프로토타입
void uart_init(void); // UART 초기화 함수

// 전송할 메시지
char message[20] = "Hello from STM32\r\n";

RTC_HandleTypeDef RtcHandle;

int __io_putchar(int ch)
{
	HAL_UART_Transmit(&huart2,(uint8_t*)&ch,1,1000);
	return ch;
}

uint8_t time[15] = {0};
uint8_t date[15] = {0};


void rtc_init(void);
void rtc_calendar_config(void);
void rtc_calendar_show(uint8_t *showtime, uint8_t *showdate);

// 메인 함수
int main()
{
	HAL_Init(); // HAL 라이브러리 초기화
	uart_init(); // UART 초기화

	__HAL_RTC_RESET_HANDLE_STATE(&RtcHandle);

	rtc_init();

	//Read backup register
	if(HAL_RTCEx_BKUPRead(&RtcHandle, RTC_BKP_DR0) != BK_FLAG)
	{
		rtc_calendar_config();
	}



	while(1) // 무한 루프
	{
		rtc_calendar_show(time,date);
//		HAL_Delay(10);  // 10ms 지연
	}
}

void rtc_init(void)
{
	//Select RTC clock
	RCC_OscInitTypeDef			RCC_OscInitStruct;
	RCC_PeriphCLKInitTypeDef	PeriphClkInitStruct;

	//Turn of LSE and turn on LSI
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE;
	RCC_OscInitStruct.LSEState = RCC_LSE_OFF;
	RCC_OscInitStruct.LSIState = RCC_LSI_ON;

	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	//set RTC clock src to LSI
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
	PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;

	HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

	//Enable RTC clock
	__HAL_RCC_RTC_ENABLE();

	//configure calendar
	RtcHandle.Instance = RTC;
	RtcHandle.Init.HourFormat = RTC_HOURFORMAT_24;
	RtcHandle.Init.AsynchPrediv = RTC_ASYNCH_PREDIV;
	RtcHandle.Init.SynchPrediv = RTC_SYNCH_PREDIV;
	RtcHandle.Init.OutPut = RTC_OUTPUT_DISABLE;

	HAL_RTC_Init(&RtcHandle);
}


void rtc_calendar_config(void)
{
	RTC_DateTypeDef sdatestructure;
	RTC_TimeTypeDef stimestructure;

	//set Date: Sunday JULY 14th 2019
	sdatestructure.Year = 0x19;
	sdatestructure.Month = RTC_MONTH_JULY;
	sdatestructure.Date = 0x14;
	sdatestructure.WeekDay = RTC_WEEKDAY_SUNDAY;

	HAL_RTC_SetDate(&RtcHandle, &sdatestructure,RTC_FORMAT_BCD);

	//set Time: 03:00:00
	stimestructure.Hours = 0x03;
	stimestructure.Minutes = 0x00;
	stimestructure.Seconds = 0x00;
	stimestructure.TimeFormat = RTC_HOURFORMAT12_AM;
	stimestructure.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	stimestructure.StoreOperation = RTC_STOREOPERATION_RESET;

	HAL_RTC_SetTime(&RtcHandle, &stimestructure,RTC_FORMAT_BCD);

	//Write to Backup Register
	HAL_RTCEx_BKUPWrite(&RtcHandle, RTC_BKP_DR0, BK_FLAG);

}

void rtc_calendar_show(uint8_t *showtime, uint8_t *showdate)
{
	RTC_DateTypeDef sdatestructureget;
	RTC_TimeTypeDef stimestructureget;

	HAL_RTC_GetTime(&RtcHandle, &stimestructureget, RTC_FORMAT_BIN);

	HAL_RTC_GetDate(&RtcHandle, &sdatestructureget, RTC_FORMAT_BIN);

	/* Display time Format: hh:mm:ss */
	sprintf((char*)showtime,"%02d:%02d:%02d",stimestructureget.Hours, stimestructureget.Minutes, stimestructureget.Seconds);

	/* Display date Format: mm-dd-yy */
	sprintf((char*)showdate,"%02d-%02d-%02d",sdatestructureget.Month, sdatestructureget.Date, 2000 + sdatestructureget.Year);

	printf(" Time : %02d:%02d:%02d\n\r",stimestructureget.Hours, stimestructureget.Minutes, stimestructureget.Seconds);

	printf(" Date : %02d-%02d-%02d\n\r",sdatestructureget.Month, sdatestructureget.Date, 2000 + sdatestructureget.Year);

}

// Systick 인터럽트 핸들러
void SysTick_Handler(void)
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

