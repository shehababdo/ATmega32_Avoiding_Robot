/*
 * BitMath.h
 *
 * Created: 8/6/2021 10:35:57 PM
 *  Author: Shehab
 */ 


#ifndef BITMATH_H_
#define BITMATH_H_


#define set_bit(Reg,bit_no)				Reg |=		 (1<<bit_no)
#define clr_bit(Reg,bit_no)				Reg &=		~(1<<bit_no)
#define toggle_bit(Reg,bit_no)			Reg ^=		 (1<<bit_no)

#define get_bit(Reg,bit_no)				(Reg&(1<<bit_no))

#define set_bit_mask(Reg,bit_mask)		Reg |=		 (bit_mask)
#define clr_bit_mask(Reg,bit_mask)		Reg &=		~(bit_mask)
#define toggle_bit_mask(Reg,bit_mask)	Reg ^=		 (bit_mask)

#define set_bits(Reg)					Reg  =		 (0xFF)
#define clr_bits(Reg)					Reg  =		 (0x00)
#define toggle_bits(Reg,bit_mask)		Reg ^=		 (0xFF)


#endif /* BITMATH_H_ */