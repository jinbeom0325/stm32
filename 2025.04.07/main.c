#include <stdint.h>
#include <stdio.h>

// global shared variable between main code and ISR
uint8_t volatile g_button_pressed = 0;
uint32_t g_button_press_count = 0;

void button_init(void);

// RCC 레지스터 (Clock 설정)
uint32_t volatile *const pClkCtrlReg        = (uint32_t*) 0x40023830;  // RCC_AHB1ENR
uint32_t volatile *const pClkCtrlRegApb2    = (uint32_t*) 0x40023844;  // RCC_APB2ENR

// GPIOA 레지스터
uint32_t volatile *const pGPIOAModeReg      = (uint32_t*) 0x40020000;  // GPIOA_MODER

// EXTI 레지스터
uint32_t volatile *const pEXTTIPendReg      = (uint32_t*) 0x40013C14;  // EXTI_PR
uint32_t volatile *const pEXTIMaskReg       = (uint32_t*) 0x40013C00;  // EXTI_IMR
uint32_t volatile *const pEXTTIEdgeCtrlReg  = (uint32_t*) 0x40013C08;  // EXTI_RTSR

// NVIC 레지스터
uint32_t volatile *const pNVICIRQEnReg      = (uint32_t*) 0xE000E100;  // NVIC_ISER0


int main(void)
{
	button_init();

	while(1)
	{
		// Disable interrupt
		*pEXTIMaskReg &= ~(1 << 0);

		if(g_button_pressed)
		{
			// Debouncing delay
			for(uint32_t volatile i=0; i<250000; i++);

			g_button_press_count++;
			printf("Button pressed : %lu\n", g_button_press_count);
			g_button_pressed = 0;
		}

		// Enable interrupt
		*pEXTIMaskReg |= (1 << 0);
	}
}


void button_init(void)
{
	// GPIOA 클럭 enable
	*pClkCtrlReg |= (1 << 0);

	// SYSCFG 클럭 enable
	*pClkCtrlRegApb2 |= (1 << 14);

	// GPIOA Pin0 (Button) 입력 모드 (00)
	*pGPIOAModeReg &= ~(3 << (0 * 2));

	// Rising edge trigger 설정
	*pEXTTIEdgeCtrlReg |= (1 << 0);

	// Interrupt Mask 설정
	*pEXTIMaskReg |= (1 << 0);

	// NVIC EXTI0 IRQ Enable (IRQ#6)
	*pNVICIRQEnReg |= (1 << 6);
}


// ISR : EXTI0 Interrupt Handler
void EXTI0_IRQHandler(void)
{
	g_button_pressed = 1;

	// Pending Bit Clear
	*pEXTTIPendReg |= (1 << 0);
}
