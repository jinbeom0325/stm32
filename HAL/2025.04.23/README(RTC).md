## RTC
- RTC(Real Time Clock): 전자 장치에서 실시간 날짜 및 시간을 유지하는 시계
- 전원이 꺼져도 시간이 유지됨 (배터리 백업 덕분)
- 예: 컴퓨터가 인터넷 없이도 시간/날짜 기억하는 이유
***
### STM32의 전원 도메인 구조
STM32는 2개의 전원 도메인을 가짐
- Main Power Domain (메인 전원): 일반 시스템 동작
- Backup Power Domain (백업 전원): RTC와 독립 감시 타이머(IWDG) 포함
  - 이 도메인은 배터리 또는 다른 전원으로 독립 동작 가능
    
RTC는 백업 도메인에 존재 → 메인 전원이 꺼져도 RTC는 계속 동작 가능
***
### RTC 백업 도메인 구성 요소
- RTC 레지스터
- 20개의 Backup Register (중요 데이터 저장 가능)
→ 시스템이 꺼져도 데이터 유지됨

아래의 경우에는 백업 레지스터가 초기화됨
- RCC 백업 도메인을 초기화한 경우
- Tamper(이상행동 감지) 발생 시
***
### 저전력 모드와 RTC
- STM32가 Sleep, Stop, Standby 모드에 들어가도, RTC는 계속 동작 가능
- EXTI Line 17을 통해 RTC 인터럽트로 시스템을 깨울 수 있음
***
### Tamper(탐퍼) 기능
- Tamper 핀을 통해 외부의 무단 접근 시도 감지 가능
- 감지 시, 백업 레지스터 초기화 + Tamper 인터럽트 발생
- 보안이 중요한 임베디드 시스템에 유용
***
### RTC Calendar 기능
RTC는 캘린더 기능을 통해 날짜와 시간을 추적함
- 시간 단위: 초, 분, 시 (12/24시간 지원)
- 날짜 단위: 요일, 일, 월, 연도
- 윤년 자동 처리
- Daylight Saving Time (서머타임) 조정 기능 지원
***
### BCD(Binary Coded Decimal) 포맷
RTC는 BCD 형식으로 시간/날짜 데이터를 제공
- 각 십진수 자릿수를 4비트 이진수로 표현
    예): 23 (십진수) → 0010 0011 (BCD)
- 데이터 처리 시, BCD ↔ 일반 십진수 변환 필요
***
### RTC 주요 기능
기능 | 설명
--|--
알람 A / B | 특정 시간에 인터럽트 발생 가능
Wakeup Timer | 주기적으로 시스템을 깨울 수 있음
Timestamp | 특정 이벤트 발생 시 시간 저장
Tamper Detection | 물리적 무단 접근 감지 기능
20개 백업 레지스터 | 중요한 데이터 저장 (전원 꺼져도 유지)
***
### RTC 클럭 소스와 프리스케일러
- RTC는 1Hz 주기로 동작해야 함 (1초마다 갱신)

- 사용 가능한 클럭 소스
  - LSE (Low Speed External, 32.768kHz)
  - LSI (Low Speed Internal, 약 32kHz)
  - HSE (High Speed External)

- 클럭 소스를 1Hz로 맞추기 위해 2개의 프리스케일러 사용
  - Asynchronous Prescaler: 7비트 (예: 127)
  - Synchronous Prescaler: 13비트 (예: 249)

예: LSE = 32.768kHz

Async = 127, Sync = 249 → 32,768 / ((127+1)(249+1)) = 1Hz
***




