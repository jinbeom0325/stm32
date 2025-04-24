#include "stm32f4xx_hal.h" // STM32F4 시리즈용 HAL 라이브러리 헤더 파일
#include <stdio.h>         // printf 등 표준 입출력 함수 사용

// RTC 프리스케일러 값 설정 (RTC 클럭을 1Hz로 만들기 위함)
#define RTC_ASYNCH_PREDIV  0x7F // 비동기 프리스케일러 (127)
#define RTC_SYNCH_PREDIV   0xF9 // 동기 프리스케일러 (249)

// RTC가 초기화되었는지 확인하기 위한 백업 레지스터 플래그 값
#define BK_FLAG            0x8888

UART_HandleTypeDef huart2;       // UART2 핸들 구조체 선언
RTC_HandleTypeDef RtcHandle;     // RTC 핸들 구조체 선언

uint8_t time[15] = {0}; // 시간을 저장할 문자열 버퍼
uint8_t date[15] = {0}; // 날짜를 저장할 문자열 버퍼

// 함수 원형 선언
void uart_init(void);                     // UART2 초기화 함수
void rtc_init(void);                      // RTC 클럭 및 설정 초기화 함수
void rtc_calendar_config(void);           // 날짜/시간 초기 설정 함수
void rtc_calendar_show(uint8_t*, uint8_t*); // 현재 날짜/시간 읽어오기 함수

// printf 함수에서 사용하는 출력 함수 정의
int __io_putchar(int ch)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, 1000); // UART2로 한 문자 전송
	return ch;
}

// 메인 함수
int main()
{
	HAL_Init();             // HAL 라이브러리 초기화 (SysTick 포함)
	uart_init();            // UART2 초기화 (PA2: TX, PA3: RX)

	__HAL_RTC_RESET_HANDLE_STATE(&RtcHandle); // RTC 핸들의 내부 상태 초기화

	rtc_init();             // RTC 설정 및 클럭 초기화

	// RTC가 초기화되어 있는지 확인 (백업 레지스터 값 확인)
	if (HAL_RTCEx_BKUPRead(&RtcHandle, RTC_BKP_DR0) != BK_FLAG)
	{
		rtc_calendar_config(); // 초기화되지 않은 경우 날짜/시간 설정
	}

	while (1) // 무한 루프
	{
		rtc_calendar_show(time, date); // 날짜와 시간 읽고 UART로 출력
//		HAL_Delay(10);               // 딜레이 추가 가능
	}
}

// RTC 설정 함수
void rtc_init(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};         // 오실레이터 설정 구조체
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0}; // 주변장치 클럭 설정 구조체

	// 오실레이터 종류 설정: LSI 사용, LSE 비활성화
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE;
	RCC_OscInitStruct.LSEState = RCC_LSE_OFF; // 외부 32.768kHz 클럭 비활성화
	RCC_OscInitStruct.LSIState = RCC_LSI_ON;  // 내부 32kHz 클럭 활성화
	HAL_RCC_OscConfig(&RCC_OscInitStruct);    // 설정 적용

	// RTC 클럭 소스를 LSI로 선택
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC; // RTC 클럭 선택 활성화
	PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI; // RTC 클럭 소스는 LSI
	HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);              // 클럭 설정 적용

	__HAL_RCC_RTC_ENABLE(); // RTC 클럭 공급 활성화

	// RTC 설정
	RtcHandle.Instance = RTC;                       // RTC 인스턴스 설정
	RtcHandle.Init.HourFormat = RTC_HOURFORMAT_24;  // 24시간 형식
	RtcHandle.Init.AsynchPrediv = RTC_ASYNCH_PREDIV; // 비동기 프리스케일러 설정
	RtcHandle.Init.SynchPrediv = RTC_SYNCH_PREDIV;   // 동기 프리스케일러 설정
	RtcHandle.Init.OutPut = RTC_OUTPUT_DISABLE;     // 출력 기능 비활성화

	HAL_RTC_Init(&RtcHandle); // 설정 적용
}

// 날짜 및 시간 초기 설정 함수
void rtc_calendar_config(void)
{
	RTC_DateTypeDef sdatestructure = {0}; // 날짜 구조체 선언
	RTC_TimeTypeDef stimestructure = {0}; // 시간 구조체 선언

	// 날짜 설정: 2019년 7월 14일 일요일
	sdatestructure.Year = 0x19;                 // 연도: 0x19 = 2019
	sdatestructure.Month = RTC_MONTH_JULY;      // 7월
	sdatestructure.Date = 0x14;                 // 14일
	sdatestructure.WeekDay = RTC_WEEKDAY_SUNDAY; // 일요일

	HAL_RTC_SetDate(&RtcHandle, &sdatestructure, RTC_FORMAT_BCD); // 날짜 설정

	// 시간 설정: 오전 3시 00분 00초
	stimestructure.Hours = 0x03;
	stimestructure.Minutes = 0x00;
	stimestructure.Seconds = 0x00;
	stimestructure.TimeFormat = RTC_HOURFORMAT12_AM; // 오전
	stimestructure.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	stimestructure.StoreOperation = RTC_STOREOPERATION_RESET;

	HAL_RTC_SetTime(&RtcHandle, &stimestructure, RTC_FORMAT_BCD); // 시간 설정

	// 설정 완료 플래그 기록
	HAL_RTCEx_BKUPWrite(&RtcHandle, RTC_BKP_DR0, BK_FLAG);
}

// 현재 날짜 및 시간 읽고 UART로 출력하는 함수
void rtc_calendar_show(uint8_t *showtime, uint8_t *showdate)
{
	RTC_DateTypeDef sdatestructureget = {0}; // 날짜 저장 구조체
	RTC_TimeTypeDef stimestructureget = {0}; // 시간 저장 구조체

	// 시간 먼저 읽기 (주의: 반드시 시간 → 날짜 순서)
	HAL_RTC_GetTime(&RtcHandle, &stimestructureget, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&RtcHandle, &sdatestructureget, RTC_FORMAT_BIN);

	// 시간 문자열 구성: hh:mm:ss 형식
	sprintf((char*)showtime, "%02d:%02d:%02d",
		stimestructureget.Hours, stimestructureget.Minutes, stimestructureget.Seconds);

	// 날짜 문자열 구성: mm-dd-yyyy 형식
	sprintf((char*)showdate, "%02d-%02d-%04d",
		sdatestructureget.Month, sdatestructureget.Date, 2000 + sdatestructureget.Year);

	// UART로 출력
	printf(" Time : %s\n\r", showtime);
	printf(" Date : %s\n\r", showdate);
}

// SysTick 인터럽트 핸들러 함수
void SysTick_Handler(void)
{
	HAL_IncTick(); // HAL 내부 타이머 1ms 증가
}

// UART2 초기화 함수 (PA2: TX, PA3: RX)
void uart_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0}; // GPIO 설정 구조체

	__HAL_RCC_GPIOA_CLK_ENABLE();  // GPIOA 클럭 활성화
	__HAL_RCC_USART2_CLK_ENABLE(); // USART2 클럭 활성화

	// PA2(TX), PA3(RX) 설정
	GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; // 대체 기능, Push-Pull 출력
	GPIO_InitStruct.Pull = GPIO_NOPULL;     // 풀업/풀다운 없음
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH; // 고속
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2; // UART2 대체 기능

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); // 설정 적용

	// UART2 설정
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;             // 보레이트
	huart2.Init.WordLength = UART_WORDLENGTH_8B; // 8비트 데이터
	huart2.Init.StopBits = UART_STOPBITS_1;      // 1 스톱 비트
	huart2.Init.Parity = UART_PARITY_NONE;       // 패리티 없음
	huart2.Init.Mode = UART_MODE_TX;             // 송신 전용 모드
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE; // 하드웨어 흐름 제어 없음
	huart2.Init.OverSampling = UART_OVERSAMPLING_16; // 오버샘플링

	HAL_UART_Init(&huart2); // UART 설정 적용
}
