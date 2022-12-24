#include "lcd.h"

void lcd_cmd(LCD_ID LCD,unsigned char cmd)
{
	GPIO_PORT_ID* GPIO_PORT_CMD =  PGPIO_PORT_get_register(LCD.GPIO_PORT_CMD);
	GPIO_PORT_ID* GPIO_PORT_DATA=  PGPIO_PORT_get_register(LCD.GPIO_PORT_DATA);
	switch(LCD.LCD_DISPLAY_MODE)
	{
		case LCD_8BIT:
		

			GPIO_PORT_DATA->PORT_ID = cmd;
			GPIO_PORT_CMD->PORT_ID &= ~(1<<LCD.rs);
			GPIO_PORT_CMD->PORT_ID &= ~(1<<LCD.rw);
			GPIO_PORT_CMD->PORT_ID |= (1<<LCD.en);
			_delay_ms(1);
			GPIO_PORT_CMD->PORT_ID &= ~(1<<LCD.en);
			_delay_ms(3);
		
		break;
		
		
		case LCD_4BIT:

			GPIO_PORT_DATA->PORT_ID = (GPIO_PORT_DATA->PORT_ID & 0x0F) | (cmd & 0xF0);/* Sending upper nibble */
			GPIO_PORT_CMD->PORT_ID &= ~ (1<<LCD.rs);		/* RS=0, command reg. */
			GPIO_PORT_CMD->PORT_ID |= (1<<LCD.en);		/* Enable pulse */
			_delay_us(1);
			GPIO_PORT_CMD->PORT_ID &= ~ (1<<LCD.en);
			_delay_us(200);
			GPIO_PORT_DATA->PORT_ID = (GPIO_PORT_DATA->PORT_ID & 0x0F) | (cmd << 4);/* Sending lower nibble */
			GPIO_PORT_CMD->PORT_ID |= (1<<LCD.en);
			_delay_us(1);
			GPIO_PORT_CMD->PORT_ID &= ~ (1<<LCD.en);
			_delay_ms(2);					
		
		break;
		
		
	}
}


LCD_ID init_lcd(LCD_DISPLAY_MODE_ID LCD_DISPLAY_MODE,GPIO_PORT GPIO_PORT_DATA, char* DPINS_NUMEBER,GPIO_PORT GPIO_PORT_CMD,char* CPINS_NUMEBER)
{
	
	LCD_ID LCD = {LCD_DISPLAY_MODE,GPIO_PORT_DATA,DPINS_NUMEBER,GPIO_PORT_CMD,CPINS_NUMEBER[0],CPINS_NUMEBER[1],CPINS_NUMEBER[2],0,0};
	switch(LCD_DISPLAY_MODE)
	{
		case LCD_8BIT:
			
			init_lcd8bit( LCD );
			break;
		case LCD_4BIT:
		
			init_lcd4bit( LCD);

			break;
		
	}
	return LCD;
}

void init_lcd8bit(LCD_ID LCD)
{
	GPIO_PORT_ID* GPIO_PORT_CMD =  PGPIO_PORT_get_register(LCD.GPIO_PORT_CMD);
	GPIO_PORT_ID* GPIO_PORT_DATA=  PGPIO_PORT_get_register(LCD.GPIO_PORT_DATA);
	GPIO_PORT_CMD->DDR_ID |= (1<<LCD.rs)|(1<<LCD.rw)|(1<<LCD.en);
	GPIO_PORT_DATA->DDR_ID = 0xFF;
	
	//lcd_data = 0xFF;
	_delay_ms(20);
	GPIO_PORT_CMD->PORT_ID |= (1<<LCD.rs);
	GPIO_PORT_CMD->PORT_ID |= (1<<LCD.rw);
	GPIO_PORT_CMD->PORT_ID |= (1<<LCD.en);
	_delay_ms(100);
	lcd_cmd( LCD,0x38);
	_delay_ms(1);
	lcd_cmd( LCD,0x02);
	_delay_ms(1);
	lcd_cmd( LCD,0x06);
	_delay_ms(1);
	lcd_cmd( LCD,0x80);
	_delay_ms(1);
	lcd_cmd ( LCD,0x0C);
	_delay_ms(1);
	lcd_cmd( LCD,0x01);
		
	
}

void init_lcd4bit(LCD_ID LCD)
{
	GPIO_PORT_ID* GPIO_PORT_CMD =  PGPIO_PORT_get_register(LCD.GPIO_PORT_CMD);
	
	GPIO_PORT_CMD->DDR_ID |= (1<<LCD.rs)|(1<<LCD.rw)|(1<<LCD.en);
	for (int i=0;i<4;i++)
	{
		GPIO_PIN_mode(LCD.GPIO_PORT_DATA,LCD.DPINS_NUMEBER[i],OUTPUT);
	}
	_delay_ms(150);		/* LCD Power ON delay always >15ms */
	

		lcd_cmd(LCD,0x33);
	lcd_cmd(LCD,0x32);	/* Send for 4 bit initialization of LCD  */
	lcd_cmd(LCD,0x28);	/* 2 line, 5*7 matrix in 4-bit mode */
	lcd_cmd(LCD,0x0c);	/* Display on cursor off */
	lcd_cmd(LCD,0x06);	/* Increment cursor (shift cursor to right) */
	lcd_cmd(LCD,0x01);	/* Clear display screen */
}
void lcd_char(LCD_ID LCD,unsigned char chars)
{
	GPIO_PORT_ID* GPIO_PORT_CMD =  PGPIO_PORT_get_register(LCD.GPIO_PORT_CMD);
	GPIO_PORT_ID* GPIO_PORT_DATA=  PGPIO_PORT_get_register(LCD.GPIO_PORT_DATA);
	switch(LCD.LCD_DISPLAY_MODE)
	{
		
		case LCD_8BIT:
		
			GPIO_PORT_DATA->PORT_ID = chars;
			GPIO_PORT_CMD->PORT_ID |= (1<<LCD.rs);
			GPIO_PORT_CMD->PORT_ID &= ~(1<<LCD.rw);
			GPIO_PORT_CMD->PORT_ID |= (1<<LCD.en);
			_delay_us(1);
			GPIO_PORT_CMD->PORT_ID &= ~(1<<LCD.en);
			_delay_ms(3);
		
		break;
		
		
		case LCD_4BIT:
		
	
		

		GPIO_PORT_DATA->PORT_ID = (GPIO_PORT_DATA->PORT_ID & 0x0F) | (chars & 0xF0);/* Sending upper nibble */
		GPIO_PORT_CMD->PORT_ID |= (1<<LCD.rs);		
		GPIO_PORT_CMD->PORT_ID |= (1<<LCD.en);		/* Enable pulse */
		_delay_us(1);
		GPIO_PORT_CMD->PORT_ID &= ~ (1<<LCD.en);
		_delay_us(200);
		GPIO_PORT_DATA->PORT_ID = (GPIO_PORT_DATA->PORT_ID & 0x0F) | (chars << 4);/* Sending lower nibble */
		GPIO_PORT_CMD->PORT_ID |= (1<<LCD.en);
		_delay_us(1);
		GPIO_PORT_CMD->PORT_ID &= ~ (1<<LCD.en);
		_delay_ms(2);		
		
		
		break;
				
	}

}

void lcd_string(LCD_ID* LCD,unsigned char* string)
{
	for (int i = 0; string[i] != '\0';i++)
	{
		
		if (LCD->postion_pointer>=16)
		{
			lcd_cmd( (*LCD),((LCD->postion_pointer-16) & 0x0F)|0xC0);
			LCD->postion_row = 1;
		}	
		
		if (LCD->postion_pointer>=32)
		{
			lcd_cmd( *LCD,((LCD->postion_pointer-32) & 0x0F)|0x90);
			LCD->postion_row = 2;
		}
		
		if (LCD->postion_pointer>=48)
		{
			lcd_cmd( *LCD,((LCD->postion_pointer-64) & 0x0F)|0xD0);
			LCD->postion_row = 3;
		}
			
		lcd_char(*LCD,string[i]);
		
		if (LCD->postion_pointer>=(64))
		{
			
			lcd_clear(LCD);
			LCD->postion_pointer = 0;
			LCD->postion_row = 0;
			
		}
		else
		LCD->postion_pointer+=1;
		

	}
}

void lcd_string_pos(LCD_ID* LCD,int row,int coulm,unsigned char* string)
{
	if (row == 0 )
	{
		lcd_cmd( *LCD,(coulm & 0x0F)|0x80);
		LCD->postion_pointer = coulm+(row*16);
		
	}
	if(row == 1)
	{
		lcd_cmd( *LCD,(coulm & 0x0F)|0xC0);
		LCD->postion_pointer = coulm+(row*16);
	}
	if (row == 2)
	{
		lcd_cmd( *LCD,(coulm & 0x0F)|0x90 );
		LCD->postion_pointer = coulm+(row*16);
	}
	if (row == 3)
	{
		lcd_cmd( *LCD,(coulm & 0x0F)|0xD0 );
		LCD->postion_pointer = coulm+(row*16);
	}

	LCD->postion_row = row;
	lcd_string( LCD,string);
}

void lcd_clear(LCD_ID* LCD)
{
	LCD->postion_pointer = 0;
	LCD->postion_row = 0;
	lcd_cmd ( *LCD,0x01);		/* clear display */
	lcd_cmd ( *LCD,0x80);		/* cursor at home position */
}

void lcd_delete(LCD_ID* LCD,char number_of_chars_to_delete)
{
	unsigned char* white =(unsigned char*) malloc(sizeof(unsigned char)*(number_of_chars_to_delete+1));
	for (int i = 0;i<number_of_chars_to_delete;i++)
	{
		white[i] = ' ';
	}
	*(white+number_of_chars_to_delete) = '\0';
	unsigned char lcd_column = (LCD->postion_pointer-number_of_chars_to_delete);
	if ((LCD->postion_pointer-number_of_chars_to_delete)>=0)
	{
		 LCD->postion_pointer = (LCD->postion_pointer-number_of_chars_to_delete);
	}
	lcd_string(LCD,white);
	LCD->postion_pointer = lcd_column;
	free(white);
}

void lcd_custom_char (LCD_ID* LCD,unsigned char loc, unsigned char *msg)
{
	unsigned char i;
	if(loc<8)
	{
		lcd_cmd (*LCD,0x40 + (loc*8));	/* Command 0x40 and onwards forces the device to point CGRAM address */
		for(i=0;i<8;i++)	/* Write 8 byte for generation of 1 character */
		lcd_char(*LCD,msg[i]);
	}
	
}