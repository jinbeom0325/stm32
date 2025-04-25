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

### rtc_init(void) 함수
**RTC를 사용할 수 있도록 내부 오실레이터 설정 -> RTC클럭 소스 설정 -> RTC 기본 설정 적용**
```c
// 오실레이터 설정 관련 구조체 초기화화
RCC_OscInitTypeDef RCC_OscInitStruct = {0};
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

### rtc_calendar_config(void) 함수
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
- 연도 (Year): 0x19는 2019년을 의미 RTC는 연도를 BCD(Binary-Coded Decimal) 형식으로 저장하므로 0x19는 2019년의 BCD 값
- 월 (Month): RTC_MONTH_JULY는 7월을 의미 RTC_MONTH_JULY는 RTC 라이브러리에서 미리 정의된 값으로, 7월
- 일 (Date): 0x14는 14일을 의미
- 요일 (WeekDay): RTC_WEEKDAY_SUNDAY는 일요일 STM32 RTC는 0~6 값으로 요일을 설정할 수 있으며, 일요일은 0
- HAL_RTC_SetDate() 함수는 실제 RTC 하드웨어에 날짜 정보를 설정하는 함수
- RTC_FORMAT_BCD는 날짜 정보가 BCD 형식으로 전달된다는 것





