## GpioInputOutput
```c
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

## UartTx_Polling

|구분|	UART|	USART|
|--|--|--|
|지원 방식|	비동기 통신만 지원|	비동기 + 동기 둘 다 지원|
|클럭 신호(CLK)|	없음|	있음(동기 모드에서 사용)|
|하드웨어 구성|	TX, RX|	TX, RX, (필요시 CLK)|
|속도|	상대적 느림|	동기 모드 시 더 빠름|  
***
|항목|	의미|	설명|
|--|--|--|
|uint32_t BaudRate|	통신 속도|	9600, 115200 같은 초당 비트 전송속도(bps)|
|uint32_t WordLength|	데이터 비트 수|	데이터 길이 (보통 8bit or 9bit)|
|uint32_t StopBits|	스탑 비트 수|	전송 끝 표시 (1bit or 2bit)|
|uint32_t Parity|	패리티 비트 설정|	데이터 오류 검출용 (None, Even, Odd)|
|uint32_t Mode|	동작 모드|	송신(TX), 수신(RX), 둘다(TX_RX)|
|uint32_t CLKPolarity|	클럭 극성|	클럭 idle 상태가 High인지 Low인지|
|uint32_t CLKPhase|	클럭 위상|	클럭의 어느 순간에 데이터 샘플링|
|uint32_t CLKLastBit|	마지막 비트 클럭 출력 여부|	마지막 비트에 클럭 출력할지 여부|
***
|구분|	설명|	예시|	방향|
|--|--|--|--|
|Simplex(단방향)|	한쪽만 전송, 한쪽만 수신|	TV, 라디오|	→|
|Half-Duplex(반이중)|	양방향 가능 but 동시에 불가능|	무전기|	→ ← (순서대로)|
|Full-Duplex(전이중)|	양방향 동시에 가능|	전화, UART(Full-Duplex)|→ ← (동시)|





