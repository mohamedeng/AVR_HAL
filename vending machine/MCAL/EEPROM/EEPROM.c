/*
 * EEPROM.c
 *
 * Created: 7/24/2022 9:21:12 PM
 *  Author: hp
 */ 
#include "EEPROM.h"
#define EEPROM  ((volatile EEPROM_id*) (0x3F))

void EEPROM_WRITE_BYTE(u8 value,u16 adress)
{
	if (adress >EEPROM_MAX_ADDRESS)
	{
		return ;
	}
	//EEPROM_id* EEPROM = (volatile EEPROM_id*) 0x3F;
	/* Wait for completion of previous write */
	while(EEPROM->EECR & (1<<EEPE));
	/* Set up address and Data Registers */
	EEPROM->EEARH = (adress & 0xFF00)>>8 ;
	EEPROM->EEARL = (adress & 0x00FF);
	EEPROM->EEDR = value;
	/* Write logical one to EEMPE */
	EEPROM->EECR |= (1<<EEMPE);
	/* Start eeprom write by setting EEPE */
	EEPROM->EECR |= (1<<EEPE);	
	
}
u8 EEPROM_READ_BYTE(u16 adress)
{
	if (adress >EEPROM_MAX_ADDRESS)
	{
		return 0;
	}	
	//EEPROM_id* EEPROM = ( volatile EEPROM_id*)(0x3F);
	/* Wait for completion of previous write */
	while(EEPROM->EECR & (1<<EEPE))
	;
	/* Set up address register */
	EEPROM->EEARH = (adress & 0xFF00)>>8 ;
	EEPROM->EEARL = (adress & 0x00FF);
	/* Start eeprom read by writing EERE */
	EEPROM->EECR |= (1<<EERE);
	/* Return data from Data Register */
	return EEPROM->EEDR;
}