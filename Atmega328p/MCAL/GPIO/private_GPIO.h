/*
 * private.h
 *
 * Created: 6/7/2022 4:48:35 AM
 *  Author: hp
 */ 


#ifndef PRIVATE_H_
#define PRIVATE_H_


typedef enum {GPIO_PORTB = 0x36,GPIO_PORTC = 0x33,GPIO_PORTD = 0x30,GPIO_PORTA = 0x39} GPIO_PORT ;


typedef struct  GPIO_PORT_ID{
	
	volatile u8 PIN_ID;
	volatile u8 DDR_ID;
	volatile u8 PORT_ID;
	
}GPIO_PORT_ID;



#endif /* PRIVATE_H_ */