/*
 * EEPROM.h
 *
 * Created: 7/24/2022 9:19:59 PM
 *  Author: hp
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "EEPROM_private.h"
void EEPROM_WRITE_BYTE(u8 value,u16 adress);
u8 EEPROM_READ_BYTE(u16 adress);


#endif /* EEPROM_H_ */