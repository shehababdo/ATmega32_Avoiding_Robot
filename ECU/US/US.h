/*
 * US.h
 *
 * Created: 2/7/2023 6:20:20 PM
 *  Author: shehab
 */ 


#ifndef US_H_
#define US_H_

#include "../../MCAL/DIO/DIO.h"
#include "../../Common/CPU_CONFIG.h"
#include "../../MCAL/TIMER/TIMER.h"
void US_Init(void);
float pulse(void);
void timer_used(void);
#endif /* US_H_ */