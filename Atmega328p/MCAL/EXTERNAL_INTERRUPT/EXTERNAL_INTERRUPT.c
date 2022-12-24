/*
 * EXTERNAL_INTERRUPT.c
 *
 * Created: 6/14/2022 4:09:07 PM
 *  Author: hp
 */ 

#include "EXTERNAL_INTERRUPT_private.h"
#include "EXTERNAL_INTERRUPT.h"


void (* EXTI_FUNC [5])(void) = {0,0,0,0,0};


void init_EXT_INT( INT_PIN_ID INT_PIN ,TRIGGER_MODE_ID TRIGGER_MODE,void (*call_back)(void))
{
	 EXTI_setTRIGGER( INT_PIN , TRIGGER_MODE);
	 
	 EXTI_FUNC [INT_PIN] = call_back;
	 
	 EXTI_ENABLE( INT_PIN);
}

void init_PC_INT(PCINT_ID PCINT_PIN,void (*call_back)(void))
{
	
	

	if (PCINT_PIN< 8)//portB int
	{
		EXTI_FUNC [2] = call_back;
	}
	
	if (PCINT_PIN>7 && PCINT_PIN< 15)//portC int
	{
		EXTI_FUNC [3] = call_back;
	}
	
	if (PCINT_PIN>15 && PCINT_PIN< 24)//portD int
	{
		EXTI_FUNC [4] = call_back;
	}	
	
	PCINT_ENABLE(PCINT_PIN);
	
	
	return;
	
}

void EXTI_setTRIGGER(INT_PIN_ID INT_PIN ,TRIGGER_MODE_ID TRIGGER_MODE)
{
	switch(INT_PIN)
	{
		case INT0:
		
		
		if (EXTI_LOW_LEVEL == TRIGGER_MODE)
		{
		resetbit( External_INT->EICRA, ISC00);
		resetbit( External_INT->EICRA, ISC01);
			
			
		}
		
		if (EXTI_ANY_CHANGE == TRIGGER_MODE)
		{
		setbit( External_INT->EICRA, ISC00);
		resetbit( External_INT->EICRA, ISC01);			
			
		}
		
		if (EXTI_FALLING_EDGE == TRIGGER_MODE)
		{
		resetbit( External_INT->EICRA, ISC00);
		setbit( External_INT->EICRA, ISC01);			
			
		}
		
		if (EXTI_RISING_EDGE == TRIGGER_MODE)
		{
			
		setbit( External_INT->EICRA, ISC00);
		setbit( External_INT->EICRA, ISC01);			
		}
		
		break;
		case INT1:
		
		
		if (EXTI_LOW_LEVEL == TRIGGER_MODE)
		{
			resetbit( External_INT->EICRA, ISC10);
			resetbit( External_INT->EICRA, ISC11);
			
			
		}
		
		if (EXTI_ANY_CHANGE == TRIGGER_MODE)
		{
			setbit( External_INT->EICRA, ISC10);
			resetbit( External_INT->EICRA, ISC11);
			
		}
		
		if (EXTI_FALLING_EDGE == TRIGGER_MODE)
		{
			resetbit( External_INT->EICRA, ISC10);
			setbit( External_INT->EICRA, ISC11);
			
		}
		
		if (EXTI_RISING_EDGE == TRIGGER_MODE)
		{
			
			setbit( External_INT->EICRA, ISC10);
			setbit( External_INT->EICRA, ISC11);
		}
		break;


	}
}

void EXTI_ENABLE(INT_PIN_ID INT_PIN)
{
	setbit(External_INT->EIMSK,INT_PIN);
	INTERRUPT_GLOBALENABLE
	
}

void EXTI_DISABLE( INT_PIN_ID INT_PIN)
{
	resetbit(External_INT->EIMSK,INT_PIN);
		
}

void PCINT_ENABLE(PCINT_ID PCINT_PIN)
{
	if (PCINT_PIN< 8)//portB int
	{
		setbit(External_INT->PCMSK0,PCINT_PIN);
		setbit(External_INT->PCICR,0);
		
		INTERRUPT_GLOBALENABLE;
		return;
	}
	
	if (PCINT_PIN< 15)//portC int
	{
		setbit(External_INT->PCMSK1,(PCINT_PIN-8));
		setbit(External_INT->PCICR,1);
		
		INTERRUPT_GLOBALENABLE
		return;
	}
	
	if (PCINT_PIN< 24)//portD int
	{
	
		setbit(External_INT->PCMSK2,(PCINT_PIN-16));
		setbit(External_INT->PCICR,2);
		
		INTERRUPT_GLOBALENABLE;
		return;
	}
	
	return;
}

void PCINT_DISABLE(PCINT_ID PCINT_PIN)
{
	if (PCINT_PIN< 8)//portB int
	{
		resetbit(External_INT->PCMSK0,PCINT_PIN);
		resetbit(External_INT->PCICR,0);
		
		return;
	}
	
	if (PCINT_PIN< 15)//portC int
	{
		resetbit(External_INT->PCMSK1,(PCINT_PIN-8));
		resetbit(External_INT->PCICR,1);
		
		return;
	}
	
	if (PCINT_PIN< 24)//portD int
	{
		
		resetbit(External_INT->PCMSK2,(PCINT_PIN-16));
		resetbit(External_INT->PCICR,2);
		
		return;
	}
	
	return;
}




void EXTI_INT0_vector(void)
{
	if (EXTI_FUNC[0] ==0)
	{
		return;
	}
	EXTI_FUNC[0]();	
}
void EXTI_INT1_vector(void)
{
	
	if (EXTI_FUNC[1] ==0)
	{
		return;
	}	
	EXTI_FUNC[1]();
}
void EXTI_PCINT0_vector(void){


	if (EXTI_FUNC[2] ==0)
	{
		return;
	}
	EXTI_FUNC[2]();
}
void EXTI_PCINT1_vector(void)
{
	if (EXTI_FUNC[3] == 0)
	{
		return;
	}
	EXTI_FUNC[3]();	
}
void EXTI_PCINT2_vector(void)
{
	if (EXTI_FUNC[4] == 0)
	{
		return;
	}	
	EXTI_FUNC[4]();
	
}
 