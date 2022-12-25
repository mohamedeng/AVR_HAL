/*
 * KEY_PAD.c
 *
 * Created: 7/24/2022 6:56:33 AM
 *  Author: mohamed mahmoud abdo
 */
#include "KEY_PAD.h"
#include <util/delay.h>
KEYPAD_ID init_KEYPAD(GPIO_PORT PORT_adress_coloms,u8* pin_coloms,GPIO_PORT PORT_adress_rows,u8* pin_rows ,u8 num_coloms,u8 num_rows,u8* key_pad_array)
{
	

	for (int i = 0;i<num_coloms;i++)
	{
		GPIO_PIN_mode(PORT_adress_coloms,pin_coloms[i] ,INPUT);
		

	}
	for (int i = 0;i<num_rows;i++)
	{
		GPIO_PIN_mode(PORT_adress_rows,pin_rows[i] ,OUTPUT);

	}	
	KEYPAD_ID KEYPAD = {PORT_adress_coloms,PORT_adress_rows,pin_coloms,pin_rows,num_coloms,num_rows,(u8*)key_pad_array};
	
	
	return KEYPAD;
}

u8 KEYPAD_get_input(KEYPAD_ID* KEYPAD)
{
	u8 pressed_key = 0;
	# 0000
	# 0010
	# 
	u8 value =7;

	for (int i = 0;i<KEYPAD->num_row;i++)
	{
		
		GPIO_writePIN_value(KEYPAD->PORT_adress_rows,KEYPAD->pin_rows[i] ,HIGH);
		for (int k = 0;k<KEYPAD->num_colom;k++)
		{
			value = GPIO_readPIN_value(KEYPAD->PORT_adress_coloms,KEYPAD->pin_coloms[k]);

			if (value != 0)
			{
					pressed_key = KEYPAD->key_pad_array[i * KEYPAD->num_colom + k];
					
					
			}
		
						
		}
		_delay_ms(5);
		GPIO_writePIN_value(KEYPAD->PORT_adress_rows,KEYPAD->pin_rows[i] ,LOW);	
	}

	return pressed_key;
	

	
}
	
void KEYPAD_get_str(KEYPAD_ID* KEYPAD,char* str)
{
	str[0] = KEYPAD_get_input(KEYPAD);
}
