/*
 * DIO_Module.c
 *
 * Created: 8/7/2021 11:34:58 AM
 *  Author: Shehab
 */ 
#include "DIO.h"
#include <avr/io.h>

#include "../../Common/BitMath.h"


void DIO_SetDir( DIO_PORT_en portNUmber , DIO_PIN_en pinNumber , DIO_DIR_en dir)
{
	if( dir == OUTPUT)
	{
		if( portNUmber == PORT_A)
		{
			set_bit(DDRA , pinNumber);
		}
		else if( portNUmber == PORT_B)
		{
			set_bit(DDRB  , pinNumber);
		}
		else if( portNUmber == PORT_C)
		{
			set_bit(DDRC  , pinNumber);
		}
		else if( portNUmber == PORT_D)
		{
			set_bit(DDRD  , pinNumber);
		}
		
	}
	else if( dir == INPUT)
	{
		if( portNUmber == PORT_A)
		{
			clr_bit(DDRA , pinNumber);
		}
		else if( portNUmber == PORT_B)
		{
			clr_bit(DDRB  , pinNumber);
		}
		else if( portNUmber == PORT_C)
		{
			clr_bit(DDRC  , pinNumber);
		}
		else if( portNUmber == PORT_D)
		{
			clr_bit(DDRD  , pinNumber);
		}
	}
	
}

uint8 DIO_GetValue( DIO_PORT_en portNUmber , DIO_PIN_en pinNumber )
{
	int var = 0;
		if( portNUmber == PORT_A)
		{
			var = get_bit(PINA , pinNumber);
		}
		else if( portNUmber == PORT_B)
		{
			var = get_bit(PINB  , pinNumber);
		}
		else if( portNUmber == PORT_C)
		{
			var = get_bit(PINC  , pinNumber);
		}
		else if( portNUmber == PORT_D)
		{
			var =get_bit(PIND  , pinNumber);
		}
		
		return var;
	
}

void DIO_SetHigh( DIO_PORT_en portNUmber , DIO_PIN_en pinNumber )
{
	if( portNUmber == PORT_A)
	{
		set_bit(PORTA , pinNumber);
	}
	else if( portNUmber == PORT_B)
	{
		set_bit(PORTB  , pinNumber);
	}
	else if( portNUmber == PORT_C)
	{
		set_bit(PORTC  , pinNumber);
	}
	else if( portNUmber == PORT_D)
	{
		set_bit(PORTD  , pinNumber);
	}
	
}

void DIO_SetLow( DIO_PORT_en portNUmber , DIO_PIN_en pinNumber )
{
		if( portNUmber == PORT_A)
		{
			clr_bit(PORTA , pinNumber);
		}
		else if( portNUmber == PORT_B)
		{
			clr_bit(PORTB  , pinNumber);
		}
		else if( portNUmber == PORT_C)
		{
			clr_bit(PORTC  , pinNumber);
		}
		else if( portNUmber == PORT_D)
		{
			clr_bit(PORTD  , pinNumber);
		}
}

void DIO_TOGGLE(DIO_PORT_en portNUmber,DIO_PIN_en pinNumber)
{
	if (pinNumber==PORT_A)
	{
		toggle_bit(PORTA,pinNumber);
	}
	else if (pinNumber==PORT_B)
	{
		toggle_bit(PORTB,pinNumber);
	}
	else if (pinNumber==PORT_C)
	{
		toggle_bit(PORTC,pinNumber);
	}
	else if (pinNumber==PORT_D)
	{
		toggle_bit(PORTD,pinNumber);
	}
}
