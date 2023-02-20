/*
 * Autonomous Car.c
 *
 * Created: 1/31/2023 2:27:54 PM
 * Author : Shehab
 */ 

#include <avr/io.h>
#include "ECU/SERVO/SERVO.h"
#include "ECU/US/US.h"
#include "ECU/LCD/LCD.h"
#include "ECU/DC/DC.h"
char string1[10];
char string2[10];
char string3[10];
int main(void)
{
	float Rd,Md,Ld,Sl,Sm,Sr;
	servo_init();
	US_Init();
	LCD_Init();
	MOTOR_init();
	
	//WELCOME MASSEGE
	LCD_WriteString("HELLO");
	_delay_ms(500);
	LCD_Clear();
	LCD_WriteString("AUTOUNMOUS CAR");
	LCD_WriteAtPosition(2,1);
	LCD_WriteString("SYSTEM");
	_delay_ms(500);
	LCD_Clear();
	

    while (1) 
    {
		servo_90_anti_clkwise();
		_delay_ms(500);
		Ld=pulse();
		_delay_ms(500);
		servo_zero();
		Ld=pulse();
		
		_delay_ms(500);
		Md=pulse();
		_delay_ms(500);
		Md=pulse();
		_delay_ms(500);
		servo_90_clkwise();
		Rd=pulse();
		_delay_ms(500);
		Rd=pulse();
		_delay_ms(500);
	//	_delay_ms(50);
		dtostrf(Ld, 2, 2, string1);/* distance to string */
		dtostrf(Md, 2, 2, string2);/* distance to string */
		dtostrf(Rd, 2, 2, string3);/* distance to string */
		LCD_WriteString("L dist= ");
		LCD_WriteString(string1);
		_delay_ms(1000);
		LCD_Clear();
		_delay_ms(50);
					
		LCD_WriteString("mid dist= ");
		LCD_WriteString(string2);
		_delay_ms(1000);
		LCD_Clear();
		_delay_ms(50);
					
		LCD_WriteString("R dist= ");
		LCD_WriteString(string3);
		_delay_ms(1000);
		LCD_Clear();
		_delay_ms(50);
		Sl=Sl+Ld;
		Sm=Sm+Md;
		Sr=Sr+Rd;

		if ((Sm>=Sr)&&(Sm>=Sl)&&Sm>=10)
		{
			//GO FOWRARD
			//LCD "FOWRARD"
			LCD_Clear();
			_delay_ms(50);
			LCD_WriteString("GO FOWRARD");
			FORWAED();
			_delay_ms(500);
			LCD_Clear();
		}
		else if ((Sr>=Sm)&&(Sr>=Sl)&&Sm>=10)
		{
			//GO RIGHT
			//LCD "RIGHT"
			LCD_Clear();
			_delay_ms(50);
			LCD_WriteString("TURN RIGHT");
			RIGHT();
			_delay_ms(500);
			LCD_Clear();
		}
		else if ((Sl>=Sm)&&(Sl>=Sr)&&Sl>=10)
		{
			//GO LEFT
			//LCD "LEFT"
			LCD_Clear();
			_delay_ms(50);
			LCD_WriteString("TURN LEFT");
			LEFT();
			_delay_ms(500);
			LCD_Clear();
		}
		Sl=0;Sm=0;Sr=0;Md=0;Rd=0;Ld=0;
    }
}