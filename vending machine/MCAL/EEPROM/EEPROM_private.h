/*
 * EEPROM_private.h
 *
 * Created: 7/24/2022 9:20:50 PM
 *  Author: hp
 */ 
#include "MCAL/STD_TYPES.h"
#include "MCAL/BIT_MATH.h"
#include "MCAL/CONFIG.h"

#ifndef EEPROM_PRIVATE_H_
#define EEPROM_PRIVATE_H_

#define EEPM1 5
#define EEPM0 4
#define EERIE 3
#define EEMPE 2
#define EEPE 1
#define EERE 0
#define SPMCSR *((volatile u8*)(0x57))

#define EEPROM_MAX_ADDRESS 1023

typedef struct {
	
	u8 EECR;
	u8 EEDR;
	u8  EEARL;
	u8 EEARH;
	
	
}EEPROM_id;

//SPMCSR






#endif /* EEPROM_PRIVATE.H_H_ */