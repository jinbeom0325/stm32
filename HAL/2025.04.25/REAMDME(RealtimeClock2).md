RTC가 꺼져도 시간이 유지되는 이유는 백업 도메인(Backup Domain) 과 백업 전원(VBAT)덕분

백업도메인(Backup Domain)
- RTC 레지스터
- RTC 백업 레지스터 (DR0 ~ DR19)
- RTC 클럭 설정
- LSE,LSI 오실레이터 설정

백업 전원(VBAT)
- VBAT핀은 전원(VDD)이 꺼져도 RTC에 전력을 공급해주는 배터리 입력 핀
***

## 코드분석
```c
// RTC 프리스케일러 값 설정 (RTC 클럭을 1Hz로 만들기 위함)
#define RTC_ASYNCH_PREDIV  0x7F // 비동기 프리스케일러 (127)
#define RTC_SYNCH_PREDIV   0xF9 // 동기 프리스케일러 (249)
```
RCT 클럭 수식 : RTC_Clock / ((Asynch_Prescaler + 1) * (Synch_Prescaler + 1)) = 1Hz 

LSI 클럭 32kHz = 32,000Hz 를 프리스케이러로 나눠서 1Hz = 1초 주기로 만들어야 함

Asynch_Prescaler는 7비트 최대 127 까지 Synch_Prescaler는 15비트 32,767까지 가능하지만 

비동기 프리스케일러를 작게하면 동작전류가 낮고 전력 소모가 적어서 127, 249 조합을 많이 씀 
***

## rtc_init(void) 함수
**RTC를 사용할 수 있도록 내부 오실레이터 설정 -> RTC클럭 소스 설정 -> RTC 기본 설정 적용**
```c
// 오실레이터 설정 관련 구조체 초기화
RCC_OscInitTypeDef RCC_OscInitStruct = {0}; //정의 및 초기화 
RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
```
- RCC_OscInitTypeDef → 오실레이터 종류/상태 설정 (LSI/LSE 등)
- RCC_PeriphCLKInitTypeDef → RTC 같은 주변장치에 어떤 클럭을 공급할지 설정
***

```c
// 오실레이터 종류 설정
RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE;
RCC_OscInitStruct.LSEState = RCC_LSE_OFF; // 외부 클럭 OFF
RCC_OscInitStruct.LSIState = RCC_LSI_ON;  // 내부 클럭 ON
HAL_RCC_OscConfig(&RCC_OscInitStruct);
```
- LSE: 외부 32.768kHz 크리스탈 (정확하지만 하드웨어 필요)
- LSI: 내부 32kHz RC 오실레이터 (정확도 떨어지지만 하드웨어 불필요)
- 이 코드는 LSI를 켜고 LSE는 끄는 설정, 별도 크리스탈 없이 내부 RC 클럭으로 RTC 구동
***

```c
// RTC 클럭 소스 설정
PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
__HAL_RCC_RTC_ENABLE(); //RTC클럭 활성화 (RTC동작)
```
- RCC_PERIPHCLK_RTC: RTC에 쓸 클럭 소스를 설정 선언
- RCC_RTCCLKSOURCE_LSI: 위에서 켜놓은 LSI를 RTC 클럭 소스로 지정
- HAL_RCCEx_PeriphCLKConfig: 설정을 실제로 적용
***

```c
// RTC설정
RtcHandle.Instance = RTC;
RtcHandle.Init.HourFormat = RTC_HOURFORMAT_24;
RtcHandle.Init.AsynchPrediv = RTC_ASYNCH_PREDIV;
RtcHandle.Init.SynchPrediv = RTC_SYNCH_PREDIV;
RtcHandle.Init.OutPut = RTC_OUTPUT_DISABLE;

HAL_RTC_Init(&RtcHandle); //설정 반영
```
설정 항목 | 설명
--|--
HourFormat = 24 | 24시간 형식 사용
AsynchPrediv | RTC 프리스케일러 설정 (비동기)
SynchPrediv | RTC 프리스케일러 설정 (동기)
OutPut = DISABLE | RTC 알람/펄스 출력 기능 사용 안함
***

## rtc_calendar_config(void) 함수
**RTC를 초기화하는 코드로, 주어진 날짜와 시간 정보를 설정하고, RTC 설정이 완료되었음을 백업 레지스터에 기록하는 함수**

```c
// 구조체 초기화 
RTC_DateTypeDef sdatestructure = {0}; // 날짜 구조체 선언 초기화 
RTC_TimeTypeDef stimestructure = {0}; // 시간 구조체 선언 초기화 
```
- RTC_DateTypeDef는 연도, 월, 일, 요일 등
- RTC_TimeTypeDef는 시간, 분, 초, 오전/오후 형식 등

```c
// 날짜 설정: 2019년 7월 14일 일요일
sdatestructure.Year = 0x19;                 // 연도: 0x19 = 2019
sdatestructure.Month = RTC_MONTH_JULY;      // 7월
sdatestructure.Date = 0x14;                 // 14일
sdatestructure.WeekDay = RTC_WEEKDAY_SUNDAY; // 일요일

HAL_RTC_SetDate(&RtcHandle, &sdatestructure, RTC_FORMAT_BCD); // 날짜 설정
```
- 연도 (Year): 0x19는 19를 의미 RTC는 연도를 BCD(Binary-Coded Decimal) 형식으로 저장
- 월 (Month): RTC_MONTH_JULY는 7월을 의미 RTC_MONTH_JULY는 RTC 라이브러리에서 미리 정의된 값
- 일 (Date): 0x14는 14일을 의미
- 요일 (WeekDay): RTC_WEEKDAY_SUNDAY는 일요일 STM32 RTC는 1~7 값으로 요일을 설정가능
- HAL_RTC_SetDate() 함수는 실제 RTC 하드웨어에 날짜 정보를 설정하는 함수
- RTC_FORMAT_BCD는 날짜 정보가 BCD 형식으로 전달된다는 것 (이진화 십진수, 각자리를 4비트씩표현)
***
```c
// 시간 설정: 오전 3시 00분 00초
stimestructure.Hours = 0x03;
stimestructure.Minutes = 0x00;
stimestructure.Seconds = 0x00;
stimestructure.TimeFormat = RTC_HOURFORMAT12_AM; // 오전
stimestructure.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
stimestructure.StoreOperation = RTC_STOREOPERATION_RESET;

HAL_RTC_SetTime(&RtcHandle, &stimestructure, RTC_FORMAT_BCD); // 시간 설정
```
- 시 (Hours): 0x03은 3시
- 분 (Minutes): 0x00은 00분
- 초 (Seconds): 0x00은 00초
- 시간 형식 (TimeFormat): RTC_HOURFORMAT12_AM은 12시간 형식, 오전을 설정. 만약 24시간 형식으로 설정하려면 RTC_HOURFORMAT_24를 사용
- Daylight Saving (DayLightSaving): RTC_DAYLIGHTSAVING_NONE은 서머타임 적용을 하지 않음을 설정
- 저장 작업 (StoreOperation): RTC_STOREOPERATION_RESET은 저장 작업을 하지 않고 리셋 상태로 설정함(한번 설정하면 시간이 계속 흐르기 때문에 reset으로 설정,불필요데이터 삭)
- HAL_RTC_SetTime() 함수는 실제 RTC 하드웨어에 시간을 설정하는 함수
- RTC_FORMAT_BCD는 시간을 BCD 형식으로 전달하는 설정
***
```c
// 설정 완료 플래그 기록
HAL_RTCEx_BKUPWrite(&RtcHandle, RTC_BKP_DR0, BK_FLAG);
```
HAL_RTCEx_BKUPWrite() 함수는 RTC 백업 레지스터에 값을 기록하는 함수
RTC_BKP_DR0: RTC 백업 레지스터 0에 플래그 값을 기록해서 다시 부팅될때 날짜/시간 설정을 건너뛰기 위해 사용 
***

## rtc_calendar_show(uint8_t *showtime, uint8_t *showdate) 함수
**RTC에 저장된 시간과 날짜를 읽고, 문자열 형식으로 변환하여 UART통신으로 출력 하는 함수**
showtime,showdate는 각각 시간/날짜 문자열이 저장될 버퍼 

```c
//구조체 정의와 초기화
RTC_DateTypeDef sdatestructureget = {0}; // 날짜 저장 구조체
RTC_TimeTypeDef stimestructureget = {0}; // 시간 저장 구조체
```
***

```c
HAL_RTC_GetTime(&RtcHandle, &stimestructureget, RTC_FORMAT_BIN);
HAL_RTC_GetDate(&RtcHandle, &sdatestructureget, RTC_FORMAT_BIN);
```
- 반드시 시간 -> 날짜 순서로 읽어야 함 RTC모듈에서 시간과 날짜를 쉐도우 레지스터로 처리하여, 시간이 바뀌면 날짜에 영향을 미칠 수 있기 때문 (날짜먼저 읽으면 사이에 시간이 바뀌어 잘못된 날짜 가능성)
- 설정할때는 BCD로 했고 읽을 때는 BIN(이진)로 읽어야 빠름
***
```c
// 시간 문자열 구성 
sprintf((char*)showtime, "%02d:%02d:%02d",
stimestructureget.Hours, stimestructureget.Minutes, stimestructureget.Seconds);
```
- 현재 시간,분,초를 각각 추출하고 형식에 맞게 저장
- (char)* showtime 하면 안됨 포인터를 형변환 하려면 (char*)showitme처럼 사용 
***

```c
// 날짜 문자열 구성
sprintf((char*)showdate, "%02d-%02d-%04d",
sdatestructureget.Month, sdatestructureget.Date, 2000 + sdatestructureget.Year);
```
- +2000해서 실제 연도와 날짜 반환
***


