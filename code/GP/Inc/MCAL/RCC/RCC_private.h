#include"../Inc/LIB/STD_TYPES.h"
#include"../Inc/LIB/BIT_MATH.h"

#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_
#define RCC ((volatile RCC_t *)0x40021000)
typedef struct
{
	volatile u32 CR;
	volatile u32 CFGR;
	volatile u32 CIR;
	volatile u32 APB2RSTR;
	volatile u32 APB1RSTR;
	volatile u32 AHBENR;
	volatile u32 APB2ENR;
	volatile u32 APB1ENR;
	volatile u32 BDCR;
	volatile u32 CSR;

}RCC_t;
#define HSI_ON_BIT 0
#define HSE_ON_BIT 16
#define PLL_ON_BIT 24


#define HSI_RDY_BIT 1
#define HSE_RDY_BIT 17
#define PLL_RDY_BIT 25


#define SYSTEM_CLOCK_BIT0 0
#define SYSTEM_CLOCK_BIT1 1

#define BUSES_PRESCALER_RESET_MASK 1023
#define AHB_PRESCALER_FBIT 4
#define APB1_PRESCALER_FBIT 8
#define APB2_PRESCALER_FBIT 11

#define PLLSRC_BIT 16
#define PLLXTPRE_BIT 17

#define MULTIPLICATION_FACTOR_RESET_MASK 0b1111 << 18
#define PLL_MUL_FBIT 18

#define AFIOEN_Bit 0
#define IOPAEN_Bit 2
#define IOPBEN_Bit 3
#define IOPCEN_Bit 4
#define IOPDEN_Bit 5
#define IOPEEN_Bit 6
#define IOPFEN_Bit 7
#define IOPGEN_Bit 8
#define ADC1EN_Bit 9
#define ADC2EN_Bit 10
#define TIM1EN_Bit 11
#define SPI1EN_Bit 12
#define TIM8EN_Bit 13
#define USART1EN_Bit 14
#define ADC3EN_Bit 15
#define TIM9EN_Bit 19
#define TIM10EN_Bit 20
#define TIM11EN_Bit 21





#endif
