## 코드흐름

### 초기화
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

### UART DMA 송수신 시작
```c
HAL_UART_Transmit_DMA(&huart1, tx_buffer, 10); // TX 시작
HAL_UART_Receive_DMA(&huart1, rx_buffer, 10);  // RX 시작
```
- DMA를 이용한 비동기 송수신 시작
- tx_buffer의 10바이트를 송신
- 수신된 10바이트는 rx_buffer에 저장

### 콜백 함수 동작
```c
//송신 완료 시 
HAL_UART_TxCpltCallback() → tx_counter++; // 송신 완료 횟수 증가
```
```c
//수신 완료 시
HAL_UART_RxCpltCallback() → rx_counter++; // 수신 완료 횟수 증가
```

### 인터럽트 핸들러 동작
```c
DMA2_Stream2_IRQHandler() → HAL_DMA_IRQHandler(&hdma_usart1_rx);
DMA2_Stream7_IRQHandler() → HAL_DMA_IRQHandler(&hdma_usart1_tx);
```
- 송/수신 중 DMA 전송이 완료되면 IRQ 발생
- 해당 IRQ 핸들러에서 HAL이 자동으로 내부 상태를 처리
-그리고 HAL 내부적으로 적절한 HAL_UART_*CpltCallback() 함수가 호출됨
 

