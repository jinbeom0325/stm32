### GpioInputOutput
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
