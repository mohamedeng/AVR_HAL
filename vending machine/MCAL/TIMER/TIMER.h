/*
 * TIMER.h
 *
 * Created: 6/14/2022 5:32:04 AM
 *  Author: hp
 */ 


#ifndef TIMER_H_
#define TIMER_H_
#include "MCAL/CONFIG.h"
#include "MCAL/TIMER/TIMER_private.h"

typedef enum {NO_CHANNEL,CHANNEL_A = 4,CHANNEL_B = 2}CHANNEL_ID;


typedef enum  {TIMER0 = 0x44,TIMER1 = 0x80,TIMER2 = 0xB0} TIMER_TYPE_ID;
typedef enum {TIMER_OVF = 0, TIMER_COMPA= 1,TIMER_COMPB = 2,TIMER_CAPT = 3}INT_SOURCE_ID;
	
typedef enum {No_clocksource,No_prescaler,prescaler_8,prescaler_64_32T2,prescaler_256_64T2,prescaler_1024,T_falling_edge,T_rising_edge} prescale_ID;

//typedef enum {No_clocksource,No_prescaler,prescaler_8,prescaler_32,prescaler_64} prescalerTIMER2_ID;
//typedef enum {No_clocksource,No_prescaler,prescaler_8 ,prescaler_64,prescaler_256,prescaler_1024,T_falling_edge,T_rising_edge} prescalerTIMER1_ID;
//typedef enum {No_clocksource,No_prescaler,prescaler_8,prescaler_64,prescaler_256,prescaler_1024,T_falling_edge,T_rising_edge} prescalerTIMER0_ID;



typedef enum {
	
TIMER_Normal ,
PWMPhaseCorrect8BIT,
PWMPhaseCorrect9BIT,
PWMPhaseCorrect10BIT,
 CTC_OCR,
 FastPWM8BIT,
 FastPWM9BIT,
 FastPWM10BIT, 
 PWMPhaseFrequencyCorrect_ICR,
 PWMPhaseFrequencyCorrect_OCRA, 
PWMPhaseCorrect_ICR ,
 PWMPhaseCorrect_OCRA ,
 CTC_ICR,
 Reserved,
 FastPWM_ICR,
 FastPWM_OCR
	
	}TIMER_MODE_ID;

typedef enum {
	
	
	TIMER_NormalPIN,
	TIMER_TogglePIN_ONCOMPARE,
	TIMER_ClearPIN_ONCOMPARE,
	TIMER_setPIN_ONCOMPARE
	
	
	
	} CHANNEL_MODE_ID;


// ctc 
// f = fclk /(2 * prescaler *(ocr+1))
// presaler = fclk/f*2*(ocr+1)

// fast 
// f = fclk / (2 * prescaler * max)


void init_TIMER(TIMER_TYPE_ID TIMER,TIMER_MODE_ID TIMER_MODE,CHANNEL_ID CHANNEL,CHANNEL_MODE_ID CHANNEL_MODE,u64 FREQ);

void SET_FREQ(TIMER_TYPE_ID TIMER,TIMER_MODE_ID TIMER_MODE,u64 FREQ);

void TIMERINT_ENABLE(TIMER_TYPE_ID TIMER,INT_SOURCE_ID INT_SOURCE,void* callback);

void TIMERINT_DISABLE(TIMER_TYPE_ID TIMER,INT_SOURCE_ID INT_SOURCE);


void init_TIMER8BIT(TIMER_TYPE_ID TIMER,u8 TIMER_MODE,CHANNEL_ID CHANNEL,CHANNEL_MODE_ID CHANNEL_MODE,u64 FREQ);

void init_TIMER16BIT(TIMER_TYPE_ID TIMER,u8 TIMER_MODE,CHANNEL_ID CHANNEL,u8 CHANNEL_MODE,u64 FREQ);


u8 get_realprescaler(TIMER_TYPE_ID TIMER,u64 prescaler);


void Update_Duty_Cycle(TIMER_TYPE_ID TIMER,CHANNEL_ID CHANNEL,u16 duty_cycle);



#endif /* TIMER_H_ */