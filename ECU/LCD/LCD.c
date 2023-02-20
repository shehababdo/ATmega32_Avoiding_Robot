
/*
1- Macros
2- Implementation of functions
*/
#include "LCD_CONFIG.h"
#include "LCD.h"
#include <util/delay.h>
#include "string.h"
#include <avr/io.h>
/***************************************************************************************/
/********************************** Macros *********************************************/
/***************************************************************************************/
#define LCD_HOME_CMD  			 0X02 		 // return cursor to first position on first line

#define LCD_CLEAR_CMD  			 0X01 		 // replace all characters with ASCII 'space'

#define LCD_DISPLY_ON      		 0x04         // Display on
#define LCD_DISPLY_OFF     		 0x00         // Display off
#define LCD_CURSER_ON      		 0x02         // cursor on
#define LCD_CURSER_OFF     		 0x00         // cursor off
#define LCD_BLINK_ON       		 0x01         // cursor blink on
#define LCD_BLINK_OFF      		 0x00         // cursor blink off
#define LCD_CONTROL_OPCODE 		 0x08
#define LCD_CONTROL_CMD    		 ( LCD_CONTROL_OPCODE | LCD_DISPLY_ON | LCD_CURSER_OFF | LCD_BLINK_OFF )

#define LCD_8_BIT_DATA           0x10         // 8-bit data
#define LCD_4_BIT_DATA           0x00         // 4-bit data
#define LCD_2_LINE               0x08         // 2-line display
#define LCD_1_LINE               0x00         // 1-line display
#define LCD_FONT_BOLD            0x04         // 5 x 10 font
#define LCD_FONT_NOT_BOLD        0x00         // 5 x 8 font
#define LCD_FUNCTION_SET_OPCODE  0x20
#define LCD_FUNCTION_SET_CMD     ( LCD_FUNCTION_SET_OPCODE | LCD_4_BIT_DATA | LCD_2_LINE | LCD_FONT_NOT_BOLD )

#define LCD_RIGHT_SHIFT       	 0x02         // shift cursor from left to right on read/write
#define LCD_LIFT_SHIFT       	 0x00         // shift cursor from right TO left on read/write
#define LCD_STOP_SHIFT      	 0x01
#define LCD_MODE_OPCODE 		 0x03
#define LCD_MODE_CMD    		 ( LCD_MODE_OPCODE | LCD_MODE_OPCODE)


void LCD_Init(void)/*Initialize LCD*/
{
	/*Define direction for command pins*/
	DIO_SetDir(LCD_CMD_PORT, LCD_RS, LCD_OUTPUT);
	DIO_SetDir(LCD_CMD_PORT, LCD_RW, LCD_OUTPUT);
	DIO_SetDir(LCD_CMD_PORT, LCD_EN, LCD_OUTPUT);
	/*Define direction for data pins*/
	DIO_SetDir(LCD_DTA_PORT, LCD_D4, LCD_OUTPUT);
	DIO_SetDir(LCD_DTA_PORT, LCD_D5, LCD_OUTPUT);
	DIO_SetDir(LCD_DTA_PORT, LCD_D6, LCD_OUTPUT);
	DIO_SetDir(LCD_DTA_PORT, LCD_D7, LCD_OUTPUT);
	/*LCD controller is slower than MC speed*/
	/* Delay 30ms to ensure the initialization of the LCD driver */
	_delay_ms(30);

	/* Return Home  */
	LCD_WriteCMD(LCD_HOME_CMD);
	_delay_ms(15);

	/* Function Set  */
	LCD_WriteCMD(LCD_FUNCTION_SET_CMD);
	_delay_ms(1);

	/* Display ON / OFF Control */
	LCD_WriteCMD(LCD_CONTROL_CMD);
	_delay_ms(1);

	/* Clear Display */
	LCD_WriteCMD(LCD_CLEAR_CMD);
	_delay_ms(15);

	/* Entry Mode Set  */
	LCD_WriteCMD(LCD_MODE_CMD);
	_delay_ms(2);
	/*
//	we can write the values direct without MACROS
//	LCD_WriteCMD(0x02);
//	LCD_WriteCMD(0x28);
//	LCD_WriteCMD(0x0C);
//	LCD_WriteCMD(0x01);
//	LCD_WriteCMD(0x06);
	*/
}

void LCD_WriteCMD(uint8 cmd)   /*Write command inside control register*/
{
	/*RS is logic(0) to write inside control register*/
	DIO_SetLow(LCD_CMD_PORT, LCD_RS);
	/*RW is logic(0) to write on LCD*/
	DIO_SetLow(LCD_CMD_PORT, LCD_RW);
	/*To be sure of enable state before start operation*/
	DIO_SetLow(LCD_CMD_PORT, LCD_EN);
	/*Send high nibble of command*/
	PORTA = (cmd & 0xF0) | (PORTA & 0x0F);
	DIO_SetHigh(LCD_CMD_PORT, LCD_EN);
	_delay_ms(1);
	DIO_SetLow(LCD_CMD_PORT, LCD_EN);
	/*send low nibble of command*/
	PORTA = (cmd << 4) | (PORTA & 0x0F);
	DIO_SetHigh(LCD_CMD_PORT, LCD_EN);
	_delay_ms(1);
	DIO_SetLow(LCD_CMD_PORT, LCD_EN);
	/*Delay for 2 millisecond*/
	_delay_ms(2);
}
void LCD_WriteChar(uint8 data)/*write data inside data register*/
{
	/*RS is logic(1) to write inside data register*/
	DIO_SetHigh(LCD_CMD_PORT, LCD_RS);  // DATA INPUT ---> RS HIGH
	/*RW is logic(0) to write on LCD*/
	DIO_SetLow(LCD_CMD_PORT, LCD_RW);   // 0 ---> WRITE 
	/*To be sure of enable state before start operation*/
	DIO_SetLow(LCD_CMD_PORT, LCD_EN);
	/*Send high nibble of command*/
	PORTA = (data & 0xF0) | (PORTA & 0x0F);
	DIO_SetHigh(LCD_CMD_PORT, LCD_EN);
	_delay_ms(1);
	DIO_SetLow(LCD_CMD_PORT, LCD_EN);
	/*send low nibble of command*/
	PORTA = (data << 4) | (PORTA & 0x0F);
	DIO_SetHigh(LCD_CMD_PORT, LCD_EN);
	_delay_ms(1);
	DIO_SetLow(LCD_CMD_PORT, LCD_EN);
	/*Delay for 2 millisecond*/
	_delay_ms(2);
}
void LCD_WriteString(char string[]) /*write string on screen*/
{
	while(*string != '\0')
	{
		LCD_WriteChar(*string);
	//	_delay_ms(10);
		string++;
	}
	
}
void LCD_Clear(void)/*Clear data display on screen*/
{
	LCD_WriteCMD(0x01);
	_delay_ms(15);
}

void LCD_WriteAtPosition(uint8 lineNumber , uint8 digitNumber)
{
	if ( (digitNumber>0 && digitNumber<=15) && (lineNumber>1 && lineNumber<=2) )
	{
	    switch(lineNumber)
	    {
		    case 1:
		    	LCD_WriteCMD(digitNumber+127);   // 127 (0x80) if the offset address of line 1 in DDRAM at LM06
		    break;
		    case 2:
		    	LCD_WriteCMD(digitNumber+191);	// 191 (0xBF) if the offset address of line 1 in DDRAM at LM06
		    break;
		    default:
		    break;
	    }
	}
}
void LCD_WriteINTEGER(uint32 integer)
{
	uint32 Revers_num = 0;
	uint8 displayed_num = 0;
	uint32 multiplier = 1, i = 0;
	if(integer == 0)
	{
		LCD_WriteChar('0');
	}
	else if(integer < 0)
	{
		LCD_WriteChar('-');
		integer *= -1;
	}
	
	while (integer != 0)
	{
		Revers_num = (Revers_num * 10) + integer % 10;
		if (Revers_num == 0)
		multiplier *= 10;
		integer /= 10;
	}
	while (Revers_num != i)
	{
		displayed_num = Revers_num % 10;
		LCD_WriteChar(displayed_num + 48);
		Revers_num/=10;
		if (Revers_num == 0 && multiplier >= 10)
		{
			i = 1;
			Revers_num = multiplier;
		}
	}
}
