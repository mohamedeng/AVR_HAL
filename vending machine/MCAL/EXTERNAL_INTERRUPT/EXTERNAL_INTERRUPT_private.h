/*
 * EXTERNAL_INTERRUPT_private.h
 *
 * Created: 6/14/2022 4:09:34 PM
 *  Author: hp
 */ 


#ifndef EXTERNAL_INTERRUPT_PRIVATE_H_
#define EXTERNAL_INTERRUPT_PRIVATE_H_


#include "MCAL/STD_TYPES.h"
#include "MCAL/BIT_MATH.h"
#include "MCAL/CONFIG.h"
#include "MCAL/INTERRUPT/INTERRUPT.h"

#define EXTI_INT0_vector __vector_1 
#define EXTI_INT1_vector __vector_2
#define EXTI_PCINT0_vector __vector_3
#define EXTI_PCINT1_vector __vector_4
#define EXTI_PCINT2_vector __vector_5


// __attribute__ used to tell the compiler to not deleted , signal to tell the compiler that it is signal trigger

void EXTI_INT0_vector(void) __attribute__((signal,used)); 
void EXTI_INT1_vector(void) __attribute__((signal,used));
void EXTI_PCINT0_vector(void) __attribute__((signal,used));
void EXTI_PCINT1_vector(void) __attribute__((signal,used));
void EXTI_PCINT2_vector(void) __attribute__((signal,used));


//void (* EXTI_FUNC [5])(void) = {0,0,0,0,0};



//EICRA
#define ISC00 0
#define ISC01 1
#define ISC10 2 
#define ISC11 3



typedef struct {
	
	
	u8 PCIFR ;
	u8 EIFR;
	u8 EIMSK;
	
	u8 Reserved1[42];
	
	u8 PCICR;
	u8 EICRA;
	u8 Reserved2;
	u8 PCMSK0;
	u8 PCMSK1;
	u8 PCMSK2;
	
	
	}External_INT_ID ;
	
	
	
#define External_INT ((volatile External_INT_ID*) (0x3B))

	


#endif /* EXTERNAL_INTERRUPT_PRIVATE_H_ */