/*
 * DIO_Module.h
 *
 * Created: 8/7/2021 11:35:17 AM
 *  Author: Shehab
 */ 


#ifndef DIO_H_
#define DIO_H_

#include "../../Common/DataType.h"


typedef enum
{
	INPUT,
    OUTPUT
}DIO_DIR_en;

typedef enum
{
	PORT_A,
	PORT_B,
	PORT_C,
	PORT_D

}DIO_PORT_en;

typedef enum
{
	PIN_0,
	PIN_1,
	PIN_2,
	PIN_3,
	PIN_4,
	PIN_5,
	PIN_6,
	PIN_7

}DIO_PIN_en;



void DIO_SetDir( DIO_PORT_en portNUmber , DIO_PIN_en pinNumber , DIO_DIR_en dir);
uint8 DIO_GetValue( DIO_PORT_en portNUmber , DIO_PIN_en pinNumber );
void DIO_SetHigh( DIO_PORT_en portNUmber , DIO_PIN_en pinNumber );
void DIO_SetLow( DIO_PORT_en portNUmber , DIO_PIN_en pinNumber );
void DIO_TOGGLE(DIO_PORT_en portNUmber,DIO_PIN_en pinNumber);



#endif /* DIO_MODULE_H_ */
