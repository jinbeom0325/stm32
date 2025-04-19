## 코드흐름 요약
- HAL 초기화

- UART1, UART2 핀 및 설정 초기화

- UART1, UART2 인터럽트 설정

- UART1, UART2 각각 10바이트 데이터 비동기 송신 및 수신 시작

- 수신 또는 송신이 완료되면 → 자동으로 콜백 함수 실행

- 콜백 함수 안에서 각각 완료 카운터 증가 (디버깅용)
***

### main() 함수 진입
```c
HAL_Init();         // HAL 드라이버 초기화
uart1_init();       // UART1 초기화
uart2_init();       // UART2 초기화
```
- HAL 내부 시스템 초기화
- UART1, UART2 핀과 설정 구성
  
### 비동기 송수신 시작
```c
HAL_UART_Transmit_IT(&huart1, tx_buffer1, 10); // UART1로 데이터 10바이트 송신
HAL_UART_Receive_IT(&huart1, rx_buffer1, 10);  // UART1로 데이터 10바이트 수신
HAL_UART_Transmit_IT(&huart2, tx_buffer2, 10); // UART2로 데이터 10바이트 송신
HAL_UART_Receive_IT(&huart2, rx_buffer2, 10);  // UART2로 데이터 10바이트 수신
```
- 비동기 송수신이기 때문에 데이터 전송이 끝나기 전에도 다음 명령 실행 가능
- 실제 완료는 인터럽트 기반으로 콜백에서 처리

### 송신 완료 시 콜백
```c
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
```
- UART1 또는 UART2 중 어떤 UART에서 송신이 끝났는지 확인
- 각각 tx_counter1, tx_counter2 증가 → 나중에 전송 완료 횟수 체크용

### 수신 완료 시 콜백
```c
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
```
- UART1 또는 UART2 중 어떤 UART에서 수신이 끝났는지 확인
- 각각 rx_counter1, rx_counter2 증가 → 나중에 수신 완료 횟수 체크용

  
