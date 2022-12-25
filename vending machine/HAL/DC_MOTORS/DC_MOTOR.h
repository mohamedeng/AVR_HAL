/*
 * DC_MOTOR.h
 *
 * Created: 7/27/2022 6:41:21 AM
 *  Author: hp
 */ 


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include "MCAL/STD_TYPES.h"
#include "MCAL/BIT_MATH.h"
#include "MCAL/CONFIG.h"
#include "MCAL/GPIO/GPIO.h"


typedef struct 
{
	u8 pin1;
	u8 pin2;
	u8 en;
	GPIO_PORT PORT_adress;
	} DC_MOTOR_ID;


void init_DCMOTOR(DC_MOTOR_ID* DC_MOTOR,GPIO_PORT PORT_adress,u8 PIN1,u8 PIN2,u8 ENPIN);

void MOTOR_MOVE(DC_MOTOR_ID* DC_MOTOR,u8 DIRECTION);

void MOTOR_STOP(DC_MOTOR_ID* DC_MOTOR);



#endif /* DC_MOTOR_H_ */