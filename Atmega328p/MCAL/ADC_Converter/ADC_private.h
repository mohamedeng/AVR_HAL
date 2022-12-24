/*
 * ADC_private.h
 *
 * Created: 6/19/2022 7:56:23 AM
 *  Author: hp
 */ 


#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_
#include "MCAL/STD_TYPES.h"
#include "MCAL/BIT_MATH.h"
#include "MCAL/CONFIG.h"
#include "MCAL/INTERRUPT/INTERRUPT.h"



typedef struct 
	{
		
	u8 ADCL;
	u8 ADCH;
	u8 ADCSRA;
	u8 ADCSRB;
	u8 ADMUX;
	u8 Reserved;
	u8 DIDR0;
	u8 DIDR1;
	
	}ADC_ID;
	
	
#define ADC ((volatile ADC_ID*)(0x78))


#define ADC_vector __vector_21

void  ADC_vector (void) __attribute__((signal,used));




#endif /* ADC_PRIVATE_H_ */