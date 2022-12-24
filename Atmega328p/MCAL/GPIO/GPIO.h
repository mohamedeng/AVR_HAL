/*
 * GPIO.h
 *
 * Created: 6/7/2022 4:47:43 AM
 *  Author: mohamed mahmoud abdo
 */ 


#ifndef GPIO_H_

#define GPIO_H_
#include "MCAL/STD_TYPES.h"
#include "MCAL/CONFIG.h"
#include "private_GPIO.h"

typedef enum {INPUT,OUTPUT,INPUT_PULLUP} GPIO_MODE ;

typedef enum {LOW,HIGH} GPIO_STATE ;





void GPIO_PIN_mode(GPIO_PORT PORT_adress,u8 PIN ,GPIO_MODE mode);
void GPIO_writePIN_value(GPIO_PORT PORT_adress,u8 PIN ,GPIO_STATE state);
void GPIO_togglePIN_value(GPIO_PORT PORT_adress,u8 PIN );
u8 GPIO_readPIN_value(GPIO_PORT PORT_adress,u8 PIN );


void GPIO_PORT_mode(GPIO_PORT PORT_adress,GPIO_MODE mode);
void GPIO_writePORT_value(GPIO_PORT PORT_adress,u8 value);
void GPIO_togglePORT_value(GPIO_PORT PORT_adress);
u8 GPIO_readPORT_value(GPIO_PORT PORT_adress);


GPIO_PORT_ID* PGPIO_PORT_get_register(GPIO_PORT PORT_adress);


#endif /* GPIO_H_ */