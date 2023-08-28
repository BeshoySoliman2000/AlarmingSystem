/*
 * PB_Config.c
 *
 *  Created on: Aug 24, 2022
 *      Author: Asmaa Hashim
 */

#include "../Inc/MCAL/DIO/DIO_interface.h"


#include "../Inc/HAL/Push_Button/PB_Interface.h"


PB_info PB_config[MAX_NUM_PB]={
		                        {GPIOA , PIN5 , Released , {RELEASED_VOLTAGE , RELEASED_VOLTAGE }},
		                        {GPIOA , PIN6 , Released , {RELEASED_VOLTAGE , RELEASED_VOLTAGE }},
		                        {GPIOA , PIN7 , Released , {RELEASED_VOLTAGE , RELEASED_VOLTAGE }},
		                        {GPIOA , PIN8 , Released , {RELEASED_VOLTAGE , RELEASED_VOLTAGE }},
		                        {GPIOA , PIN9 , Released , {RELEASED_VOLTAGE , RELEASED_VOLTAGE }},
		                        {GPIOA , PIN10 , Released , {RELEASED_VOLTAGE , RELEASED_VOLTAGE }},
		                        {GPIOA , PIN11 , Released , {RELEASED_VOLTAGE , RELEASED_VOLTAGE }},


};
