/*
 * TIMER_private.h
 *
 * Created: 6/14/2022 5:33:00 AM
 *  Author: hp
 */ 


#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_



#include "MCAL/STD_TYPES.h"
#include "MCAL/BIT_MATH.h"
#include "MCAL/CONFIG.h"

#include "MCAL/INTERRUPT/INTERRUPT.h"




#define TIFR_BASE_ADRESS  ((volatile u8*)(0x35))

#define TIMSK_BASE_ADRESS ((volatile u8*)(0x6E))
#define TIMSK_TIMER1_ADRESS (*(volatile u8*)(0x6F))
#define TIMSK_TIMER2_ADRESS (*(volatile u8*)(0x70))



typedef struct {
	
	u8 TCCRA;
		
	u8 TCCRB;
	
	u8 TCNT;
	
	u8 OCRA;
	
	u8 OCRB;
	
	u8 Reserved;
	
	u8 ASSR;
	
		
	}TIMER8BIT_ID ;
	

typedef struct{
	
	u8 TCCR1A;
	u8 TCCR1B;
	u8 TCCR1C;
	u8 Reserved;
	
	u16 TCNT1;
	
	u16 ICR;
	
	u16 OCR1A;
	
	u16 OCR1B;
	
	
	}TIMER16BIT_ID;
	
	

#define TIMER2_COMPA __vector_7
#define TIMER2_COMPB __vector_8
#define TIMER2_OVF   __vector_9

#define TIMER1_CAPT  __vector_10
#define TIMER1_COMPA __vector_11
#define TIMER1_COMPB __vector_12
#define TIMER1_OVF   __vector_13

#define TIMER0_COMPA __vector_14
#define TIMER0_COMPB __vector_15
#define TIMER0_OVF   __vector_16




void TIMER0_OVF(void)    __attribute__((signal,used));
void TIMER0_COMPB(void)  __attribute__((signal,used));
void TIMER0_COMPA(void)  __attribute__((signal,used));

void TIMER1_OVF(void)       __attribute__((signal,used));
void TIMER1_COMPB(void)     __attribute__((signal,used));
void TIMER1_COMPA(void)     __attribute__((signal,used));
void TIMER1_CAPT(void) __attribute__((signal,used));


void TIMER2_OVF(void)    __attribute__((signal,used));
void TIMER2_COMPB(void)  __attribute__((signal,used));
void TIMER2_COMPA(void)  __attribute__((signal,used));






	

#endif /* TIMER_PRIVATE_H_ */