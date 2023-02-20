#ifndef CPU_CONFIGRATION_H
#define CPU_CONFIGRATION_H

//Micro controller CPU config
#undef F_CPU    // UNDEFINED INTERNAL OSCILLATOR
#define F_CPU 16000000  //DEFINED EXTERNAL OSCILLATOR
#include <avr/io.h>
#include <avr/interrupt.h>  // define interrupt for avr
#include <util/delay.h>     // built in delay function 
#include <stdio.h>
#include "string.h"
#include "BitMath.h"
#include "DataType.h"
#endif /* CPU_CONFIGRATION_H */