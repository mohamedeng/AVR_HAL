/*
 * ADC.h
 *
 * Created: 6/19/2022 7:56:03 AM
 *  Author: hp
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "MCAL/ADC_Converter/ADC_private.h"

typedef enum {ADC0,ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7,ADC8,VBG = 14,ADC_GND = 15}ADC_channel_ID; 
typedef enum {AREF_PIN,AVCC_PIN,Internal_1V}Voltage_Reference_ID;
typedef enum {ADC_PRE_2,ADC_PRE_4 = 2,ADC_PRE_8,ADC_PRE_16,ADC_PRE_32,ADC_PRE_64,ADC_PRE_128}ADC_Prescaler_ID;
typedef enum {ADC_NO_TRIGGER = -1,ADC_Free_Running,ADC_Analog_Comparator,ADC_External_Interrupt,Timer0COMPA,Timer0OVF,Timer1COMPB,Timer1OVF,Timer1_CaptureEvent}ADC_Trigger_Source_ID;	
typedef enum {ADC_INT_ENABLE,ADC_INT_DISABLE}ADC_INT_ID;
void init_ADC(Voltage_Reference_ID Voltage_Reference,ADC_Prescaler_ID ADC_Prescaler,ADC_Trigger_Source_ID ADC_Trigger_Source,ADC_INT_ID ADC_INT, void(*ADC_INT_FUNC)(u16));

u16 ADC_anlogRead(ADC_channel_ID ADC_channel);

u16 ADC_anlogRead8BIT(ADC_channel_ID ADC_channel);
u16 ADC_anlogRead16BIT(ADC_channel_ID ADC_channel);






#endif /* ADC_H_ */