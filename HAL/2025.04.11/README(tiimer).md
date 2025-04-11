## SysTick Timer
모든 Cortex-M 마이크로컨트롤러에 기본적으로 포함되어 있는 타이머
***
**Delay 계산 방법 예시**

  System Clock = 16MHz

  LOAD 레지스터 값 = 9 → 총 10클록 딜레이 (0~9 세니까)

  1클록 시간 = 1 / 16M = 62.5ns

  총 딜레이 = 10 * 62.5ns = 625ns (나노초)
  ***
Delay 구하는 공식
- Delay Time = (LOAD 레지스터 값 + 1) / System Clock

LOAD 값 구하는 공식
- LOAD = Delay Time * System Clock - 1
***
## Timer vs Counter 개념 차이
|Clock Source|	명칭|
|--|--|
|내부 클럭 사용|	Timer (타이머)|
|외부 입력 클럭 사용|	Counter (카운터)|
***
## 주요 레지스터
|레지스터|	기능|
|--|--|
|CNT (Counter Register)|	현재 카운터 값 저장 (16bit or 32bit)|
|ARR (Auto Reload Register)|	타이머가 카운트할 최대값 (주기 설정)|
|PSC (Prescaler Register)|	타이머 입력 클럭 나눠서 느리게 만듦|
***
## 타이머 동작 흐름

타이머 클럭 흐름 (예: System Clock = 16MHz)
1. System Clock → Divider
   
    - 16MHz → Divider = 1 → 그대로 16MHz

2. Divider → APB Prescaler
   
    - APB Prescaler = 1 → 그대로 16MHz

    - APB Prescaler가 2 이상이면 Timer Clock = APB Clock × 2

3. Timer Clock → Timer Prescaler (PSC)
   
    - PSC = 15999 설정

    → Timer Clock ÷ (PSC + 1) = 16MHz ÷ 16000 = 1kHz

    → Timer CNT 값이 1ms 마다 1씩 증가

4. Timer CNT → ARR 비교
   
    ARR = 원하는 값 설정 (예: ARR = 999)

    → CNT가 0 ~ 999까지 세면 총 1000번 → 1초

5. CNT = ARR → 이벤트 발생
   
  * CNT 값이 ARR 값 도달 시

    - CNT → 0으로 초기화

    - Update Event 발생 (인터럽트 발생 가능)
***
## 타이머 주기 계산 공식(인터럽트 발생 주기)
타이머 주기 = (PSC + 1) x (ARR + 1) / Timer Clock
```
//예시
Timer Clock = 48MHz

PSC = 47999

ARR = 499

주기 = (47999 + 1) x (499 + 1) / 48,000,000  
     = 48,000 x 500 / 48,000,000  
     = 0.5초 (500ms)
```
***
|용어|	의미|	설명|
|--|--|--|
|System Clock (시스템 클럭)|	MCU 기본 동작 클럭|	STM32F401RE 기준 내부 또는 외부 클럭 (예: 16MHz)|
|Divider (분주기)|	클럭 나누기 설정|	Timer에 들어가기 전 클럭 나눔 (보통 APB 클럭 관련)|
|APB Prescaler (APB 프리스케일러)|	APB 버스 클럭 나누기|	APB1, APB2 버스 클럭을 나눔 (타이머 동작 클럭에 영향)|
|Timer Prescaler (PSC)|	타이머 내부 분주기|	Timer CNT가 올라가는 속도 결정|
|ARR (Auto Reload Register)|	자동 리로드 값|	CNT가 ARR 값까지 도달하면 0으로 초기화 + 이벤트 발생|
|CNT (Counter)|	타이머 카운터 값|	PSC 설정에 따라 일정 주기마다 증가하는 값|
***
|용어|의미|
|--|--|
|Update Event|	Timeout 발생 (인터럽트 발생)|
|Period|	ARR 값 (카운트 최대값)|
|Up Counter|	0부터 ARR까지 증가|
|Down Counter|	ARR부터 0까지 감소|


  



