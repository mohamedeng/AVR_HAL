/*
 * ADC.c
 *
 * Created: 6/19/2022 7:56:34 AM
 *  Author: hp
 */ 
#include "MCAL/ADC_Converter/ADC.h"

u16 (*pointerto816bitfunc)(ADC_channel_ID ADC_channel);
void (* callback_ADC) (u16) = {0};


void init_ADC(Voltage_Reference_ID Voltage_Reference,ADC_Prescaler_ID ADC_Prescaler,ADC_Trigger_Source_ID ADC_Trigger_Source,ADC_INT_ID ADC_INT,void(*ADC_INT_FUNC)(u16))
{
	ADC->ADMUX = (Voltage_Reference<<6);
	ADC->ADCSRA = ADC_Prescaler;
	if (0)
	{
		pointerto816bitfunc = &ADC_anlogRead8BIT;
	}
	else
	{
		pointerto816bitfunc = &ADC_anlogRead16BIT;	
	}
	if (ADC_Trigger_Source != ADC_NO_TRIGGER)
	{
		setbit(ADC->ADCSRA,5);
		ADC->ADCSRB |= ADC_Trigger_Source;
	}
	
	//setbit(ADC->ADMUX,7);
	setbit(ADC->ADMUX,6);
	ADC->ADCSRA |= 0x07;
	setbit(ADC->ADCSRA,7);
	//setbit(ADC->ADCSRA,7);	
	setbit(ADC->ADCSRA,6);
	while(ADC->ADCSRA &(1<<6));
	if (ADC_INT)
	{
		callback_ADC = ADC_INT_FUNC;
		setbit(ADC->ADCSRA,3);
		INTERRUPT_GLOBALENABLE
		
	}
}
u16 ADC_anlogRead(ADC_channel_ID ADC_channel)
{	
		ADC->ADMUX &=0xF0;
		ADC->ADMUX |=ADC_channel;
		
		setbit(ADC->ADCSRA,6);
		
		while((ADC->ADCSRA &(1<<6)));
		u16 result = (ADC->ADCL);
		result |= (ADC->ADCH <<8 );
		return result;
	//return pointerto816bitfunc(ADC_channel);	
}
u16 ADC_anlogRead8BIT(ADC_channel_ID ADC_channel)
{
	
		ADC->ADMUX &=0xF0;
		ADC->ADMUX |=ADC_channel;
		
		setbit(ADC->ADCSRA,6);
		
		while((ADC->ADCSRA &(1<<6)));
		u16 result = (ADC->ADCL);
		//u8 temp = ADC->ADCH;
		return result;	
	
}
u16 ADC_anlogRead16BIT(ADC_channel_ID ADC_channel)
{

}
void  ADC_vector (void)
{
	if (callback_ADC == 0 )
	{
		return;
	}
	//callback_ADC(ADC_result);
	
	
}
