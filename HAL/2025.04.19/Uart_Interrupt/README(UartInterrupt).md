## 목적

- UART1을 초기화

- 10바이트의 데이터를 비동기로 전송(Transmit_IT)

- 10바이트의 데이터를 비동기로 수신(Receive_IT)

- 송수신이 완료될 때마다 콜백 함수가 호출되어 카운터를 증가

## 코드흐름
### main() 함수
- HAL_UART_Transmit_IT(): tx_buffer의 10바이트를 비동기 송신 시작.

- HAL_UART_Receive_IT(): 10바이트 수신 대기 시작 → 데이터가 수신되면 인터럽트 발생.

### uart_init() 함수
- GPIOA 클럭 활성화: UART TX/RX 핀은 PA9, PA10을 사용하므로 GPIOA 포트가 필요.

- PA9/PA10 핀 설정:

  - 모드: AF_PP (Alternate Function Push-Pull)

  - 속도: 매우 빠르게 설정

  - 대체 기능: AF7 → USART1 사용

- UART1 클럭 활성화

- UART 설정: 115200 bps, 8N1 (8비트 데이터, 패리티 없음, 1 스톱비트)

- 인터럽트 활성화:

  - USART1_IRQn의 우선순위 설정 후 인터럽트 사용 허가

 ### USART1_IRQHandler() 함수
- UART 인터럽트가 발생했을 때 호출됨.

- 실제 처리는 HAL 내부의 HAL_UART_IRQHandler()가 수행.

### HAL_UART_TxCpltCallback() & HAL_UART_RxCpltCallback() 함수
- 각각 송신과 수신이 완료되었을 때 자동으로 호출되는 함수.

- 카운터를 증가시켜서 몇 번 완료되었는지 추적 가능.
