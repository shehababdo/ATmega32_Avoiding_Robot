/*
 * SERVO.c
 *
 * Created: 2/27/2022 11:41:54 PM
 *  Author: Shehab
 */ 
#include "SERVO.h"


void servo_init(void)
{
	// INITIALIZATION FOR TIMER 1 CHANNEL B
	DDRD |= (1<<4);  //set OC1A OUTPUT 
	TIMER_Set_OCR_Value(TIMER1_A,40000); // periodic time equals 20 ms 
    TIMER_Paramter_t timerUsed ;
    timerUsed.Timer_Channel = TIMER1;
    timerUsed.TMR1_Channel  = T1_B ;
    timerUsed.Timer1_Mode = FAST_PWM_OCR;
    timerUsed.COM_Pin = NON_INVERTED;
    timerUsed.Timer_OCR_Interrupt = OCR_disable;
    timerUsed.Timer_ICR_Interrupt = ICR_disable;
    timerUsed.Timer_OVF_Interrupt = TOVF_disable;
	 timerUsed.Timer_Prescale = PRESCALING_CLK8;
    TIMER_Init(timerUsed);
	
}

void servo_90_anti_clkwise(void)
{
	TCNT1=0; 
	TIMER_Set_OCR_Value(TIMER1_B,1000);  //----------> TO get 1/2 ms high 
}

void servo_90_clkwise(void)
{
	TCNT1=0;
	TIMER_Set_OCR_Value(TIMER1_B,5000);  //----------> TO get 2.5 ms high
}

void servo_zero(void)
{
	TCNT1=0;
	TIMER_Set_OCR_Value(TIMER1_B,3000);  //----------> TO get 1.5 ms high
}