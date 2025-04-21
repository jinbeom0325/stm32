## 코드흐름

### 1.초기화
```c
HAL_Init();        // HAL 라이브러리 초기화 (시스템 타이머 등 내부 설정)
uart_init();       // UART1, GPIO, DMA 초기화
```
- HAL 관련 기본 시스템 설정 (SysTick, NVIC, 내부 변수 등)
- uart_init() 안에서:
  - GPIOA (PA9, PA10) → UART용으로 설정
  - USART1 → 보레이트 등 UART 설정
  - DMA2 Stream2 (RX), Stream7 (TX) → 초기화 및 UART 연결
  - DMA 인터럽트 우선순위 설정 및 활성화

### 2.UART DMA 송수신 시작
```c
HAL_UART_Transmit_DMA(&huart1, tx_buffer, 10); // TX 시작
HAL_UART_Receive_DMA(&huart1, rx_buffer, 10);  // RX 시작
```
- DMA를 이용한 비동기 송수신 시작
- tx_buffer의 10바이트를 송신
- 수신된 10바이트는 rx_buffer에 저장

### 3.콜백 함수 동작
```c
//송신 완료 시 
HAL_UART_TxCpltCallback() → tx_counter++; // 송신 완료 횟수 증가
```
```c
//수신 완료 시
HAL_UART_RxCpltCallback() → rx_counter++; // 수신 완료 횟수 증가
```

### 4.인터럽트 핸들러 동작
```c
DMA2_Stream2_IRQHandler() → HAL_DMA_IRQHandler(&hdma_usart1_rx);
DMA2_Stream7_IRQHandler() → HAL_DMA_IRQHandler(&hdma_usart1_tx);
```
- 송/수신 중 DMA 전송이 완료되면 IRQ 발생
- 해당 IRQ 핸들러에서 HAL이 자동으로 내부 상태를 처리
-그리고 HAL 내부적으로 적절한 HAL_UART_*CpltCallback() 함수가 호출됨
***

## 흐름 요약
```c
main()
 ├─ HAL_Init()
 ├─ uart_init()
 │   ├─ GPIO 설정
 │   ├─ UART 설정
 │   ├─ DMA 설정 (TX/RX)
 │   └─ 인터럽트 활성화
 ├─ HAL_UART_Transmit_DMA()   ← DMA 송신 시작
 ├─ HAL_UART_Receive_DMA()    ← DMA 수신 시작
 └─ while(1) 루프

↓ (전송/수신 완료 시)
DMA IRQ 발생
 ├─ DMA2_StreamX_IRQHandler()
 │   └─ HAL_DMA_IRQHandler()
 │       └─ HAL_UART_Tx/RxCpltCallback() 호출됨
 └─ tx_counter / rx_counter 증가
```

### 코드 새로운 부분 
```c
.Init.PeriphInc = DMA_PINC_DISABLE; // 주변기기 주소 고정 (레지스터니까)
.Init.MemInc = DMA_MINC_ENABLE;     // 메모리 주소 증가 (배열 저장)

.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE; // (UART는 바이트 단위 전송이므로)
.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;

.Init.Mode = DMA_NORMAL; // NORMAL: 전송 한 번만 수행하고 끝

.Init.Priority = DMA_PRIORITY_LOW; // 우선순위는 여러 DMA가 겹칠 때 고려
.Init.FIFOMode = DMA_FIFOMODE_DISABLE; // FIFO 미사용 시 직접 전송
```

### 용어 
용어 | 의미
--|--
Stream | DMA 내부의 데이터 전송 단위. 하나의 송수신 작업을 맡음 (ex: USART1_RX용 Stream2)
Channel | 어떤 주변장치(USART, ADC 등)가 사용할 수 있는 연결 라인. 하나의 스트림에 여러 채널 중 하나를 선택해서 연결

- 스트림(Stream): DMA가 사용하는 도로(고속도로 차선)
- 채널(Channel): 각각의 목적지에 연결된 출입구(램프)
- 즉 하나의 스트림에는 여러 개의 채널이 연결되어 있다. 


