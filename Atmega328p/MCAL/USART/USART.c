/*
 * library.c
 *
 * Created: 3/12/2022 11:19:50 PM
 *  Author: Mohamed Mahmoud
 */ 

#include "usart.h"

volatile void (*callback_T)(u16 data);
volatile char(*callback_R)(void);

void (*USART_INT_callback[3])(u16);


void init_USART(unsigned int Baud_Rate,uint8_t mode,uint8_t Size,uint8_t parity,u8 stop_bit,uint8_t Receiver ,uint8_t Transmiter,USART_Int_ID USART_Int,void(*USART_Intcallback)(u16) )
{
	// parity : 0 no parity, 1 odd , 2 even
	unsigned int myUBRR;		
		switch(mode)
		{
			case USART_Normal:
			
			myUBRR = F_CPU/Baud_Rate/16-1;
			
			UBRR0H = (unsigned char)(myUBRR>>8); // baud_rate
			UBRR0L =  (unsigned char)(myUBRR);
			
			UCSR0B =  Transmiter ? setbit(UCSR0B,RXEN0) : UCSR0B ;// turn on rx
			UCSR0B = Receiver ? setbit(UCSR0B,TXEN0) : UCSR0B ; // turn on tx
			
			if (parity == 1 )
			{
				
			UCSR0C =  setbit(UCSR0C,UPM01) ; 
			
			UCSR0C =  setbit(UCSR0C,UPM00) ;	
						
			}
			if (parity == 2)
			{
				
			UCSR0C =  setbit(UCSR0C,UPM01) ;
						
			}

			if (stop_bit == 2)
			{
				
				UCSR0C =    setbit(UCSR0C,USBS0) ; //stop bit delete the comment if you want 2 stop bits 
			}
			
			
			UCSR0C =  ((Size-5)<<UCSZ00) ; //size of the data 5bit to 9 bit
			
			if (Size == 9)
			{
				callback_T = &USART_Transmit_9bitchar;
				callback_R = &USART_receive_9bitchar;
				setbit(UCSR0C,UCSZ02);
			}
			else
			{
				callback_T = &USART_Transmit_8bitchar;
				callback_R = &USART_receive_8bitchar;
			}
			break;
				
			case USART_Double:
			
			myUBRR = F_CPU/Baud_Rate/8-1;
			UBRR0H = (unsigned char)(myUBRR>>8); // baud_rate
			UBRR0L =  (unsigned char)(myUBRR);
			
			UCSR0B =  Transmiter ? setbit(UCSR0B,RXEN0) : UCSR0B ;// turn on rx
			UCSR0B = Receiver ? setbit(UCSR0B,TXEN0) : UCSR0B ; // turn on tx
			
			
			if (parity == 1 )
			{
				
				UCSR0C =  setbit(UCSR0C,UPM01) ;
				
				UCSR0C =  setbit(UCSR0C,UPM00) ;
				
			}
			if (parity == 2)
			{
				
				UCSR0C =  setbit(UCSR0C,UPM01) ;
				
			}

			
			if (stop_bit == 2)
			{
				
				UCSR0C =    setbit(UCSR0C,USBS0) ; //stop bit delete the comment if you want 2 stop bits
			}
			
			
			UCSR0C =  ((Size-5)<<UCSZ00) ; //size of the data 5bit to 9 bit
			if (Size == 9)
			{
				callback_T = &USART_Transmit_9bitchar;
				callback_R = &USART_receive_9bitchar;
				setbit(UCSR0C,UCSZ02);
			}
			else
			{
				callback_T = &USART_Transmit_8bitchar;
				callback_R = &USART_receive_8bitchar;
			}
			
			
			break;
			
			case USART_Master:
			
			myUBRR = F_CPU/Baud_Rate/2-1;
			UBRR0H = (unsigned char)(myUBRR>>8); // baud_rate
			UBRR0L =  (unsigned char)(myUBRR);
			
			UCSR0B =  Transmiter ? setbit(UCSR0B,RXEN0) : UCSR0B ;// turn on rx
			UCSR0B = Receiver ? setbit(UCSR0B,TXEN0) : UCSR0B ; // turn on tx
			
			if (parity == 1 )
			{
				
				UCSR0C =  setbit(UCSR0C,UPM01) ;
				
				UCSR0C =  setbit(UCSR0C,UPM00) ;
				
			}
			if (parity == 2)
			{
				
				UCSR0C =  setbit(UCSR0C,UPM01) ;
				
			}

			
			if (stop_bit == 2)
			{
				
				UCSR0C =    setbit(UCSR0C,USBS0) ; //stop bit delete the comment if you want 2 stop bits
			}
			
			
			UCSR0C =  ((Size-5)<<UCSZ00) ; //size of the data 5bit to 8 bit
			if (Size == 9)
			{
				callback_T = &USART_Transmit_9bitchar;
				callback_R = &USART_receive_9bitchar;
				setbit(UCSR0C,UCSZ02);
			}
			else
			{
				callback_T = &USART_Transmit_8bitchar;
				callback_R = &USART_receive_8bitchar;
			}
			
		
		
		}
		
	switch(USART_Int)
	{
		case USART_RX_ENABLE:
		 USART_INT_callback [0]= USART_Intcallback;
		 INTERRUPT_GLOBALENABLE
		break;
		
		case USART_TX_ENABLE:
		 USART_INT_callback [1]= USART_Intcallback;
		 INTERRUPT_GLOBALENABLE
		
		break;
		case USART_TX_RX_ENABLE:
		 USART_INT_callback [2]= USART_Intcallback;
		 INTERRUPT_GLOBALENABLE
		break;
		case USART_DISABLE_INT:
		break;
		default:
		#warning "you used out of range value check the USART INT IDS"
		break;
		
		
		
	}	


	
}




void USART_Transmit_char( u16 data)
{
	callback_T(data);

}
void USART_Transmit_9bitchar( u16 data)
{
	UCSR0B &= ~(1<<TXB80);
	if ( data & 0x0100 )
	UCSR0B |= (1<<TXB80);
	UDR0 = data;
	
}
void USART_Transmit_8bitchar( u16 data)
{
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;	
}


u16 USART_receive_char()
{
	return callback_R();
}
u16 USART_receive_8bitchar()
{
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;	
}
u16 USART_receive_9bitchar()
{
	u8 status, resh, resl;
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get status and 9th bit, then data */
	/* from buffer */
	status = UCSR0A;
	resh = UCSR0B;
	resl = UDR0;
	/* If error, return -1 */
	if ( status & ((1<<FE0)|(1<<DOR0)|(1<<UPE0)) )
	return -1;
	/* Filter the 9th bit, then return */
	resh = (resh >> 1) & 0x01;
	return ((resh << 8) | resl);	
	
}

u8 USART_available(void)
{
	return (UCSR0A & (1<<RXC0)); // check for data available in buffer 
}


void USART_RX_vector (void)
{
	if (USART_INT_callback[0] == 0)
	{
		return;
	}
	
	USART_INT_callback[0](UDR0);
}	

void USART_UDRE_vector (void)
{
	if (USART_INT_callback[1] == 0)
	{
		return;
	}
	
	USART_INT_callback[1](UDR0);	
}

void USART_TX_vector (void)
{
	if (USART_INT_callback[2] == 0)
	{
		return;
	}
	
	USART_INT_callback[2](UDR0);	
}
