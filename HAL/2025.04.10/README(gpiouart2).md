## GpioInputOutput
```c
//구조체 
typedef struct
{
	uint32_t Pin;        // 사용할 핀 번호
	uint32_t Mode;       // 동작 모드 설정
	uint32_t Pull;       // Pull-up / Pull-down 설정
	uint32_t Speed;      // 속도 설정
	uint32_t Alternate;  // Alternate Function 설정
} GPIO_InitTypeDef;
```
***
세부설명
|멤버|	설명|	예시|
|--|--|--|
|Pin|	설정할 핀|	GPIO_PIN_0 ~ GPIO_PIN_15|
|Mode|	핀 동작 모드|	GPIO_MODE_INPUT, GPIO_MODE_OUTPUT_PP, GPIO_MODE_AF_PP 등|
|Pull|	풀업/풀다운 설정|	GPIO_NOPULL, GPIO_PULLUP, GPIO_PULLDOWN|
|Speed|	출력 속도|	GPIO_SPEED_LOW, GPIO_SPEED_MEDIUM, GPIO_SPEED_HIGH, GPIO_SPEED_VERY_HIGH|
|Alternate|	AF 모드 시 사용|	AF 번호 지정 (예: GPIO_AF7_USART2)|
***

### GpioInputOutput 주요코드 정리 
|내용|	설명|
|--|--|
|HAL_Init|	HAL 기반 MCU 내부 초기화|
|GPIO_Init|	핀 설정 (입력 / 출력 / 풀업 / 풀다운)|
|HAL_GPIO_ReadPin|	입력핀 값 읽기|
|HAL_GPIO_WritePin|	출력핀 값 쓰기|
|Systick_Handler|	ms 시간 카운팅 처리|
***

## UartTx_Polling강의 부분 

|구분|	UART|	USART|
|--|--|--|
|지원 방식|	비동기 통신만 지원|	비동기 + 동기 둘 다 지원|
|클럭 신호(CLK)|	없음|	있음(동기 모드에서 사용)|
|하드웨어 구성|	TX, RX|	TX, RX, (필요시 CLK)|
|속도|	상대적 느림|	동기 모드 시 더 빠름|  
***
## UART 구조체 내용
| 항목 | 의미 | 설명 |
|------|------|------|
| uint32_t BaudRate | 통신 속도 | 전송 속도(bps) 설정 (ex: 9600, 115200) |
| uint32_t WordLength | 데이터 비트 수 | 전송 데이터 비트 길이 (8bit or 9bit) |
| uint32_t StopBits | 스탑 비트 수 | 데이터 전송 끝 표시 비트 (1bit or 2bit) |
| uint32_t Parity | 패리티 비트 | 오류 검출 비트 설정 (None, Even, Odd) |
| uint32_t Mode | 동작 모드 | 송신(TX), 수신(RX), 둘 다(TX_RX) 설정 |
| uint32_t HwFlowCtl | 하드웨어 플로우 제어 | 흐름제어 사용 여부 (None, RTS, CTS, RTS_CTS) |
| uint32_t OverSampling | 오버샘플링 설정 | 데이터 샘플링 속도 (8배 or 16배 샘플링) |
***
### 데이터 통신방식 분류
- UART는 보통 full-duplex구조
  
|구분|	설명|	예시|	방향|
|--|--|--|--|
|Simplex(단방향)|	한쪽만 전송, 한쪽만 수신|	TV, 라디오|	→|
|Half-Duplex(반이중)|	양방향 가능 but 동시에 불가능|	무전기|	→ ← (순서대로)|
|Full-Duplex(전이중)|	양방향 동시에 가능|	전화, UART(Full-Duplex)|→ ← (동시)|
***







