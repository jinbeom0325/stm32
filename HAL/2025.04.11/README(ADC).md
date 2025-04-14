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


    
