/*
 * EXTERNAL_INTERRUPT.h
 *
 * Created: 6/14/2022 4:08:56 PM
 *  Author: hp
 */ 


#ifndef EXTERNAL_INTERRUPT_H_
#define EXTERNAL_INTERRUPT_H_


#include "MCAL/STD_TYPES.h"
#include "MCAL/BIT_MATH.h"
#include "MCAL/CONFIG.h"
#include "EXTERNAL_INTERRUPT_private.h"
#include "MCAL/GPIO/private_GPIO.h"


typedef enum {INT0,INT1}INT_PIN_ID;

typedef enum { EXTI_LOW_LEVEL, EXTI_ANY_CHANGE ,EXTI_FALLING_EDGE,EXTI_RISING_EDGE}TRIGGER_MODE_ID;

	
	
typedef enum {
	//PORTB
	PCINT0, 
	PCINT1,
	PCINT2,
	PCINT3,
	PCINT4,
	PCINT5,
	PCINT6,
	PCINT7,
	
	//PORTC
	PCINT8,
	 PCINT9,
	 PCINT10,
	 PCINT11,
	 PCINT12,
	 PCINT13,
	 PCINT14,
	 Reserved1,
	 //PORTD
	 PCINT16,
	 PCINT17,
	 PCINT18,
	 PCINT19,
	 PCINT20,
	 PCINT21,
	 PCINT22,
	 PCINT23 
	}PCINT_ID;

;

void init_EXT_INT( INT_PIN_ID INT_PIN ,TRIGGER_MODE_ID TRIGGER_MODE,void (*call_back)(void));

void  init_PC_INT(PCINT_ID PCINT_PIN,void (*call_back)(void));

void EXTI_setTRIGGER(INT_PIN_ID INT_PIN ,TRIGGER_MODE_ID TRIGGER_MODE);

void EXTI_ENABLE(INT_PIN_ID INT_PIN);
void EXTI_DISABLE( INT_PIN_ID INT_PIN);



void PCINT_ENABLE(PCINT_ID PCINT_PIN);
void PCINT_DISABLE(PCINT_ID PCINT_PIN);



#endif /* EXTERNAL_INTERRUPT_H_ */