#include<stdint.h>
#include<stdio.h>

void delay(void)
{
	for(uint32_t i = 0; i < 300000; i++);
}

int main(void)
{
	// GPIOA, GPIOD, RCC Base Address
	uint32_t volatile *const pGPIOAModeReg  = (uint32_t*)(0x40020000);
	uint32_t volatile *const pGPIOAOutReg   = (uint32_t*)(0x40020014);

	uint32_t volatile *const pGPIODModeReg  = (uint32_t*)(0x40020C00);
	uint32_t volatile *const pGPIODInReg    = (uint32_t*)(0x40020C10);
	uint32_t volatile *const pGPIODPUPDReg  = (uint32_t*)(0x40020C0C);

	uint32_t volatile *const pRCC_AHB1ENR   = (uint32_t*)(0x40023800 + 0x30);

	// 1. Clock Enable
	*pRCC_AHB1ENR |= (1 << 0); // GPIOA
	*pRCC_AHB1ENR |= (1 << 3); // GPIOD

	// 2. PA0 ~ PA3 (ROW) Output 설정
	*pGPIOAModeReg &= ~(0xFF << 0); // Clear
	*pGPIOAModeReg |=  (0x55 << 0); // Output Mode

	// 3. PD2 ~ PD5 (COL) Input 설정
	*pGPIODModeReg &= ~(0xFF << 4); // Input Mode 유지

	// 4. PD2 ~ PD5 Pull-up 설정
	*pGPIODPUPDReg &= ~(0xFF << 4); // Clear
	*pGPIODPUPDReg |=  (0x55 << 4); // Pull-up

	while(1)
	{
		// ROW HIGH 초기화
		*pGPIOAOutReg |= 0x0F;

		// R1 LOW (PA0)
		*pGPIOAOutReg &= ~(1 << 0);
		if(!(*pGPIODInReg & (1 << 2))) { delay(); printf("1\n"); }
		if(!(*pGPIODInReg & (1 << 3))) { delay(); printf("2\n"); }
		if(!(*pGPIODInReg & (1 << 4))) { delay(); printf("3\n"); }
		if(!(*pGPIODInReg & (1 << 5))) { delay(); printf("A\n"); }

		*pGPIOAOutReg |= 0x0F;
		// R2 LOW (PA1)
		*pGPIOAOutReg &= ~(1 << 1);
		if(!(*pGPIODInReg & (1 << 2))) { delay(); printf("4\n"); }
		if(!(*pGPIODInReg & (1 << 3))) { delay(); printf("5\n"); }
		if(!(*pGPIODInReg & (1 << 4))) { delay(); printf("6\n"); }
		if(!(*pGPIODInReg & (1 << 5))) { delay(); printf("B\n"); }

		*pGPIOAOutReg |= 0x0F;
		// R3 LOW (PA2)
		*pGPIOAOutReg &= ~(1 << 2);
		if(!(*pGPIODInReg & (1 << 2))) { delay(); printf("7\n"); }
		if(!(*pGPIODInReg & (1 << 3))) { delay(); printf("8\n"); }
		if(!(*pGPIODInReg & (1 << 4))) { delay(); printf("9\n"); }
		if(!(*pGPIODInReg & (1 << 5))) { delay(); printf("C\n"); }

		*pGPIOAOutReg |= 0x0F;
		// R4 LOW (PA3)
		*pGPIOAOutReg &= ~(1 << 3);
		if(!(*pGPIODInReg & (1 << 2))) { delay(); printf("*\n"); }
		if(!(*pGPIODInReg & (1 << 3))) { delay(); printf("0\n"); }
		if(!(*pGPIODInReg & (1 << 4))) { delay(); printf("#\n"); }
		if(!(*pGPIODInReg & (1 << 5))) { delay(); printf("D\n"); }
	}
}
