
/******************************** INCLUDES********************/
/******************************** LIB INCLUDE********************/
#include "../Inc/LIB/BIT_MATH.h"
#include "../Inc/LIB/STD_TYPES.h"
/******************************** HAL INCLUDE********************/
#include "../Inc/HAL/LCD/LCD_interface.h"
#include "../Inc/HAL/Push_Button/PB_Interface.h"
/******************************** MCAL INCLUDE ********************/
#include "../Inc/MCAL/SYSTIC/STK_interface.h"
#include "../Inc/MCAL/RCC/RCC_interface.h"
#include "../Inc/MCAL/DIO/DIO_interface.h"
#include "../Inc/MCAL/TIM/T2DELAY_interface.h"
/******************************** SERVICE INCLUDE ********************/
#include "../Inc/SERVICE/RTOS/RTOS_interface.h"

static volatile u8 SEC =0;//allocating integer memory for storing seconds

static volatile u8 MIN =0;// allocating integer memory for storing minutes

static volatile u8 HOU =0;// allocating integer memory for storing hours
/****************************************/

static volatile u8 ALARM_SEC =0;//allocating integer memory for storing alarm seconds

static volatile u8 ALARM_MIN =0;// allocating integer memory for storing alarm minutes

static volatile u8 ALARM_HOU =0;// allocating integer memory for storing alarm hours

/************************************************************************************************************************/

/******************************** SEC _INCREMENT********************/
u8 BUTTON1  =0;
/******************************** SEC _DECREMENT********************/
u8 BUTTON2 = 0;
/******************************** MIN _INCREMENT********************/
u8 BUTTON3 = 0;
/******************************** MIN _DECREMENT********************/
u8 BUTTON4 = 0;
/******************************** HOURS _INCREMENT********************/
u8 BUTTON5 = 0;
/******************************** HORS _DECREMENT********************/
u8 BUTTON6 = 0;
/******************************** RESET ********************/
u8 BUTTON7 = 0;
/************************************************************************************************************************/


/******************************************************************************/
/*Function: ALARM_START                          			                   */
/*I/P Parameters: void  		            						          */
/*Returns:it returns void                            				          */
/*Desc:This Function starts and sets the alarms         					  */
/******************************************************************************/

void ALARM_START()
{
	/***** RESET BUTTON ******/
	BUTTON1=MGPIO_u8GetPinValue(GPIOA, PIN5);
	BUTTON2=MGPIO_u8GetPinValue(GPIOA, PIN6);
	BUTTON3=MGPIO_u8GetPinValue(GPIOA, PIN7);
	BUTTON4=MGPIO_u8GetPinValue(GPIOA, PIN8);
	BUTTON5=MGPIO_u8GetPinValue(GPIOA, PIN9);
	BUTTON6=MGPIO_u8GetPinValue(GPIOA, PIN10);
	BUTTON7=MGPIO_u8GetPinValue(GPIOA, PIN11);


	if (BUTTON7==Pre_pressed)
	{

		ALARM_SEC=0;
		ALARM_MIN=0;
		ALARM_HOU=0;
		MGPIO_voidSetPinValue(GPIOA, PIN14, GPIO_LOW);
	}
	if (BUTTON1==Pre_pressed)
	{

		if (ALARM_SEC == 60)
				{
					ALARM_SEC = 0;
					HLCD_voidDisplayClear();
				}
		else
		{

				ALARM_SEC ++;
		}
	}
	if (BUTTON2 == Pre_pressed)
	{

		if (ALARM_SEC == 0)
		{

			ALARM_SEC=59;
		}
		else
		{

			if (ALARM_SEC==10)
			{
				HLCD_voidDisplayClear();
				ALARM_SEC --;
			}
			else
			{

	    ALARM_SEC --;
			}
		}
	}
	if (BUTTON3 == Pre_pressed)
	{

		if (ALARM_MIN == 60)
		{
			ALARM_MIN = 0;
			HLCD_voidDisplayClear();
		}
		else
		{

		    ALARM_MIN ++;
		}
	}
	if (BUTTON4 == Pre_pressed)
	{

		if (ALARM_MIN == 0)
			{

			ALARM_MIN=59;
			}
			else
			{
				if (ALARM_MIN==10)
							{
								HLCD_voidDisplayClear();
								ALARM_MIN --;
							}
							else
							{

					    ALARM_MIN --;
							}
			}
	}
	if (BUTTON5 == Pre_pressed)
	{

		if (ALARM_HOU == 24)
		{
			ALARM_HOU = 0;
			HLCD_voidDisplayClear();
		}
		else
		{

			ALARM_HOU ++;
		}
	}
	if (BUTTON6 == Pre_pressed)
	{

		if (ALARM_HOU == 0)
			{
			ALARM_HOU=23;
			}
			else
			{
				if (ALARM_HOU==10)
							{
								HLCD_voidDisplayClear();
								ALARM_HOU --;
							}
							else
							{

					    ALARM_HOU --;
							}
			}
	}
		}
/******************************************************************************/
/*Function : Counter                        			                      */
/*I/P Parameters: void  		            						          */
/*Returns:it returns void                            				          */
/*Desc:This Function starts & updates Clock       					          */
/******************************************************************************/
void  Counter()   // counter compare match


	{

	if (SEC<60)

	{

		SEC++;

	}

	if (SEC==60)

	{

	if (MIN<60)

	{

		MIN++;

	}

	SEC=0;
	HLCD_voidDisplayClear();

	}

	if (MIN==60)

	{

	if (HOU<24)

	{

		HOU++;

	}

	MIN=0;
	HLCD_voidDisplayClear();

	}

	if (HOU==24)

	{

		HOU=0;
	HLCD_voidDisplayClear();

	}

	}
/******************************************************************************/
/*Function:  DisplayClock                       			                  */
/*I/P Parameters: void  		            						          */
/*Returns:it returns void                            				          */
/*Desc:This Function Display clock on 2*16 LCD        					      */
/******************************************************************************/
void DisplayClock()
{
	    Counter();
		HLCD_voidGoTo(0, 0);
		HLCD_voidSendString("CLOCK");
		HLCD_voidGoTo(0, 6);
		HLCD_voidNumberDisplay(HOU);
		HLCD_voidGoTo(0, 8);
		HLCD_voidSendChar(':');
		HLCD_voidGoTo(0,9 );
		HLCD_voidNumberDisplay(MIN);
		HLCD_voidGoTo(0,11 );
		HLCD_voidSendChar(':');
		HLCD_voidGoTo(0, 12);
		HLCD_voidNumberDisplay(SEC);
}
/******************************************************************************/
/*Function:  DisplaySetAlarm                      			                  */
/*I/P Parameters: void  		            						          */
/*Returns:it returns void                            				          */
/*Desc:This Function Display alarm on 2*16 LCD        					      */
/******************************************************************************/
void DisplaySetAlarm()
{
	    ALARM_START();
		HLCD_voidGoTo(1, 0);
		HLCD_voidSendString("ALARM");
		HLCD_voidGoTo(1, 6);
		HLCD_voidNumberDisplay(ALARM_HOU);
		HLCD_voidGoTo(1, 8);
		HLCD_voidSendChar(':');
		HLCD_voidGoTo(1,9 );
		HLCD_voidNumberDisplay(ALARM_MIN);
		HLCD_voidGoTo(1,11 );
		HLCD_voidSendChar(':');
		HLCD_voidGoTo(1, 12);
		HLCD_voidNumberDisplay(ALARM_SEC);
}
/******************************************************************************/
/*Function: Start_Alarming_Task                   			                  */
/*I/P Parameters: void  		            						          */
/*Returns:it returns void                            				          */
/*Desc:This Function start alarm alert (Buzzer)       					      */
/******************************************************************************/
void Start_Alarming_Task(void)
{
	static u8 counter_seconds = 0;
	static u8 flag = 0;
	if((ALARM_HOU == HOU) && (ALARM_MIN == MIN) && (ALARM_SEC == SEC))
	{
		if ((SEC==0)&&(MIN==0)&&HOU==0)
		{
			MGPIO_voidSetPinValue(GPIOA , PIN14  , GPIO_LOW);
		}
		else
		{
			MGPIO_voidSetPinValue(GPIOA , PIN14  , GPIO_HIGH);
						/*ALARM_HOU=0;
						ALARM_MIN=0;
						ALARM_SEC=0;*/
						flag=1;
		}

	}
	if(flag == 1 && counter_seconds < 30)
	{
		counter_seconds++;
	}
	if(counter_seconds == 30)
	{
		MGPIO_voidSetPinValue(GPIOA , PIN14  , GPIO_LOW);
		counter_seconds = 0;
		flag = 0;
	}
}

int main(void)
{
	     /******************** Rcc_ init _HSI***************************/
		MRCC_voidInit();
		/******************* RCC PORTA INIT ***************************/
		MRCC_voidPerClock_State(APB2, IOPA_PERIPHERAL, PClock_enable);
		/******************* RCC PORTB INIT ***************************/
		MRCC_voidPerClock_State(APB2, IOPB_PERIPHERAL, PClock_enable);
		/******************* RCC TIMER2 INIT ***************************/
		MRCC_voidPerClock_State(APB1, TIM2_PERIPHERAL, PClock_enable);
		/*******************LCD INIT************************************/
		HLCD_voidInit();
		/******************TIMER 2 INIT ********************************/
		MTIMER2_voidInitTimer2Delay();
		/***************** SYSTIC INIT ********************************/
		MSTK_voidInit();
		/*************BUZZER PIN INIT ********************************/
		MGPIO_voidSetPinDirection(GPIOA, 14, OUTPUT_SPEED_2MHZ_PP);
		/****************PUSH BUTTON INIT ****************************/
		MGPIO_voidSetPinDirection(GPIOA, PIN5, INPUT_PULL_UP_DOWN);
		MGPIO_voidSetPinDirection(GPIOA, PIN6, INPUT_PULL_UP_DOWN);
		MGPIO_voidSetPinDirection(GPIOA, PIN7, INPUT_PULL_UP_DOWN);
		MGPIO_voidSetPinDirection(GPIOA, PIN8, INPUT_PULL_UP_DOWN);
		MGPIO_voidSetPinDirection(GPIOA, PIN9, INPUT_PULL_UP_DOWN);
		MGPIO_voidSetPinDirection(GPIOA, PIN10, INPUT_PULL_UP_DOWN);
		MGPIO_voidSetPinDirection(GPIOA, PIN11, INPUT_PULL_UP_DOWN);

		/*****************RTOS INIT *******************************/
	RTOS_voidInit ();
	RTOS_voidCreateTask (0 , 1000 , DisplayClock        ,  0);
	RTOS_voidCreateTask (2,  20,    HPB_Update          ,  0);
	RTOS_voidCreateTask (1,  1000 , DisplaySetAlarm     ,  0);
	RTOS_voidCreateTask (3,  1000 , Start_Alarming_Task ,  0);


    /* Loop forever */
while (1)
{



}
}
