#include "main.h"

int main(void)
{
	RCC_AHB1ENR_t volatile *const pClkCtrlReg   = (RCC_AHB1ENR_t*) 0x40023830;  // RCC AHB1ENR
	GPIOx_MODER_t  volatile *const pPortAModeReg = (GPIOx_MODER_t*)  0x40020000;  // GPIOA MODER
	GPIOx_ODR_t   volatile *const pPortAOutReg  = (GPIOx_ODR_t*)   0x40020014;  // GPIOA ODR

	// 1. GPIOA 클럭 Enable
	pClkCtrlReg->gpioa_en = 1;

	// 2. PA5를 Output 모드로 설정
	pPortAModeReg->pin_5 = 1;

	while(1)
	{
		// PA5 High (LED ON)
		pPortAOutReg->pin_5 = 1;

		for(uint32_t i=0 ; i<300000 ; i++);

		// PA5 Low (LED OFF)
		pPortAOutReg->pin_5 = 0;

		for(uint32_t i=0 ; i<300000 ; i++);
	}
}
