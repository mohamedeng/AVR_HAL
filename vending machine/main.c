/*
 * main.c
 *
 * Created: 7/23/2022 8:16:53 PM
 *  Author: hp
 */ 
#include <stdio.h>

#include "MCAL/STD_TYPES.h"
#include "MCAL/BIT_MATH.h"
#include "MCAL/CONFIG.h"
#include "MCAL/GPIO/GPIO.h"
#include "MCAL/USART/USART.h"
#include "MCAL/INTERRUPT/INTERRUPT.h"
#include "MCAL/EXTERNAL_INTERRUPT/EXTERNAL_INTERRUPT.h"
#include "MCAL/ADC_Converter/ADC.h"
#include "MCAL/TIMER/TIMER.h"
#include "MCAL/GPIO/GPIO.h"
#include "MCAL/EEPROM/EEPROM.h"
#include "HAL/LCD/lcd.h"
#include "HAL/KEY_PAD/KEY_PAD.h"
#include "HAL/DC_MOTORS/DC_MOTOR.h"
#include <util/delay.h>


#define BYTE_CONFIG 6

#define BYTE_PRODUCT_COUNT 7




void help_screen(LCD_ID* LCD)
{
	char str[]= " use the keypad    for move";
	lcd_string(LCD,str);
	enter_bottun(LCD);
	
}

	
void add_product(char* product_name,int product_price)
{
	int ofset = EEPROM_READ_BYTE(BYTE_PRODUCT_COUNT);
	char cash[4]={0};
	sprintf(cash, "%d",product_price);
	
	for (int i = 0;i<12;i++)
	{
		EEPROM_WRITE_BYTE(product_name[i],i+(ofset*20)+10);
		
	}
	for (int i = 0;i<4;i++)
	{
	EEPROM_WRITE_BYTE(cash[i],i+12+10+(ofset*20));	
	}
	
	
	EEPROM_WRITE_BYTE(EEPROM_READ_BYTE(BYTE_PRODUCT_COUNT)+1,BYTE_PRODUCT_COUNT);
	

}


//static int count=BYTE_PRODUCT_COUNT;
void delete_product()
{
	EEPROM_WRITE_BYTE(EEPROM_READ_BYTE(BYTE_PRODUCT_COUNT)-1,EEPROM_READ_BYTE(BYTE_PRODUCT_COUNT));
}

void product_on_screen_list(LCD_ID* LCD ,int start_screen_value)
{
	char ofset = EEPROM_READ_BYTE(BYTE_PRODUCT_COUNT);
	for (int i = start_screen_value,j=0;i<EEPROM_READ_BYTE(BYTE_PRODUCT_COUNT);i++)
	{
	char product_name[12] = {0};
	char product_price[4]= {0};
			for (int k = 0;k<12;k++)
			{
				product_name[k] = EEPROM_READ_BYTE(k+(i*20)+10);
			}
			for (int k =0;k<3;k++)
			{
				product_price[k] = EEPROM_READ_BYTE(k+12+10+(i*20));
			}
		
			if(j>2 || i>100)
			{
				return;
			}
			lcd_string_pos(LCD,j,0,product_name);
			lcd_string_pos(LCD,j,13,product_price);
			j++;
	}
	
	
	
}


void enter_bottun(LCD_ID* LCD)
{
		char s[2]={3,'\0'};
		char none[]={' ','\0'};
		char str2 []="enter";
		lcd_string_pos(LCD,3,10,str2);
		
		while(GPIO_readPIN_value(GPIO_PORTB,7) != 0)
		{
			lcd_string_pos(LCD,3,15,s);
			_delay_ms(10);
			lcd_string_pos(LCD,3,15,none);
		}
		
		lcd_clear(LCD);
}


void program_start_menu(LCD_ID* LCD)
{
	char str[] = "Embedded systemsexam            designer:mohamed";
	lcd_string(LCD,str);
	enter_bottun(LCD);
}

void frist_setup(LCD_ID* LCD,KEYPAD_ID* KEYPAD)
{
	
	EEPROM_WRITE_BYTE(0,BYTE_PRODUCT_COUNT); // product list counter
	
	char str[] = "the machine needto setup for    frist use";
	lcd_string(LCD,str);
	enter_bottun(LCD);
	config_machine(LCD,KEYPAD);
}



void config_machine(LCD_ID* LCD,KEYPAD_ID* KEYPAD)
{
	char edit_mode[] = "#1990";
	char user_mode[] = "*1990";
	//lcd_clear(LCD);
	char str[60] = "for config of   machine please  enter pass code ";
	u8 pass_right = 0;
	lcd_string_pos(LCD,0,0,str);
	enter_bottun(LCD);
	char user_input [7]= {0,0,0,0,0,0,'\0'};
	lcd_string_pos(LCD,1,5,user_input);
	for (int i = 0;i<5;i++)
	{
		while(user_input[i] == 0)
		user_input[i] = KEYPAD_get_input(KEYPAD);
		_delay_ms(100);
		
		lcd_string_pos(LCD,1,5,user_input);
		
		
		
			if (edit_mode[i] == user_input[i])
			{
				pass_right++;
			}
			else
			pass_right = 0;
		
			
			if (i == 4)
				{
					lcd_delete(LCD,16);
					enter_bottun(LCD);
					if (pass_right != 5 )
					{
						u8 wrong[]= "worng password";
						lcd_string_pos(LCD,1,1, wrong);
						enter_bottun(LCD);
						i=0;
						for (int j =0;j<5;j++)
						{
							user_input[j] = 0;
						}
						lcd_string_pos(LCD,1,5,str);
						enter_bottun(LCD);
					}
					
					if (pass_right == 5)
					{
						u8 right[]="right password";
						
						lcd_string_pos(LCD,1,1,right);
						enter_bottun(LCD);
						EEPROM_WRITE_BYTE('D',BYTE_CONFIG);
						lcd_clear(LCD);
						user_add_product(LCD,KEYPAD);
						
						
					}
			
				}					
						
		
	}

	
}

void user_add_product(LCD_ID* LCD,KEYPAD_ID* KEYPAD)
{
	
	char str[]="Add product";
	lcd_string(LCD,str);
	enter_bottun(LCD);
	char product_name[12] = {0};
	char price[7] ={0};
	char user_name []= "enter product";
	char user_price []="enter price";
	
	char input = 0;
	char capetal = 0;
	for(int i =0;i<11 ; i++)
	{
		lcd_string_pos(LCD,0,0,user_name);
		lcd_string_pos(LCD,1,0,product_name);
		while(input == 0)
		{
			input = KEYPAD_get_input(KEYPAD);
			_delay_ms(100);

			if (GPIO_readPIN_value(GPIO_PORTB,7) == 0)
			{
				i = 11;
				break;
			}
		}
		
		if (input == '#')
		{
			capetal = 1;
		}
		if (capetal == 0)
		{
			product_name[i] = input+31;
		}

		if (capetal == 1)
		{
			product_name[i] = input+11;
		}		
		
		

		input = 0;
	
	}
	lcd_clear(LCD);
	product_name[11] = '\0';
	for(int i =0;i<4 ; i++)
	{
		lcd_string_pos(LCD,0,0,user_price);
		lcd_string_pos(LCD,3,6,price);
		while(input == 0)
		{
			input = KEYPAD_get_input(KEYPAD);
			_delay_ms(100);

			if (GPIO_readPIN_value(GPIO_PORTB,7) == 0)
			{
				i = 3;
				break;
			}
		}
		price[i] = input;

		input = 0;
		
	}	
	price[3] = '\0'; 
	int product_price = atoi(price);
	add_product(product_name,product_price);
	lcd_clear(LCD);
}

u8 pay_screen(LCD_ID* LCD,KEYPAD_ID* KEYPAD,int product)
{
		DC_MOTOR_ID DC_MOTOR ;
		init_DCMOTOR(&DC_MOTOR,GPIO_PORTC,0,1,7);
		DC_MOTOR_ID DC_MOTOR2 ;
		init_DCMOTOR(&DC_MOTOR2,GPIO_PORTC,2,3,7);
		char product_price[4];
		for (int k =0;k<3;k++)
		{
			product_price[k] = EEPROM_READ_BYTE(k+12+10+(product*20));
		}	
	
		int product_price_int = atoi(product_price); 
		char str[]="Enter the cash and press enter ";
		char input = 0;
		char cash [6]= {0};
		lcd_clear(LCD);
		int sum = 0;

		
		for(int i =0;i<4 ; i++)
		{
			lcd_string_pos(LCD,1,1,str);
			lcd_string_pos(LCD,3,6,cash);
			while(input == 0)
			{
				input = KEYPAD_get_input(KEYPAD);
				_delay_ms(100);

				if (GPIO_readPIN_value(GPIO_PORTB,7) == 0)
				{
					i = 3;
					break;
				}
			}
			cash[i] = input;

			input = 0;
			
		}
				MOTOR_MOVE(&DC_MOTOR,1);
				_delay_ms(1000);
				MOTOR_STOP(&DC_MOTOR);
		lcd_clear(LCD);
		sum  =atoi(cash);
		if (sum >255)
		{
			sum = 255;
		}
		if (sum < product_price_int)
		{
			char str3[]= "the cash is not enough";
			lcd_string(LCD,str3);
			enter_bottun(LCD);
			return 3;
		}
		if (sum > product_price_int)
		{
		char str3[]= "the rest: ";
		char str4 [6];
		sprintf(str4, "%d",sum-product_price_int);
		lcd_string(LCD,str3);			
		lcd_string(LCD,str4);	
		
		MOTOR_MOVE(&DC_MOTOR,0);
		_delay_ms(1000);
		MOTOR_STOP(&DC_MOTOR);	

		MOTOR_MOVE(&DC_MOTOR2,0);
		_delay_ms(1000);
		MOTOR_STOP(&DC_MOTOR2);
		
		}
		else
		{
		char str3[]= "have a nice product";

		lcd_string(LCD,str3);
		MOTOR_MOVE(&DC_MOTOR2,0);
		_delay_ms(1000);
		MOTOR_STOP(&DC_MOTOR2);		
		}
	enter_bottun(LCD);
	return 0;
}

void move_on_screen(LCD_ID* LCD,KEYPAD_ID* KEYPAD)
{
	
	char input =0 ;
	char mover = 0;
	
		
		char s[2]={3,'\0'};
		char none[]={' ','\0'};
		char str2 []="enter";
		
		char want_to_buy = 0;
		
		product_on_screen_list(LCD,0);
		while(1)
		{
			lcd_string_pos(LCD,3,11,str2);
			while(input == 0 && want_to_buy == 0)
			{
				input = KEYPAD_get_input(KEYPAD);
				
				if (GPIO_readPIN_value(GPIO_PORTB,7) == 0)
				want_to_buy = 3;
			}
			
			if (want_to_buy == 3)
			{
				want_to_buy=pay_screen(LCD,KEYPAD,mover);
				if (want_to_buy !=3)
				{
					product_on_screen_list(LCD,0);
				}
				
			}
			
			if (input =='*')
			{
				config_machine(LCD,KEYPAD);
				product_on_screen_list(LCD,mover);
			}
			
			if (input == '2')
			{
				if (mover >0)
				{
					mover--;
				}
				lcd_clear(LCD);	
				product_on_screen_list(LCD,mover);
			}
			if (input == '8')
			{
				if (mover <EEPROM_READ_BYTE(BYTE_PRODUCT_COUNT)-1)
				{
					mover++;
				}
				lcd_clear(LCD);	
				product_on_screen_list(LCD,mover);
				
			}
			
			
			input = 0;
				
			
		}
		
		
	
	

	
}

int main(void)
{
	EEPROM_WRITE_BYTE(0,BYTE_PRODUCT_COUNT);
	
	char product_name[10] = {'p','r','o','d','u','c','t','1'};
	product_name[9] = '\0';
	char product_price= 200;
	for (int i=0; i<10;i++)
	{
		add_product(product_name,i+product_price);
	}

	
//#####################################################
	char enter_buttom[] = {
		0b00000,
		0B00001,
		0B00011,
		0B00111,
		0B01111,
		0B00011,
		0B00001,
		0B00000
	};
	char lcd_data_pins[4] ={4,5,6,7};
	char lcd_cmd_pins[3] =  {1,2,3};
	LCD_ID LCD = init_lcd(LCD_4BIT,GPIO_PORTD,lcd_data_pins,GPIO_PORTD,lcd_cmd_pins);
	lcd_custom_char(&LCD,3,enter_buttom);
	lcd_clear(&LCD);
	//#############################
	//product_on_screen_list(&LCD,1);
	//_delay_ms(5000);
	//############################
//#####################################################
	u8 num_colums = 3;
	u8 colums[3] = {2,1,0};
	u8 num_rows = 4;
	u8 rows[4] = {3,4,5,6};
	u8 keypad_array [4][3]= {
		
			{'1','2','3'},
			{'4','5','6'},
			{'7','8','9'},
			{'*','0','#'}
		
	};
	KEYPAD_ID KEYPAD = init_KEYPAD(GPIO_PORTB,colums,GPIO_PORTB,rows,num_colums,num_rows,(u8*)keypad_array);
//#####################################################	

	//u16 f= EEPROM_READ_BYTE(10);
	GPIO_PIN_mode(GPIO_PORTB,7,INPUT_PULLUP);
	GPIO_PIN_mode(GPIO_PORTD,0,INPUT_PULLUP);
	
	
	
	program_start_menu(&LCD);
	while (EEPROM_READ_BYTE(BYTE_CONFIG) != 'D')
	{
		
		frist_setup(&LCD,&KEYPAD);
	}
	if (EEPROM_READ_BYTE(BYTE_CONFIG) == 'D')
	{
		char x []="welcome to my vending machine ";
		lcd_string(&LCD,x);
		_delay_ms(500);
		lcd_clear(&LCD);
	}
	help_screen(&LCD);

	

	
	if (EEPROM_READ_BYTE(BYTE_PRODUCT_COUNT) == 0)
	{
		char str[]="no products in the machine";
		lcd_string(&LCD,str);
	}
	
    while(1)
    {
		 move_on_screen(&LCD,&KEYPAD);

		
    }
	
}