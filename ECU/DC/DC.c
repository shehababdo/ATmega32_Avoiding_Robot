/*
 * DC.c
 *
 * Created: 2/16/2023 9:38:43 PM
 *  Author: sheha
 */ 
#include "DC.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../Common/CPU_CONFIG.h"
void MOTOR_init()
{
	//LEFT MOTOR
	DIO_SetDir(PORT_A,PIN_0,OUTPUT);
	DIO_SetDir(PORT_A,PIN_1,OUTPUT);
	//RIGHT MOTOR
	DIO_SetDir(PORT_A,PIN_2,OUTPUT);
	DIO_SetDir(PORT_A,PIN_3,OUTPUT);
}
void FORWAED()
{
	DIO_SetHigh(PORT_A,PIN_0);
	DIO_SetLow(PORT_A,PIN_1);
	
	DIO_SetHigh(PORT_A,PIN_2);
	DIO_SetLow(PORT_A,PIN_3);
}
void RIGHT()
{
	DIO_SetHigh(PORT_A,PIN_0);
	DIO_SetLow(PORT_A,PIN_1);
	
	DIO_SetLow(PORT_A,PIN_2);
	DIO_SetLow(PORT_A,PIN_3);
}
void LEFT()
{
	DIO_SetLow(PORT_A,PIN_0);
	DIO_SetLow(PORT_A,PIN_1);
	
	DIO_SetHigh(PORT_A,PIN_2);
	DIO_SetLow(PORT_A,PIN_3);
}