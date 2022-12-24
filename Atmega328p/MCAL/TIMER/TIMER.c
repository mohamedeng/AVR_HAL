/*
 * TIMER.c
 *
 * Created: 6/14/2022 5:32:16 AM
 *  Author: hp
 */ 

#include "MCAL/TIMER/TIMER.h"
#include <stdio.h>
#include <string.h>
void (*timer_call_back[9])(void) = {0};
void (*timer_call_back_CAP)(u16 EVENT) = {0};
#define ICR1_RG *((volatile u16*)(0x86)) 

void init_TIMER(TIMER_TYPE_ID TIMER,TIMER_MODE_ID TIMER_MODE,CHANNEL_ID CHANNEL,CHANNEL_MODE_ID CHANNEL_MODE,u64 FREQ)

{
	
	if (TIMER == TIMER1)
	
	{
		init_TIMER16BIT( TIMER, TIMER_MODE, CHANNEL, CHANNEL_MODE, FREQ);
	}
	
	if (TIMER == TIMER2 || TIMER == TIMER0)
	{
		init_TIMER8BIT(TIMER,TIMER_MODE,CHANNEL,CHANNEL_MODE,FREQ);
	}
	
}

void init_TIMER8BIT(TIMER_TYPE_ID TIMER,TIMER_MODE_ID TIMER_MODE,CHANNEL_ID CHANNEL,CHANNEL_MODE_ID CHANNEL_MODE,u64 FREQ)
{

	volatile TIMER8BIT_ID* TIMER8BIT = ( TIMER8BIT_ID*)TIMER;
	volatile u8 realprescaler;
	volatile u64 prescaler;
	//u32 prescaler = get_prescaler(TIMER8BIT,TIMER_MODE,FREQ);

	switch(TIMER_MODE)
	{
		case Reserved:
		return;
		break;
		case TIMER_Normal :
		
		TIMER8BIT->TCCRB =0;
		TIMER8BIT->TCCRA =0;
		
		
		TIMER8BIT->TCCRA |= (CHANNEL_MODE<<(CHANNEL+2));
		
		prescaler = F_CPU/FREQ/256;
		realprescaler = get_realprescaler(TIMER,prescaler);

		TIMER8BIT->TCCRB |= realprescaler;	
		break;
		
		case PWMPhaseCorrect8BIT:


	
	TIMER8BIT->TCCRA |=3;
	
	TIMER8BIT->TCCRA |= (CHANNEL_MODE<<(CHANNEL+2));
	
	prescaler = F_CPU/FREQ/256;
	realprescaler = get_realprescaler(TIMER,prescaler);

	TIMER8BIT->TCCRB |= realprescaler;
	

		break;
		
		case CTC_OCR:
	//0 1 2
	//setbit(TIMER8BIT->TCCRA,2);
		
	TIMER8BIT->TCCRA |= (CHANNEL_MODE<<(CHANNEL+2));
	TIMER8BIT->TCCRA |= 0x04;
	//TIMER8BIT->OCRA =  F_CPU/(FREQ*2);
	prescaler = (F_CPU/(FREQ*2))/2;
	
	realprescaler = get_realprescaler(TIMER,prescaler);

	TIMER8BIT->TCCRB |= realprescaler;
		
		break;
		
		case FastPWM8BIT:
	
		TIMER8BIT->TCCRA |=3;
		
		TIMER8BIT->TCCRA |= (CHANNEL_MODE<<(CHANNEL+2));
		
		prescaler = F_CPU/FREQ/256;
		realprescaler = get_realprescaler(TIMER,prescaler);

		TIMER8BIT->TCCRB |= realprescaler;

		
		
		
		break;
		
		case PWMPhaseCorrect_OCRA:
		
	
	TIMER8BIT->TCCRA |=3;
	
	TIMER8BIT->TCCRA |= (CHANNEL_MODE<<(CHANNEL+2));
	
	prescaler = F_CPU/FREQ/256;
	realprescaler = get_realprescaler(TIMER,prescaler);
	
	

	TIMER8BIT->TCCRB |= realprescaler;		
	setbit(TIMER8BIT->TCCRB,3);	
				
		break;
		
		case FastPWM_OCR:


	
	TIMER8BIT->TCCRA |=3;
	
	TIMER8BIT->TCCRA |= (CHANNEL_MODE<<(CHANNEL+2));
	
	prescaler = F_CPU/FREQ/256;
	realprescaler = get_realprescaler(TIMER,prescaler);

	TIMER8BIT->TCCRB |= realprescaler;
	setbit(TIMER8BIT->TCCRB,3);	
	
	
		
		break;
		
		
		default:
		return;
		
		
		
	}
	
	
}
void init_TIMER16BIT(TIMER_TYPE_ID TIMER,TIMER_MODE_ID TIMER_MODE,CHANNEL_ID CHANNEL,u8 CHANNEL_MODE,u64 FREQ)
{
	volatile TIMER16BIT_ID* TIMER16BIT = ( TIMER16BIT_ID*)TIMER;
	volatile u8 realprescaler;
	volatile u64 prescaler;
	//u32 prescaler = get_prescaler(TIMER8BIT,TIMER_MODE,FREQ);

	switch(TIMER_MODE)
	{
		case TIMER_Normal :
		
		TIMER16BIT->TCCR1A =0;
		TIMER16BIT->TCCR1A =0;
		
		
		TIMER16BIT->TCCR1A |= (CHANNEL_MODE<<(CHANNEL+2));
		prescaler = F_CPU/FREQ/256;
		realprescaler = get_realprescaler(TIMER,prescaler);		
		
		
		break;
		
		case PWMPhaseCorrect8BIT:


		
		TIMER16BIT->TCCR1A |=3;
		
		TIMER16BIT->TCCR1A |= (CHANNEL_MODE<<(CHANNEL+2));
		
		prescaler = F_CPU/FREQ/256;
		realprescaler = get_realprescaler(TIMER,prescaler);

		TIMER16BIT->TCCR1B |= realprescaler;
		

		break;
		
		case CTC_OCR:

		
		TIMER16BIT->TCCR1A |=3;
		
		TIMER16BIT->TCCR1A |= (CHANNEL_MODE<<(CHANNEL+2));
		
		prescaler = F_CPU/FREQ/256;
		realprescaler = get_realprescaler(TIMER,prescaler);

		TIMER16BIT->TCCR1B |= realprescaler;
		
		break;
		
		case FastPWM8BIT:
		
		TIMER16BIT->TCCR1A |=1;
		
		TIMER16BIT->TCCR1A |= (CHANNEL_MODE<<(CHANNEL+2));
		
		prescaler = F_CPU/FREQ/256;
		realprescaler = get_realprescaler(TIMER,prescaler);

		TIMER16BIT->TCCR1B |= realprescaler;
		setbit(TIMER16BIT->TCCR1B,3 );		
				

		
		break;
		
		
		case FastPWM9BIT:
		
	
		TIMER16BIT->TCCR1A |=2;
		
		TIMER16BIT->TCCR1A |= (CHANNEL_MODE<<(CHANNEL+2));
		
		prescaler = F_CPU/FREQ/512;
		realprescaler = get_realprescaler(TIMER,prescaler);

		TIMER16BIT->TCCR1B |= realprescaler;
		setbit(TIMER16BIT->TCCR1B,3 );

	
		break;
		
		case FastPWM10BIT:
		
		TIMER16BIT->TCCR1A |=3;
		
		TIMER16BIT->TCCR1A |= (CHANNEL_MODE<<(CHANNEL+2));
		
		prescaler = F_CPU/FREQ/1024;
		realprescaler = get_realprescaler(TIMER,prescaler);

		TIMER16BIT->TCCR1B |= realprescaler;
		setbit(TIMER16BIT->TCCR1B,3 );
		

		
		
		break;
		
		case PWMPhaseCorrect_OCRA:
		
		
		TIMER16BIT->TCCR1A |=3;
		
		TIMER16BIT->TCCR1A |= (CHANNEL_MODE<<(CHANNEL+2));
		
		prescaler = F_CPU/FREQ/256;
		realprescaler = get_realprescaler(TIMER,prescaler);

		TIMER16BIT->TCCR1B |= realprescaler;
		
		
		break;
		
		case FastPWM_OCR:

		TIMER16BIT->TCCR1A |=3;
		
		TIMER16BIT->TCCR1A |= (CHANNEL_MODE<<(CHANNEL+2));
		
		TIMER16BIT->OCR1A = F_CPU/FREQ/256;
		
		prescaler = F_CPU/FREQ/(256*TIMER16BIT->OCR1A);
		realprescaler = get_realprescaler(TIMER,prescaler);

		TIMER16BIT->TCCR1B |= realprescaler;
		
		
		
		break;
		
		
		
		
		default:
		return;		
		
	}
	
	
}


u8 get_realprescaler(TIMER_TYPE_ID TIMER,u64 prescaler)
{
	u16 realprescaler[6]= {-20,0,8,64,256,1024};
	u16 realprescalertimer2[5]= {-20,0,8,32,64};	
	u8 i;
	switch(TIMER){
		
		case TIMER0:
			
		for (i = 1; i<7;i ++)
		{
			
			if (prescaler<=realprescaler[i])
			{
				return i;
				
			}
			
		}
		return i;
	

		break;
		case TIMER1:
					
			for (i = 1; i<7;i ++)
			{
				
				if (prescaler<realprescaler[i])
				{
					return i;
					
				}
				
			}
			return i;
		

		break;
		
		
		case TIMER2:;
		
			
		for (i = 1; i<5;i ++)
		{
			
			if (prescaler<realprescalertimer2[i])
			{
				return i;
				
			}
			
		}
		return i;
	
			
		break;
		
	}
	
	return 0;
	
	}
	// presaler = fclk/f*2*(ocr+1)

void Update_Duty_Cycle(TIMER_TYPE_ID TIMER,CHANNEL_ID CHANNEL,u16 duty_cycle)
{
	
	switch(TIMER)
	{
		case TIMER0:;
		case TIMER2:;
		//duty_cycle = (duty_cycle*255/100);
		volatile TIMER8BIT_ID* TIMER8BIT = ( TIMER8BIT_ID*)TIMER;
		if (CHANNEL == CHANNEL_A)
		{
			TIMER8BIT->OCRA = duty_cycle;
		}
		
		if (CHANNEL == CHANNEL_B)
		{
			TIMER8BIT->OCRB = duty_cycle;
		}
		

		
		break;
		case TIMER1:;
		//duty_cycle = (duty_cycle*255/100);
		volatile TIMER16BIT_ID* TIMER16BIT = ( TIMER16BIT_ID*)TIMER;
		if (CHANNEL == CHANNEL_A)
		{
			TIMER16BIT->OCR1A = duty_cycle;
		}
				
		if (CHANNEL == CHANNEL_B)
		{
			TIMER16BIT->OCR1B = duty_cycle;
		}
		
		
	}
	
	
}


void TIMERINT_ENABLE(TIMER_TYPE_ID TIMER,INT_SOURCE_ID INT_SOURCE,void* callback)
{

	switch(TIMER){
		
		case TIMER0:;
		
		
		setbit(TIMSK_BASE_ADRESS[0],INT_SOURCE);
		
		timer_call_back[INT_SOURCE] = callback;
		
		
		
		INTERRUPT_GLOBALENABLE
		
		
		case TIMER1:;
		if (INT_SOURCE == TIMER_CAPT)
		{
			
			timer_call_back_CAP = callback;
		} 
		else
		{
			
		
		timer_call_back[INT_SOURCE+3] = callback;
		}
		setbit(TIMSK_BASE_ADRESS[1],INT_SOURCE);
		
		
		
		INTERRUPT_GLOBALENABLE
		
		case TIMER2:
			
		//timer_call_back[(INT_SOURCE+6)] = callback;
		if (INT_SOURCE == TIMER_OVF)
		{
			setbit(TIMSK_TIMER2_ADRESS,0);
			timer_call_back[6] = callback;
			TIMSK_TIMER2_ADRESS |= 0x01;
		}
		if (INT_SOURCE == TIMER_COMPA)
		{
			setbit(TIMSK_TIMER2_ADRESS,1);
			timer_call_back[7] = callback;
			TIMSK_TIMER2_ADRESS |= 0x02;
		}
		if (INT_SOURCE == TIMER_COMPB)
		{
			setbit(TIMSK_TIMER2_ADRESS,2);
			timer_call_back[8] = callback;
			TIMSK_TIMER2_ADRESS |= 0x04;
		}
		//setbit(TIMSK_BASE_ADRESS[2],INT_SOURCE);
		INTERRUPT_GLOBALENABLE		
		
		
	}
	
	
	
	
}

void TIMERINT_DISABLE(TIMER_TYPE_ID TIMER,INT_SOURCE_ID INT_SOURCE)
{
	
	switch(TIMER){
		
		case TIMER0:;
		
		resetbit(TIMSK_BASE_ADRESS[0],INT_SOURCE);
			
		case TIMER1:;

		resetbit(TIMSK_BASE_ADRESS[1],INT_SOURCE);
		
	
		case TIMER2:
	
		resetbit(TIMSK_BASE_ADRESS[2],INT_SOURCE);

		
		
	}	
	
}


void TIMER0_OVF(void) 
{
	
	if (timer_call_back[0] == 0)
	{
		return;
	}
	timer_call_back[0]();	
	
}
void TIMER0_COMPB(void) {
	
	if (timer_call_back[1] == 0)
	{
		return;
	}
	timer_call_back[1]();	
	
	
}
void TIMER0_COMPA(void)  {
	
	if (timer_call_back[2] == 0)
	{
		return;
	}
	timer_call_back[2]();	
	
}

void TIMER1_OVF(void)   {
	
	
	if (timer_call_back[3] == 0)
	{
		return;
	}
	timer_call_back[3]();	
	
	
}

void TIMER1_COMPB(void) {
	
	
	if (timer_call_back[4] == 0)
	{
		return;
	}
	timer_call_back[4]();	
	
	
}

void TIMER1_COMPA(void)  {
	
	
	if (timer_call_back[5] == 0)
	{
		return;
	}
	timer_call_back[5]();	
	
}

void TIMER1_CAPT(void) {
	
	
	
	if (timer_call_back_CAP == 0)
	{
		return;
	}
	
	timer_call_back_CAP(ICR1_RG);	
	
	
}



void TIMER2_OVF(void)  {
	
	
	if (timer_call_back[6] == 0)
	{
		return;
	}
	timer_call_back[6]();	
	
	
}

void TIMER2_COMPB(void) {
	
	
	if (timer_call_back[7] == 0)
	{
		return;
	}
	timer_call_back[7]();	
	
	
}

void TIMER2_COMPA(void) {
	
	
	if (timer_call_back[8] == 0)
	{
		return;
	}
	timer_call_back[8]();	
	
	
	
	
}


