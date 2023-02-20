/*
 * US.c
 *
 * Created: 2/7/2023 6:20:08 PM
 *  Author: shehab
 */ 
#include "US.h"
#include "../../Common/CPU_CONFIG.h"
#include "../../MCAL/TIMER/TIMER.h"
uint8 count=0,state=0,Tpc=0,Tdc=0;
uint8 Tp=0,Td=0;
float tot_time,freq,duty,duty_freq,dist,Time;
char trig_pin =1;
char echo_pin =2;
 
void US_Init(void)
{
	//RISING EDGE
	set_bit(MCUCR,ISC00);
	set_bit(MCUCR,ISC01);
	
	DIO_SetDir(PORT_D,trig_pin,OUTPUT);
	DIO_SetDir(PORT_D,echo_pin,OUTPUT);
	
	set_bit(GICR,INT0);
	set_bit(SREG, 7);
	
	/*TIMER 0 SETUP*/
	/*TCCR0=0x04;
	TIMSK=1;*/
	set_bit(GICR,INT0);
	timer_used();
	sei();
}
float pulse(void)
{

	DIO_SetHigh(PORT_D,trig_pin);
	_delay_us(15);
	DIO_SetLow(PORT_D,trig_pin);
	
	set_bit(GICR,INT0);
	
	/*start detecting the pulse*/
	if(state==3)
	{
		freq=16000000.0/((Tp+Tpc*256ul)*256.0);
		duty=((float)(Td+Tdc*256ul)/(Tp+Tpc*256ul));
		duty_freq=freq*duty;
		DDRC=duty_freq;
		PORTC=freq;
		tot_time=1/duty_freq;
		Time=tot_time/2.0;
		dist=Time*3.43;
		Tp=0,Tpc=0,Tdc=0,Td=0;
		state=0;
	}
	if (dist==0)
	{ return 1/0;} 
	else
	{ return dist;}
}

void timer_used(void)
{
	TIMER_Paramter_t timerUsed ;
	timerUsed.Timer_Channel = TIMER0;
	timerUsed.Timer_Mode = NORMAL;
	timerUsed.COM_Pin = Disconnected;
	timerUsed.Timer_OCR_Interrupt = OCR_disable;
	timerUsed.Timer_OVF_Interrupt = TOVF_enable;
	timerUsed.Timer_Prescale = PRESCALING_CLK256;
	TIMER_Init(timerUsed);
}

ISR(INT0_vect)
{
	if (state==0)
	{	
		TCCR0=0x04;
		TCNT0=0;
		count=0;
		// FALLING EDGE
		clr_bit(MCUCR,ISC00);
		set_bit(MCUCR,ISC01);
		state=1;
	}
	else if(state==1)
	{
		Td=TCNT0;
		Tdc=count;
		//RISING EDGE
		set_bit(MCUCR,ISC00);
		set_bit(MCUCR,ISC01);
		
		state=2;
	}
	else if (state ==2)
	{
		Tp=TCNT0;
		Tpc=count;
		clr_bit(GICR,INT0);
		TCCR0=0;
		state=3;
	}
}

ISR(TIMER0_OVF_vect)
{
	count++;
}