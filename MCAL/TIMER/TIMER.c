/*
 * TIMER.c
 *
 *  Created on: Dec 3, 2021
 *      Author: Shehab
 */

#include "TIMER.h"

ptrFunction TMR0_OVF_INT_ISR = NULL, TMR0_OC_INT_ISR = NULL;
ptrFunction TMR2_OVF_INT_ISR = NULL, TMR2_OC_INT_ISR = NULL;

ptrFunction TMR1_ICR_INT_ISR = NULL, TMR1A_OC_INT_ISR = NULL , TMR1B_OC_INT_ISR = NULL;


void TIMER_Init(TIMER_Paramter_t timerCfgParamter)
{
	switch(timerCfgParamter.Timer_Channel)
	{
		case TIMER0:
		{

			// set interrupt
			TIMSK |= (timerCfgParamter.Timer_OVF_Interrupt << TOIE0) |
					(timerCfgParamter.Timer_OCR_Interrupt << OCIE0);

			// enable global interrupt
			if( timerCfgParamter.Timer_OVF_Interrupt || timerCfgParamter.Timer_OCR_Interrupt)
			{
				set_bit(SREG, 7);
			}
			TCCR0 &=~(1 << WGM00) | (1 << WGM01);
				// set prescale , operation mode
			switch(timerCfgParamter.Timer_Mode)
			{
				case NORMAL:
				{
					// set wave generation
				//	TCCR0 |=(0 << WGM00) | (0<< WGM01);
				clr_bit(TCCR0,WGM00);
				clr_bit(TCCR0,WGM01);
					break;
				}

				case CTC:
				{
					// set wave generation
					TCCR0 |=(0 << WGM00) | (1 << WGM01);
					break;
				}
				
				case FAST_PWM:
				{
					// set wave generation
					TCCR0 |=(1 << WGM00) | (1 << WGM01);
					break;
				}
				
				case PWM_PHASE:
				{
					// set wave generation
					TCCR0 |=(1 << WGM00) | (0 << WGM01);
					break;
				}
			

			}
TCCR0 |= ( timerCfgParamter.Timer_Prescale << CS00 )|( timerCfgParamter.COM_Pin << COM00);
			break;
		}

		case TIMER1:
		{
				// set interruptS
				TIMSK |= (timerCfgParamter.Timer_OVF_Interrupt << TOIE1) |
				(timerCfgParamter.Timer_ICR_Interrupt << TICIE1);
				
				
				// enable global interrupt
				if( timerCfgParamter.Timer_OVF_Interrupt || timerCfgParamter.Timer_ICR_Interrupt)
				{
					set_bit(SREG, 7);
				}
				
				switch(timerCfgParamter.Timer1_Mode)
				{
					case normal:
					{
						// set wave generation
// 						TCCR1A |=(0 << WGM10) | (0<< WGM11);
// 						TCCR1B |=(0 << WGM12) | (0<< WGM13);
						clr_bit(TCCR1A,WGM10);
						clr_bit(TCCR1A,WGM11);
						clr_bit(TCCR1B,WGM12);
						clr_bit(TCCR1B,WGM13);

						break;
					}

					case CTC_OCR1A:
					{
						// set wave generation
// 						TCCR1A |=(0 << WGM10) | (0<< WGM11);
// 						TCCR1B |=(1 << WGM12) | (0<< WGM13);
						clr_bit(TCCR1A,WGM10);
						clr_bit(TCCR1A,WGM11);
						set_bit(TCCR1B,WGM12);
						clr_bit(TCCR1B,WGM13);
						break;
					}
					
					case FAST_PWM_ICR:
					{
						// set wave generation
						
// 					TCCR1A |=(0 << WGM10) | (1<< WGM11);
// 					TCCR1B |=(1 << WGM12) | (1<< WGM13);
						clr_bit(TCCR1A,WGM10);
						set_bit(TCCR1A,WGM11);
						set_bit(TCCR1B,WGM12);
						set_bit(TCCR1B,WGM13);
						break;
					}
					
					case FAST_PWM_OCR:
					{
						// set wave generation
// 					TCCR1A |=(1 << WGM10) | (1 << WGM11);
// 					TCCR1B |=(1 << WGM12) | (1 << WGM13);
						set_bit(TCCR1A,WGM10);
						set_bit(TCCR1A,WGM11);
						set_bit(TCCR1B,WGM12);
						set_bit(TCCR1B,WGM13);
						break;
					}
					case FAST_PWM_8bit:
					{
						// set wave generation
// 						TCCR1A |=(1 << WGM10) | (0 << WGM11);
// 						TCCR1B |=(1 << WGM12) | (0 << WGM13);
						set_bit(TCCR1A,WGM10);
						clr_bit(TCCR1A,WGM11);
						set_bit(TCCR1B,WGM12);
						clr_bit(TCCR1B,WGM13);
						break;
					}
				}
				//choosing between channel A|B
				switch(timerCfgParamter.TMR1_Channel)
				{
						
				
					case T1_A :
					{
						TCCR1A |= ( timerCfgParamter.COM_Pin << COM1A0);
						
						
						TIMSK |= (timerCfgParamter.Timer_OCR_Interrupt << OCIE1A);
						break;
					}
					
					case T1_B :
					{
						TCCR1A |= ( timerCfgParamter.COM_Pin << COM1B0);
						
						TIMSK |= (timerCfgParamter.Timer_OCR_Interrupt << OCIE1B);
						break;
					}
				}
				// set pre_scale
				TCCR1B |= ( timerCfgParamter.Timer_Prescale << CS10 ) ;
			break;
		}

		case TIMER2:
		{

			// set pre_scale , operation mode ,and wave generation
			TCCR2 |= ( timerCfgParamter.Timer_Prescale << CS20 ) |
			( timerCfgParamter.COM_Pin << COM20);

			// set interrupt
			TIMSK |= (timerCfgParamter.Timer_OVF_Interrupt << TOIE2) |
			(timerCfgParamter.Timer_OCR_Interrupt << OCIE2);

			// enable global interrupt
			if( timerCfgParamter.Timer_OVF_Interrupt || timerCfgParamter.Timer_OCR_Interrupt)
			{
				set_bit(SREG, 7);
			}
			
			TCCR2 &=~(1 << WGM20) | (1<< WGM21);
			switch(timerCfgParamter.Timer_Mode)
			{
				case NORMAL:
				{
					// set wave generation
					TCCR2 |=(0 << WGM20) | (0<< WGM21);

					break;
				}

				case CTC:
				{
					// set wave generation
					TCCR2 |=(0 << WGM20) | (1 << WGM21);
					break;
				}
				
				case FAST_PWM:
				{
					// set wave generation
					TCCR2 |=(1 << WGM20) | (1 << WGM21);
					break;
				}
				
				case PWM_PHASE:
				{
					// set wave generation
					TCCR2 |=(1 << WGM20) | (0 << WGM21);
					break;
				}

			}

			break;
		}
	}

}

uint16 TIMER_Read_Counter_Value( TMR_Channel_t timerChannel )
{
	uint16 value =0;

	switch(timerChannel)
	{

		case TIMER0 :
		{
			value = TCNT0;
			break;
		}

		case TIMER1 :
		{
			value = TCNT1;
			break;
		}
		
		case TIMER1_A :
		{
			value = TCNT1;
			break;
		}
		
		case TIMER1_B :
		{
			value = TCNT1;
			break;
		}

		case TIMER2 :
		{
            value=TCNT2;
			break;
		}
	}

	return value;

}

void TIMER_Set_Counter_Value( TMR_Channel_t timerChannel , uint16 value)
{
	switch(timerChannel)
	{

		case TIMER0 :
		{
			TCNT0 =(uint8)value ;
			break;
		}

		case TIMER1 :
		{
			TCNT1 =(uint16)value ;
			break;
		}
		
		case TIMER1_A :
		{
			TCNT1 =(uint16)value ;
			break;
		}
		
		case TIMER1_B :
		{
			TCNT1 =(uint16)value ;
			break;
		}

		case TIMER2 :
		{
		   TCNT2 =(uint8)value ;
			break;
		}
	}
}

void TIMER_Set_OCR_Value( TMR_Channel_t timerChannel , uint16 value)
{
	switch(timerChannel)
	{

		case TIMER0 :
		{
			OCR0 =(uint8)value ;
			break;
		}

		case TIMER1_A :
		{
			OCR1A =(uint16)value ;
			break;
		}
			   
		case TIMER1_B :
		{
			OCR1B =(uint16)value ;
			break;
		} 

		case TIMER2 :
		{
			OCR2 =(uint8)value ;
			break;
		}
	}
}

void TIMER_Set_ICR_Value(uint16 value)
	{
		ICR1=value ;
	}
