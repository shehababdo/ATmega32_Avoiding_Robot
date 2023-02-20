/*
 * SERVO.h
 *
 * Created: 2/27/2022 11:42:10 PM
 *  Author: Shehab
 */ 


#ifndef SERVO_H_
#define SERVO_H_
#include  "../../MCAL/TIMER/TIMER.h"
#include "../../COMMON/CPU_CONFIG.h"

void servo_init(void);
void servo_90_anti_clkwise(void);
void servo_90_clkwise(void);
void servo_zero(void);




#endif /* SERVO_H_ */