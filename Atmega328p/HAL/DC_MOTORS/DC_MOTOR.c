/*
 * DC_MOTOR.c
 *
 * Created: 7/27/2022 6:41:35 AM
 *  Author: hp
 */ 
#include "DC_MOTOR.h"

void init_DCMOTOR(DC_MOTOR_ID* DC_MOTOR,GPIO_PORT PORT_adress,u8 PIN1,u8 PIN2,u8 ENPIN)
{
	DC_MOTOR->pin1 = PIN1;
	DC_MOTOR->pin2 =PIN2;
	DC_MOTOR->en = ENPIN;
	DC_MOTOR->PORT_adress = PORT_adress;
	GPIO_PIN_mode(PORT_adress,PIN1,OUTPUT);
	GPIO_PIN_mode(PORT_adress,PIN2,OUTPUT);
	GPIO_PIN_mode(PORT_adress,ENPIN,OUTPUT);
}
void MOTOR_MOVE(DC_MOTOR_ID* DC_MOTOR,u8 DIRECTION)
{
	if (DIRECTION )
	{
		GPIO_writePIN_value(DC_MOTOR->PORT_adress,DC_MOTOR->pin1,HIGH);
		GPIO_writePIN_value(DC_MOTOR->PORT_adress,DC_MOTOR->pin2,LOW);
		return;	
	}
	
	GPIO_writePIN_value(DC_MOTOR->PORT_adress,DC_MOTOR->pin2,HIGH);
	GPIO_writePIN_value(DC_MOTOR->PORT_adress,DC_MOTOR->pin1,LOW);
	
}


void MOTOR_STOP(DC_MOTOR_ID* DC_MOTOR)
{
	GPIO_writePIN_value(DC_MOTOR->PORT_adress,DC_MOTOR->pin2,LOW);
	GPIO_writePIN_value(DC_MOTOR->PORT_adress,DC_MOTOR->pin1,LOW);	
}

