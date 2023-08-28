#include"../Inc/LIB/STD_TYPES.h"
#include"../Inc/LIB/BIT_MATH.h"
#include "../Inc/MCAL/RCC/RCC_configuration.h"
#include "../Inc/MCAL/RCC/RCC_interface.h"
#include "../Inc/MCAL/RCC/RCC_private.h"
#include "../Inc/MCAL/DIO/DIO_config.h"
#include "../Inc/MCAL/DIO/DIO_interface.h"
#include "../Inc/MCAL/DIO/DIO_private.h"




void MRCC_voidInit(void)
{
#if CLK_SOURCE == HSI
	MRCC_voidClkEnable(HSI);
	while (MRCC_u8CheckClockReady(HSI==NOT_READY));
	MRCC_voidSetBusesPrescalars(AHB_PRESCALER,ABP1_PRESCALER,ABP2_PRESCALER);
	MRCC_voidClkEnable(HSE);
	MRCC_voidClkDisable(HSI);
	MRCC_voidClkEnable(PLL);

#elif CLK_SOURCE == HSE
	MRCC_voidCLKEnable(HSE);
		while (MRCC_voidCheckClockReady(HSE==NOT_READY));
		MRCC_voidSetBusesPrescalars(AHB_PRESCALER,ABP1_PRESCALER,ABP2_PRESCALER);
		MRCC_voidCLKSetCLKSource(HSI);
		MRCC_voidCLKDisnable(HSE);
		MRCC_voidCLKEnable(PLL);
#elif CLK_SOURCE == PLL
#if PLL_SOURCE == HSI
		MRCC_voidSetPLLSource(HSI,HSE_NOT_DIVIDED);
		MRCC_voidCLKEnable(HSI);
		while (MRCC_voidCheckClockReady(HSI==NOT_READY))
			MRCC_voidCLKEnable (HSE);
		while (MRCC_voidCheckClockReady(HSE==NOT_READY))
			MRCC_voidSetCLKSource (HSE);
#elif PLL_SOURCE == HSE
		MRCC_voidSetPLLSource(HSE,PLL_HSE_FACTOR);
		MRCC_voidCLKEnable(HSE);
		while (MRCC_voidCheckClockReady(HSE==NOT_READY))
			MRCC_voidCLKEnable (HSI);
		while (MRCC_voidCheckClockReady(HSI==NOT_READY))
			MRCC_voidSetCLKSource (HSI);
#else
#error Wrong PLL Configurations
#endif
		MRCC_voidSetPLLMulFactor (PLL_MULTIPLICATION_FACTOR);
		MRCC_voidSetBusesPrescaler (AHB_PRESCALER,ABP1_PRESCALER,ABP2_PRESCALER );
		MRCC_voidCLKEnable (PLL);
		while (MRCC_voidCheckClockReady(PLL==NOT_READY))
			MRCC_voidSetCLKSource (PLL);
#if PLL_SOURCE == HSI
	MRCC_voidCLKDisnable(HSE);
#elif PLL_SOURCE == HSE
	MRCC_voidCLKDisable(HSI);
#endif
#else
#error CLOCK Source isn not configured in the right way
#endif
}
void MRCC_voidSetPLLMulFactor (u8 A_u8MulFactor)
{
	RCC->CFGR &= ~(MULTIPLICATION_FACTOR_RESET_MASK);
	RCC->CFGR |= (A_u8MulFactor << PLL_MUL_FBIT);
}
void MRCC_voidSetPLLSource (u8 A_u8CLKSource, u8 A_u8Prescalar)
{
	switch(A_u8CLKSource)
	{
	case HSI:
		CLR_BIT(RCC->CFGR,PLLSRC_BIT);
	break;
	case HSE:
		SET_BIT(RCC->CFGR, PLLSRC_BIT);
		switch(A_u8Prescalar)
		{
		case HSE_NOT_DIVIDED:
			CLR_BIT(RCC->CFGR,PLLXTPRE_BIT);
			break;
		case HSE_DIVIDED:
			SET_BIT(RCC->CFGR,PLLXTPRE_BIT);
			break;
		default:
					break;
		}
		break;
	}
}
void MRCC_voidClkEnable (u8 A_u8CLKSource)
{
	switch(A_u8CLKSource)
	{
	case HSI:
		SET_BIT (RCC->CR, HSI_ON_BIT);
		break;
	case HSE:
		SET_BIT (RCC->CR, HSE_ON_BIT);
		break;
	case PLL:
		SET_BIT (RCC->CR, PLL_ON_BIT);
		break;
	}
}

void MRCC_voidClkDisable (u8 A_u8CLKSource)
{
	switch(A_u8CLKSource)
		{
		case HSI:
			CLR_BIT (RCC->CR, HSI_ON_BIT);
			break;
		case HSE:
			CLR_BIT (RCC->CR, HSE_ON_BIT);
			break;
		case PLL:
			CLR_BIT (RCC->CR, PLL_ON_BIT);
			break;
		}
}
u8 MRCC_u8CheckClockReady (u8 A_u8CLKSource)
{
	u8 local_u8ReadyFlag = 0;
	switch(A_u8CLKSource)
		{
		case HSI:
			local_u8ReadyFlag = GET_BIT (RCC->CR, HSI_RDY_BIT);
			break;
		case HSE:
			local_u8ReadyFlag = GET_BIT (RCC->CR, HSE_RDY_BIT);
			break;
		case PLL:
			local_u8ReadyFlag = GET_BIT (RCC->CR, PLL_RDY_BIT);
			break;
		}
	return local_u8ReadyFlag;
}
void MRCC_voidSetCLKSource (u8 A_u8CLKSource)
{
	switch(A_u8CLKSource)
	{
	case HSI:
		CLR_BIT (RCC->CFGR, SYSTEM_CLOCK_BIT0);
		CLR_BIT (RCC->CFGR, SYSTEM_CLOCK_BIT1);
		break;
	case HSE:
		SET_BIT (RCC->CFGR, SYSTEM_CLOCK_BIT0);
		CLR_BIT (RCC->CFGR, SYSTEM_CLOCK_BIT1);
		break;
	case PLL:
		CLR_BIT (RCC->CFGR, SYSTEM_CLOCK_BIT0);
		SET_BIT (RCC->CFGR, SYSTEM_CLOCK_BIT1);
	}
}
void MRCC_voidSetBusesPrescalars (u8 A_u8AHBPrescalar, u8 A_u8APB1Prescalar, u8 A_u8APB2Prescalar)
{

RCC->CFGR &= ~(BUSES_PRESCALER_RESET_MASK);
RCC->CFGR |= (A_u8AHBPrescalar << AHB_PRESCALER_FBIT );
RCC->CFGR |= (A_u8APB1Prescalar << APB1_PRESCALER_FBIT );
RCC->CFGR |= (A_u8APB2Prescalar << APB2_PRESCALER_FBIT );
}
void 	MRCC_voidPerClock_State(Buses_t A_u8Bus,u8 A_u8Peripheral,PClock_State_t A_u8CLKSignal)
{

	switch (A_u8Bus) {
	            case AHB  :
		        	if(A_u8CLKSignal == PClock_enable)
		        	{
		        		SET_BIT (RCC->AHBENR  , A_u8Peripheral );
		        	}
		        	else if(A_u8CLKSignal == PClock_disable)
		        	{
			        	CLR_BIT (RCC->AHBENR  , A_u8Peripheral );

		        	}
		        	break;

		        case APB1 :
		        	if(A_u8CLKSignal == PClock_enable)
		        	{
		        		SET_BIT (RCC->APB1ENR  , A_u8Peripheral );
		        	}
		        	else if(A_u8CLKSignal == PClock_disable)
		        	{
		        		CLR_BIT (RCC->APB1ENR  , A_u8Peripheral );
		        	}
		        	break;
		        case APB2 :
		        	if(A_u8CLKSignal == PClock_enable)
		        	{
		        		SET_BIT (RCC->APB2ENR  , A_u8Peripheral );
		        	}
		        	else if(A_u8CLKSignal == PClock_disable)
		        	{
		        		CLR_BIT (RCC->APB2ENR  , A_u8Peripheral );
		        	}
		        	break;

		        default       : break;
		      }
	}
