/*
 * INTERRUPT.h
 *
 * Created: 6/14/2022 3:28:28 PM
 *  Author: hp
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_
#include "MCAL/STD_TYPES.h"
#include "MCAL/CONFIG.h"
#include "MCAL/BIT_MATH.h"
#include "INTERRUPT_private.h"


# define INTERRUPT_GLOBALENABLE setbit(SREG,7);
# define INTERRUPT_GLOBALDISABLE resetbit(SREG,7);




#endif /* INTERRUPT_H_ */