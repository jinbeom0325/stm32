### realterm (시리얼 통신,uart등) 터미널 프로그램 
- 시리얼 통신은 데이터를 한비트씩 순서대로 주고 받는 방식
- PA2(TX) 송신해서 >> PC로 전송하면 >> 읽어주는곳이 realterm 시리얼 모니터 (아두이노 생각하면됨)

### 대표적인 시리얼 통신 종류
- 이런것들이 있고 아직 UART쪽 

|방식|	설명|	핀|
|--|--|--|
|UART|	MCU 내부 시리얼 모듈|	TX, RX|
|USART|	UART + 동기 방식 지원|	TX, RX|
|USB|	사실 내부적으로 시리얼 기반|	D+, D-|
|I2C|	시리얼 통신 종류|	SDA, SCL|
|SPI|	시리얼 통신 종류|	MOSI, MISO, SCK|
***
### cubleide에서 
- stm32f4xx_hal_conf.h는 어떤 HAL드라이버 쓸지 고르는 설정
- 드라이버에 있는 stm32f4xx_hal.h은 HAL라이브러리 묶음 각 모듈 include

### uart_polling 코드부분
- HAL_UART_Transmit(&huart2, (uint8_t *)message, 20, 100); 
  
  HAL_UART_Transmit( [어떤 UART], [보낼 데이터 주소], [보낼 데이터 크기], [타임아웃 시간] ) //Polling전송방식 상태계속 확인 
***
- UART_HandleTypeDef huart2;
 
  stm32 HAL이 이미 만들어 놓는 구조, UART 핸들러 구조체 선언
***
- huart2.Instance = USART2; 소프트웨어 구조 (HAL 레벨) 
  여기서 USART2는 주소값 그자체 , 이미정의 되어 있음 #define USART2((USART_TypeDef *) 0x40004400UL) 이런식으로 
  USART2쓸거라고 HAL에게 알려주는거 (메뉴얼 하드웨어 기준이라 없는듯)

코드 흐름
```
START
│
├─ 1. HAL_Init()                → HAL 라이브러리 기본 초기화
│                                 (시스템 클럭, 인터럽트, SysTick 설정)
│
├─ 2. uart_init()               → UART 관련 초기화
│    │
│    ├─ GPIO 클럭 ON           → __HAL_RCC_GPIOA_CLK_ENABLE()
│    ├─ UART 클럭 ON           → __HAL_RCC_USART2_CLK_ENABLE()
│    ├─ GPIO 핀 설정           → PA2(TX), PA3(RX) Alternate Function
│    ├─ huart2.Instance = USART2 → UART 레지스터 연결
│    └─ HAL_UART_Init(&huart2)  → 레지스터 세팅 자동으로 됨
│
└─ 3. while(1) 
     │
     ├─ HAL_UART_Transmit()   → huart2(=USART2) TX로 message 전송
     │
     ├─ HAL_Delay(10)         → 10ms 대기
     │
     └─ 반복
```
***
HAL_UART_Transmit 동작흐름 
```
HAL_UART_Transmit(huart2, message, 길이, 타임아웃)
│
├─ huart2.Instance → USART2 주소 참조
│
├─ 데이터 하나씩 TX 레지스터(USART2->DR)에 넣음
│
├─ TXE 플래그(비었는지) 확인하면서 반복
│
└─ 다 전송하면 종료

```
***
### uart_printf 코드부분
__io_putchar() 함수는 printf쓸 때 자동으로 불리는 함수 

***
system_stm32f4xx.c는 시스템 클럭 관련 핵심 설정 데이터(주파수값, AHB(cpu,메모리,SRAM), APB(gpio,UART,I2C,SPI))
|이름|	목적|	사용처|
|--|--|--|
|SystemCoreClock|	현재 CPU 클럭|	딜레이, SysTick|
|AHBPrescTable|	AHB 버스 나눌 때|	HCLK 계산|
|APBPrescTable|	APB 버스 나눌 때|	PCLK1, PCLK2 계산|

prescaler = 클럭 나눠주기 






