
#include "../Inc/LIB/BIT_MATH.h"
#include "../Inc/LIB/STD_TYPES.h"

#include "../Inc/HAL/LCD/LCD_interface.h"
#include "../Inc/HAL/LCD/LCD_private.h"
#include "../Inc/HAL/LCD/LCD_config.h"

#include "../Inc/MCAL/DIO/DIO_interface.h"
#include "../Inc/MCAL/TIM/T2DELAY_interface.h"

void HLCD_voidInit()
{
	MGPIO_voidSetPortDirection(LCD_DATA_PORT,OUTPUT_SPEED_2MHZ_PP_PORT);
	MGPIO_voidSetPinDirection(LCD_CONTROL_PORT, RS, OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(LCD_CONTROL_PORT, RW, OUTPUT_SPEED_2MHZ_PP);
	MGPIO_voidSetPinDirection(LCD_CONTROL_PORT, EN, OUTPUT_SPEED_2MHZ_PP);

	MTIMER2_voidStartDealyInMicroSeconds(30000);
	HLCD_voidSendCommand(LCD_RETURN_HOME);
	MTIMER2_voidStartDealyInMicroSeconds(15000);
	HLCD_voidSendCommand(LCD_SET_8_BITES_2_LINES);
	MTIMER2_voidStartDealyInMicroSeconds(1000);
	HLCD_voidSendCommand(LCD_DISPLAY_ON);
	MTIMER2_voidStartDealyInMicroSeconds(1000);
	HLCD_voidSendCommand(LCD_CLR);
	MTIMER2_voidStartDealyInMicroSeconds(15000);
	HLCD_voidSendCommand(LCD_ENTRY_MODE);
	MTIMER2_voidStartDealyInMicroSeconds(2000);
}
void HLCD_voidSendCommand(u8 Copy_u8CmdID)
{
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, RS, GPIO_LOW);

	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, RW, GPIO_LOW);

	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, EN, GPIO_HIGH);

	MGPIO_voidSetPortValue(LCD_DATA_PORT, Copy_u8CmdID);

	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, EN, GPIO_LOW);

	MTIMER2_voidStartDealyInMicroSeconds(10000);

	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, EN, GPIO_HIGH);

	MTIMER2_voidStartDealyInMicroSeconds(20000);

}
void HLCD_voidDisplayClear()
{
	HLCD_voidSendCommand(LCD_CLR);
}
void HLCD_voidGoTo(u8 Copy_u8RowID, u8 Copy_u8COLID)
{
	u8 Local_address = 0;
	switch  (Copy_u8RowID)
	{
	case 0:
		Local_address = Copy_u8COLID;
		break;
	case 1:
		Local_address = Copy_u8COLID + 0x40;
		break;
	case 2:
		Local_address = Copy_u8COLID + 0x10;
		break;
	case 3:
		Local_address = Copy_u8COLID + 0x50;
		break;
	}
	HLCD_voidSendCommand(Local_address | LCD_CURSOR_OFFSET);
}
void HLCD_voidSendChar(u8 Copy_u8Data)
{
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, RS, GPIO_HIGH);
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, RW, GPIO_LOW);
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, EN, GPIO_HIGH);
	MGPIO_voidSetPortValue(LCD_DATA_PORT, Copy_u8Data);
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, EN, GPIO_LOW);
	MTIMER2_voidStartDealyInMicroSeconds(5000);
	MGPIO_voidSetPinValue(LCD_CONTROL_PORT, EN, GPIO_HIGH);
	MTIMER2_voidStartDealyInMicroSeconds(1000);
}
void HLCD_voidSendString(u8 *ptr_u8String)
{
	u8 Index = 0;
	while (ptr_u8String[Index] != '\0')
	{
		HLCD_voidSendChar(ptr_u8String[Index]);
		Index++;
		MTIMER2_voidStartDealyInMicroSeconds(1000);
	}
}
void HLCD_voidNumberDisplay(u8 Copy_u8Number)
{
	s8 * Local_ptr_str[16]={0};
	itoa (Copy_u8Number, (char *)Local_ptr_str, 10);
	HLCD_voidSendString((u8 *)Local_ptr_str);
}
