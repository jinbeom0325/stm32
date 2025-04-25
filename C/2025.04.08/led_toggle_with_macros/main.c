#include "main.h"


int main(void)
{
	RCC_AHB1ENR_t volatile *const pClkCtrlReg   = ADDR_REG_AHB1ENR;  // RCC AHB1ENR
	GPIOx_MODER_t  volatile *const pPortAModeReg = ADDR_REG_GPIOA_MODE;  // GPIOA MODER
	GPIOx_ODR_t   volatile *const pPortAOutReg  = ADDR_REG_GPIOA_OD;  // GPIOA ODR

	// 1. GPIOA 클럭 Enable
	pClkCtrlReg->gpioa_en = CLOCK_ENABLE;

	// 2. PA5를 Output 모드로 설정
	pPortAModeReg->pin_5 = MODE_CONF_OUTPUT;

	while(1)
	{
		// PA5 High (LED ON)
		pPortAOutReg->pin_5 = PIN_STATE_HIGH;

		for(uint32_t i=0 ; i<DELAY_COUNT ; i++);

		// PA5 Low (LED OFF)
		pPortAOutReg->pin_5 = PIN_STAGE_LOW;

		for(uint32_t i=0 ; i<DELAY_COUNT ; i++);
	}
}
