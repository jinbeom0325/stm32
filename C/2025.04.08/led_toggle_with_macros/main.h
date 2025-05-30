#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>

#define ADDR_REG_AHB1ENR ((RCC_AHB1ENR_t*) 0x40023830) //매크로 사용
#define ADDR_REG_GPIOA_MODE ((GPIOx_MODER_t*)  0x40020000)
#define ADDR_REG_GPIOA_OD ((GPIOx_ODR_t*)   0x40020014)

#define CLOCK_ENABLE (1)
#define MODE_CONF_OUTPUT (1)
#define PIN_STATE_HIGH (1)
#define PIN_STAGE_LOW (0)

#define DELAY_COUNT (300000UL) //부호없는 long 32bit값으로 처리

// RCC AHB1ENR 구조체
typedef struct
{
	uint32_t gpioa_en		:1;
	uint32_t gpiob_en		:1;
	uint32_t gpioc_en		:1;
	uint32_t gpiod_en		:1;
	uint32_t gpioe_en		:1;
	uint32_t reserved1		:2;
	uint32_t gpioh_en		:1;
	uint32_t reserved2		:4;
	uint32_t crc_en			:1;
	uint32_t reserved3		:7;
	uint32_t dma1_en		:1;
	uint32_t dma2_en		:1;
	uint32_t reserved4		:9;
} RCC_AHB1ENR_t;

// GPIOx_MODER 구조체
typedef struct
{
	uint32_t pin_0		:2;
	uint32_t pin_1		:2;
	uint32_t pin_2		:2;
	uint32_t pin_3		:2;
	uint32_t pin_4		:2;
	uint32_t pin_5		:2;
	uint32_t pin_6		:2;
	uint32_t pin_7		:2;
	uint32_t pin_8		:2;
	uint32_t pin_9		:2;
	uint32_t pin_10		:2;
	uint32_t pin_11		:2;
	uint32_t pin_12		:2;
	uint32_t pin_13		:2;
	uint32_t pin_14		:2;
	uint32_t pin_15		:2;
} GPIOx_MODER_t;

// GPIOx_ODR 구조체
typedef struct
{
	uint32_t pin_0		:1;
	uint32_t pin_1		:1;
	uint32_t pin_2		:1;
	uint32_t pin_3		:1;
	uint32_t pin_4		:1;
	uint32_t pin_5		:1;
	uint32_t pin_6		:1;
	uint32_t pin_7		:1;
	uint32_t pin_8		:1;
	uint32_t pin_9		:1;
	uint32_t pin_10		:1;
	uint32_t pin_11		:1;
	uint32_t pin_12		:1;
	uint32_t pin_13		:1;
	uint32_t pin_14		:1;
	uint32_t pin_15		:1;
	uint32_t reserved	:16;
} GPIOx_ODR_t;


#endif /* MAIN_H_ */
