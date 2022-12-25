/*
 * KEY_PAD.h
 *
 * Created: 7/24/2022 6:56:22 AM
 *  Author: mohamed mahmoud abdo
 */ 


#ifndef KEY_PAD_H_
#define KEY_PAD_H_
#include "MCAL/STD_TYPES.h"
#include "MCAL/BIT_MATH.h"
#include "MCAL/CONFIG.h"
#include "MCAL/GPIO/GPIO.h"



typedef struct {
	GPIO_PORT PORT_adress_coloms;
	GPIO_PORT PORT_adress_rows;
	u8* pin_coloms;
	u8* pin_rows ;
	u8 num_colom;
	u8 num_row;
	u8* key_pad_array;

	
	
	
	}KEYPAD_ID;
	
/*
input example:

{
	{0,1,2},
	{3,4,5},
	{6,7,8},
	{9,10,11},
}

*/	
	
	
KEYPAD_ID init_KEYPAD(GPIO_PORT PORT_adress_coloms,u8* pin_coloms,GPIO_PORT PORT_adress_rows,u8* pin_rows ,u8 num_coloms,u8 num_rows,u8* key_pad_array);

u8 KEYPAD_get_input(KEYPAD_ID* KEYPAD);
void KEYPAD_get_str(KEYPAD_ID* KEYPAD,char* str);


#endif /* KEY_PAD_H_ */