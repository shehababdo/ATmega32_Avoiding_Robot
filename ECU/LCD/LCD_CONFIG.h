
#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/*
What should i do here !
1- Macros needed
2- Renaming of ports needed
3- Renaming of pins needed
4- States
*/

#include "../../COMMON/DataType.h"
#include "../../MCAL/DIO/DIO.h"

/*LCD Mode will be used*/
#define LCD_MODE        4
/*Command Port*/
#define LCD_CMD_PORT  PORT_B
/*Data Port*/
#define LCD_DTA_PORT  PORT_A
/*Control Pins*/
#define LCD_RS        PIN_1
#define LCD_RW        PIN_2
#define LCD_EN        PIN_3
/*Data Pins*/
#define LCD_D4        PIN_4
#define LCD_D5        PIN_5
#define LCD_D6        PIN_6
#define LCD_D7        PIN_7
/*State*/
#define LCD_OUTPUT    OUTPUT


#endif /* LCD_CONFIG_H_ */
