## HAL 설정 
### ~~에러코드 경로문제~~ ../Dmake: *** [Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/iar/subdir.mk:85: Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/iar/startup_stm32f401xc.o] Error 1

```c
//BTN = PC13
//LED = PA5
```
 ## 용어 
 ### APB
- ARM에서 사용하는 버스 종류 중 하나  
- **STM32 기준으로 보면** STM32 MCU 안에 있는 Peripheral(타이머, UART, SPI 등)들이 연결되는 버스
 
|이름|	특징|	어디 연결|
|--|--|--|
|APB1|	저속(저클럭)|	타이머, UART2~5, I2C, SPI2, CAN 등|
|APB2|	고속(고클럭)|	GPIO, 타이머, UART1, SPI1, ADC 등|

### AHB
- STM32 내부에서 CPU, 메모리, 주변장치 연결하는 고속버스
```
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
|항목|	설명|
|--|--|
|연결|	메모리, GPIO, DMA, Flash 등|
|속도|	APB보다 빠름|
|역할|	CPU가 메모리나 GPIO 빠르게 접근할 때 사용|
 
 
