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
- 시스템 클럭 → Divider → APB1 / APB2 Bus → Timer

- Timer Prescaler (PSC) 로 클럭 속도를 더 나눔

- CNT 값이 ARR 값과 같아지면 → Interrupt 발생 (Update Event)

- CNT 값 자동 초기화 후 다시 카운트 시작

만약 시스템 클럭이 16MHz 라고 가정하면,

Divider = 1 → 그대로 16MHz

APB Prescaler = 1 → 그대로 16MHz

Timer Prescaler (PSC) = 원하는 값으로 설정
예) PSC = 15999 → (16MHz / (15999 + 1)) = 1kHz
→ 타이머는 1ms마다 CNT 값 증가
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
|용어|의미|
|--|--|
|Update Event|	Timeout 발생 (인터럽트 발생)|
|Period|	ARR 값 (카운트 최대값)|
|Up Counter|	0부터 ARR까지 증가|
|Down Counter|	ARR부터 0까지 감소|


  



