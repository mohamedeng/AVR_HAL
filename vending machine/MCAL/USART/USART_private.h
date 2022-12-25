/*
 * UART_private.h
 *
 * Created: 3/14/2022 11:39:31 PM
 *  Author: hp
 */ 


#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

#include "MCAL/STD_TYPES.h"
#include "MCAL/BIT_MATH.h"
#include "MCAL/CONFIG.h"
#include "MCAL/INTERRUPT/INTERRUPT.h"


#define UCSR0C *((volatile char*)0xC2)

// UCSR0C
#define UMSEL01 7
#define UMSEL00 6
#define UPM01 5
#define UPM00 4
#define USBS0 3
#define UCSZ01 2 
#define UCSZ00 1
#define UCPOL0 0
//

#define UCSR0B *((volatile char*)0xC1)

//UCSR0B
#define RXCIE0 7
#define TXCIE0 6
#define UDRIE0 5
#define RXEN0 4
#define TXEN0 3
#define UCSZ02 2
#define RXB80 1
#define TXB80 0
//


#define UCSR0A *((volatile char*)0xC0)  
//UCSR0A
#define RXC0 7
#define TXC0 6
#define UDRE0 5
#define FE0 4
#define DOR0 3
#define UPE0 2
#define U2X0 1
#define MPCM0 0
//
               
#define UDR0 *((volatile char*)0xC6)


#define UBRR0H *((volatile char*)0xC5)
#define UBRR0L *((volatile char*)0xC4)


#define USART_RX_vector __vector_18
#define USART_UDRE_vector __vector_19
#define USART_TX_vector __vector_20

void USART_RX_vector (void) __attribute__((signal,used));
void USART_UDRE_vector (void) __attribute__((signal,used));
void USART_TX_vector (void) __attribute__((signal,used));


#endif /* UART_PRIVATE_H_ */