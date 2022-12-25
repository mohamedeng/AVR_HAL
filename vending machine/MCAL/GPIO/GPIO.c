/*
 * GPIO.c
 *
 * Created: 6/7/2022 4:50:45 AM
 *  Author: mohamed mahmoud abdo
 */ 
#include "MCAL/STD_TYPES.h"
#include "MCAL/BIT_MATH.h"
#include "GPIO.h"


#include "avr/delay.h"



GPIO_PORT_ID* PGPIO_PORT_get_register(GPIO_PORT PORT_adress)
{
	GPIO_PORT_ID* PORT = (GPIO_PORT_ID*) PORT_adress;
	return PORT;

}


void GPIO_PIN_mode( GPIO_PORT PORT_adress,u8 PIN ,GPIO_MODE mode)
{
	volatile GPIO_PORT_ID* PORT = PGPIO_PORT_get_register(PORT_adress);
	switch (mode)
	{
		case INPUT :
		resetbit(PORT->DDR_ID,PIN);
		break;
		
		case OUTPUT :
		setbit(PORT->DDR_ID,PIN);
		break;
		
		case INPUT_PULLUP :
		resetbit(PORT->DDR_ID,PIN);
		setbit(PORT->PORT_ID,PIN);
		break;
	}
}
void GPIO_writePIN_value(GPIO_PORT PORT_adress,u8 PIN ,GPIO_STATE state)
{
	volatile GPIO_PORT_ID* PORT = PGPIO_PORT_get_register(PORT_adress);
	switch (state)
	{
		case LOW :
		resetbit(PORT->PORT_ID,PIN);
		break;
		
		case HIGH :
		setbit(PORT->PORT_ID,PIN);
		break;

		

	}
}
void GPIO_togglePIN_value(GPIO_PORT PORT_adress,u8 PIN )
{
	GPIO_PORT_ID* PORT = PGPIO_PORT_get_register(PORT_adress);
	togglebit(PORT->PORT_ID,PIN);
}
u8 GPIO_readPIN_value(GPIO_PORT PORT_adress,u8 PIN )
{
	volatile GPIO_PORT_ID* PORT = PGPIO_PORT_get_register(PORT_adress);
	
	if (PIN > 7)
	{
		return 255;
	}
	return readbit(PORT->PIN_ID,PIN);
}


void GPIO_PORT_mode(GPIO_PORT PORT_adress,GPIO_MODE mode)
{
	GPIO_PORT_ID* PORT = PGPIO_PORT_get_register(PORT_adress);
	switch (mode)
	{
		case INPUT :
		reset(PORT->DDR_ID);
		break;
		
		case OUTPUT :
		set(PORT->DDR_ID);
		break;
		
		case INPUT_PULLUP:
		reset(PORT->DDR_ID);
		set(PORT->PORT_ID);
		break;
		

	}
}
void GPIO_writePORT_value(GPIO_PORT PORT_adress,u8 value)
{
	GPIO_PORT_ID* PORT = PGPIO_PORT_get_register(PORT_adress);
	PORT->PORT_ID = value;
	
}
void GPIO_togglePORT_value (GPIO_PORT PORT_adress)
{
	GPIO_PORT_ID* PORT = PGPIO_PORT_get_register(PORT_adress);
	toggle(PORT->PORT_ID);
	
}
u8 GPIO_readPORT_value(GPIO_PORT PORT_adress)
{
	GPIO_PORT_ID* PORT = PGPIO_PORT_get_register(PORT_adress);
	return PORT->PIN_ID;
}

