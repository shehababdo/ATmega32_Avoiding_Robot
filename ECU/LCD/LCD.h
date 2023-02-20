

#ifndef LCD_H_
#define LCD_H_
#define  F_CPU 16000000
/*
What should i write here!
1- Macros
2- User defined data types (Structure - Union - Enumeration)
3- Global variables (if Exist)
4- Functions prototypes
*/

#include "LCD_CONFIG.h"

void LCD_Init(void);              								 /*Initialize LCD*/
void LCD_WriteCMD(uint8 cmd);   								/*Write command inside control register*/
void LCD_WriteChar(uint8 data);   								/*write data inside data register*/
void LCD_WriteString (char string[]);  								/*write string on screen*/
void LCD_WriteAtPosition(uint8 lineNumber , uint8 digitNumber);/*write number on specific position on screen*/
void LCD_Clear(void);              								/*Clear data display on screen*/
void LCD_WriteINTEGER(uint32 integer);							/*write number on screen*/

#endif /* LCD_H_ */
