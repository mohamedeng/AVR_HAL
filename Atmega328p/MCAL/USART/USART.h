/*
 * usart.h
 *
 * Created: 3/12/2022 11:46:21 PM
 *  Author: mohamed mahmoud
 */ 


#ifndef USART_H_
#define USART_H_
// mode

#include "MCAL/STD_TYPES.h"
#include "MCAL/CONFIG.h"
#include "MCAl/USART/USART_private.h"
#include "MCAL/BIT_MATH.h"
#define USART_Normal 0
#define USART_Double 1
#define USART_Master 2

#define EVEN 2
#define ODD 1
#define NO_PARITY 0


#define STOPBIT_1 1

#define STOPBIT_2 2


#define USART_INT_ENABLE 1
#define USART_INT_DISABLE 0

 
#define USART_Receiver_ENABLE 1
#define USART_Receiver_DISABLE 0

#define USART_Transmiter_ENABLE 1
#define USART_Transmiter_DISABLE 0

typedef enum {USART_DISABLE_INT,USART_RX_ENABLE,USART_TX_ENABLE,USART_TX_RX_ENABLE}USART_Int_ID; 

void init_USART(unsigned int Baud_Rate,u8 mode,u8 Size,u8 parity,u8 stop_bit,u8 Receiver ,u8 Transmiter,USART_Int_ID USART_Int ,void(*USART_Intcallback)(u16));

void USART_Transmit_char( u16 data);

void USART_Transmit_8bitchar( u16 data);
void USART_Transmit_9bitchar( u16 data);


u16 USART_receive_char();
u16 USART_receive_8bitchar();
u16 USART_receive_9bitchar();


u8 USART_available(void);



#endif /* USART_H_ */