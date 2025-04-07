## F401RE-C04 보드로 LED 코드 연습
***
```c
#include<stdint.h>

int main(void)
{
uint32_t *pClkCtrlReg =   (uint32_t*)0x40023830;   // RCC_AHB1ENR
uint32_t *pPortAModeReg = (uint32_t*)0x40020000;   // GPIOA_MODER
uint32_t *pPortAOutReg  = (uint32_t*)0x40020014;   // GPIOA_ODR

// 1. GPIOA 클럭 Enable (bit 0)
*pClkCtrlReg |= (1 << 0);

// 2. PA5 핀을 Output 모드로 설정
*pPortAModeReg &= ~(3 << (5 * 2)); // 10번째, 11번째 비트 clear
*pPortAModeReg |=  (1 << (5 * 2)); // 10번째 비트 set (01 = output)

while(1)
{
	// LED ON (PA5 HIGH)
	*pPortAOutReg |= (1 << 5);

	for(uint32_t i = 0; i < 100000; i++); // 딜레이

	// LED OFF (PA5 LOW)
	*pPortAOutReg &= ~(1 << 5);

	for(uint32_t i = 0; i < 100000; i++);
}
}
```
***
## const
```c
//포인터가 가리키는 값이 const인 경우
const int *p = &a;
*p = 20;      // 오류: 가리키는 값 변경 불가
p = &b;       // 가능: 다른 주소를 가리킬 수 있음

//포인터 자체가 const인 경우
int * const p = &a;
*p = 20;      // 가능: 가리키는 값은 변경 가능
p = &b;       // 오류: 다른 주소로 변경 불가

//모두 const인 경우
const int * const p = &a;
*p = 20;      // 오류
p = &b;       // 오류

```
***
## F401RE-C04 보드로 LED와 버튼 연습
```c
#include <stdint.h>

int main(void)
{
// RCC AHB1 peripheral clock enable register (RCC_AHB1ENR)
uint32_t volatile *const pClkCtrlReg = (uint32_t *)0x40023830;

// GPIOA - LED
uint32_t volatile *const pPortAModeReg = (uint32_t *)0x40020000;   // MODER 버튼
uint32_t volatile *const pPortAOutReg  = (uint32_t *)0x40020014;   // ODR 입력 오프셋

// GPIOC - Button
uint32_t volatile *const pPortCModeReg = (uint32_t *)0x40020800;   // MODER 버튼
uint32_t const volatile *const pPortCInReg = (uint32_t *)0x40020810; // IDR 출력 오프셋

// Enable clocks 클럭활성화 
*pClkCtrlReg |= (1 << 0);  // GPIOA 핀지우기 
*pClkCtrlReg |= (1 << 2);  // GPIOC 핀지우기

// Set PA5 as output
*pPortAModeReg &= ~(3 << (5 * 2)); //0으로 설정
*pPortAModeReg |=  (1 << (5 * 2)); //10번째 0, 01설정  출력모드 

// Set PC13 as input
*pPortCModeReg &= ~(3 << (13 * 2)); //버튼 0설정 입력모드 


while (1)
{
	uint8_t pinStatus = (uint8_t)((*pPortCInReg >> 13) & 0x1);  // PC13 

	if (pinStatus) //1 버튼 안눌림
		*pPortAOutReg |= (1 << 5);   // LED ON
	else
		*pPortAOutReg &= ~(1 << 5);  // LED OFF
}
}
```


