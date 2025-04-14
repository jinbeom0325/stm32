## ADC Independent Modes
ADC는 아날로그 신호(전압)를 디지털 신호(숫자)로 바꿔주는 작업 

STM32 시리즈 MCU에는 ADC 동작 모드가 여러 개 존재
- Independent Modes (독립 모드) → 이번 수업 내용
- Dual Modes (듀얼 모드) → ADC가 2개 이상 있을 때만 가능 (STM32F7 등)
***
STM32F4는

ADC Module(변환장치) = 1개

ADC Channel(아날로그 입력 핀) = 최대 16개 (센서 16개 연결 가능)

따라서 Independent Modes만 사용 가능
***
## Independent Modes 종류 (5가지)
## Single Channel, Single Conversion Mode (단일 채널 단일 변환 모드)
```
START → 변환 (1회) → STOP
```
- 특징
  - 채널 1개만 변환
  - 변환 끝나면 자동 종료
- 사용 예
  - 전압 확인 후 부팅 여부 결정
  - 배터리 레벨 체크 등
    
## Multi Channel, Single Conversion Mode (다중 채널 단일 변환 모드)
```
START → 채널1 변환 → 채널2 변환 → ... → 채널N 변환 → STOP
```
- 특징
  - 여러 채널을 순차적으로 1회씩 변환
  - 각 채널 별 Sampling Time 설정 가능
- 사용 예
  - 여러 센서 데이터 모아서 조건 만족 여부 판단

## Single Channel, Continuous Conversion Mode (단일 채널 연속 변환 모드)
```
START → 변환 → 변환 → 변환 → ... (무한 반복)
```
- 특징
  - 한 채널만 계속 반복 변환
  - CPU 개입 X (백그라운드 동작)
- 사용 예
  - 온도센서 → 에어컨 자동 제어
  - 조도센서 → 밝기 조절 등

## Multi Channel, Continuous Conversion Mode (다중 채널 연속 변환 모드)
```
START → 채널1 변환 → 채널2 변환 → ... → 채널N 변환 → 다시 채널1 변환 → 반복
```
- 특징
  - 여러 채널을 순차적으로 계속 반복 변환
- 사용 예
  - 로봇팔 위치 모니터링 (Joint 5개 위치 지속 측정 등)
  - 여러 센서 동시 모니터링

## Injected Conversion Mode (인젝션 변환 모드)
```
특정 이벤트 발생 → 즉시 우선 변환 수행
```
- 특징
  - 외부 이벤트나 소프트웨어 트리거 발생 시 ADC 변환
  - Regular Group보다 우선순위 높음
  - Regular Group 동작 중에도 Interrupt 가능
- 사용 예
  - 특정 시간 동기화 ADC 측정
  - 외부 인터럽트 발생 시 ADC 측정
  - 고정밀, 이벤트 기반 변환 필요 시

regular group은 정규변환 그룹으로 센서 값을 계속 읽거나, 한 번만 읽는 등의 상황에서의 ADC변환 방식 

injected group은 우선순위 변환 그룹으로 regular group을 끼어들기(인터럽트)해서 긴급하게 측정하고 싶은 채널 

평소에 regular group으로 센서들을 측정 중인데, 갑자기 중요한 이벤트가 발생하면 injected group으로 실행됨
***
