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
