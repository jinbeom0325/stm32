## 코드내용
### 메인
```c
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
//        HAL_Delay(10);               // 딜레이 추가 가능
    }
}
```
- RTC 핸들 초기화: __HAL_RTC_RESET_HANDLE_STATE(&RtcHandle)를 사용해 RTC 핸들의 내부 상태를 초기화. RTC의 상태가 이전에 설정된 값과 충돌하지 않도록 하기위해
- RTC 초기화: rtc_init() 함수가 호출되어 RTC의 설정
- 백업 레지스터 확인: RTC가 이미 설정되었는지 확인하기 위해 백업 레지스터(RTC_BKP_DR0)를 확인. 초기화되지 않았다면 rtc_calendar_config() 함수로 날짜와 시간을 설정
- 무한 루프: rtc_calendar_show(time, date) 함수가 호출되어 현재 RTC에서 날짜와 시간을 읽고, UART로 출력
***

### RTC초기화 
```c
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
```
- 오실레이터 설정: RCC_OscInitTypeDef 구조체를 사용하여 내부 클럭 LSI(32kHz)를 활성화하고 외부 LSE(32.768kHz)는 비활성화
- RTC 클럭 설정: RCC_PeriphCLKInitTypeDef 구조체를 통해 RTC 클럭 소스를 LSI로 설정
- RTC 클럭 공급: __HAL_RCC_RTC_ENABLE()을 호출하여 RTC에 클럭을 공급
- RTC 초기화: RTC 인스턴스를 설정하고, 24시간 형식, 프리스케일러 값을 설정
***

### 날짜 및 시간 초기 설정
```c
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
```
- 날짜 설정: RTC_DateTypeDef 구조체를 사용하여 2019년 7월 14일을 설정
- 시간 설정: RTC_TimeTypeDef 구조체를 사용하여 오전 3시 00분 00초로 설정
- 설정 완료 플래그 기록: 설정이 완료되면, 백업 레지스터에 플래그를 기록해서 다시 초기화 방지 
***

### 현재 날짜 및 시간 읽고 uart로 출력
```c
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
```
- 시간과 날짜 읽기: HAL_RTC_GetTime()과 HAL_RTC_GetDate()를 호출하여 RTC에서 현재 시간과 날짜 읽음
- 시간 문자열 구성: sprintf()를 사용하여 읽어온 시간을 hh:mm:ss 형식으로 문자열로 저장
- 날짜 문자열 구성: sprintf()를 사용하여 읽어온 날짜를 mm-dd-yyyy 형식으로 문자열로 저장
- UART로 출력: printf()를 통해 시간을 UART로 출력
***

