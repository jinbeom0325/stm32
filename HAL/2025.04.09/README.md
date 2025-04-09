## HAL 설정 
### ~~에러코드 경로문제~~ ../Dmake: *** [Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/iar/subdir.mk:85: Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/iar/startup_stm32f401xc.o] Error 1
***
 ## 용어 
 ### APB
- ARM에서 사용하는 버스 종류 중 하나  
- **STM32 기준으로 보면** STM32 MCU 안에 있는 주변장Peripheral(타이머, UART, SPI 등)들이 연결되는 버스
 
|이름|	특징|	어디 연결|
|--|--|--|
|APB1|	저속(저클럭)|	타이머, UART2~5, I2C, SPI2, CAN 등|
|APB2|	고속(고클럭)|	GPIO, 타이머, UART1, SPI1, ADC 등|
***
### AHB
- STM32 내부에서 CPU, 메모리, 주변장치 연결하는 고속버스

|항목|	설명|
|--|--|
|연결|	메모리, GPIO, DMA, Flash 등|
|속도|	APB보다 빠름|
|역할|	CPU가 메모리나 GPIO 빠르게 접근할 때 사용|
***
```
//stm32버스구조 
                ┌─────────────┐
                │     CPU     │
                └─────┬───────┘
                      │
                ┌─────▼───────┐
                │     AHB     │  ← 고속 버스 (메모리, GPIO, DMA 연결)
                └─────┬───────┘
          ┌───────────┴───────────┐
          │                       │
        APB1                    APB2
   (느림, 저클럭)          (빠름, 고클럭)
   (UART2, TIM2 등)        (UART1, GPIO 등)

```
***
## 레지스터 정리중
|상태|	MODER 설정값|	설명|
|--|--|--|
|Input|	00|	외부 입력 받을 때|
|Output|	01|	GPIO 출력 핀|
|Alternate Function|	10|	UART, SPI, PWM, 타이머 등 주변기기 연결|
|Analog|	11|	ADC, DAC 등 아날로그 동작|
***
|상태|	OTYPER 설정값|	설명|
|--|--|--|
|Push-Pull|	0|	기본 출력 방식, 0 또는 1 출력 (구조: P-MOS + N-MOS)|
|Open-Drain|	1|	드레인 오픈 방식, 0만 출력 가능, 1출력 시 High-Z 상태 (외부 풀업 저항 필요)|
***
|상태|OSPEEDR 설정값|설명|
|--|--|--|
|Low Speed|00|2MHz 속도, 소비 전력 낮음, 신호 변화 느림|
|Medium Speed|01|12.5MHz ~ 50MHz 중간 속도|
|High Speed|10|25MHz ~ 100MHz 빠른 속도|
|Very High Speed|11|50MHz ~ 200MHz 최대 속도, 소비 전력 높음|
***
|상태|PUPDR 설정값|설명|
|--|--|--|
|Floating (No Pull)|00|내부 풀업/풀다운 저항 없음, 외부 회로에 따라 상태 결정|
|Pull-up|01|내부 풀업 저항 연결 (입력 시 기본 High 유지)|
|Pull-down|10|내부 풀다운 저항 연결 (입력 시 기본 Low 유지)|
|Reserved|11|사용 안 함 (설정 금지)|
***
|상태|IDR 값|설명|
|--|--|--|
|Low (입력 Low)|0|핀 상태가 Low (0V 또는 GND 레벨)|
|High (입력 High)|1|핀 상태가 High (VCC 레벨)|
***
|상태|ODR 값|설명|
|--|--|--|
| Low (출력 Low)    | 0     | 핀 상태가 Low (0V 또는 GND 레벨)|
| High (출력 High)  | 1     | 핀 상태가 High (VCC 레벨)|
***
비트 설정/리셋 레지스터
| 상태               | BSRR 값 | 설명                                   |
|------------------|--------|--------------------------------------|
| Set (출력 High)   | 1      | 해당 핀을 High로 설정 (VCC 레벨)       |
| Reset (출력 Low)  | 0      | 해당 핀을 Low로 설정 (0V 또는 GND 레벨) |
***
잠금레지스터 
| 상태               | LCKR 값 | 설명                                   |
|------------------|--------|--------------------------------------|
| Locked (잠금)     | 1      | 해당 핀의 설정이 잠금 상태 (수정 불가) |
| Unlocked (해제)   | 0      | 해당 핀의 설정이 해제 상태 (수정 가능) |
***
| 상태               | AFRL 값 | 설명                                       |
|------------------|--------|------------------------------------------|
| 기능 선택 0      | 0      | 해당 핀의 기본 기능 (예: GPIO 입력/출력)   |
| 기능 선택 1~7    | 1~7    | 해당 핀에 대한 대체 기능 (예: UART, SPI 등) |





 
 
