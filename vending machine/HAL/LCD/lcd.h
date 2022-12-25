#include <stdlib.h>
#include "MCAL/CONFIG.h"
#include "MCAL/BIT_MATH.h"
#include "MCAL/GPIO/GPIO.h"
#include "MCAL/GPIO/private_GPIO.h"
#include <util/delay.h>
//#define lcd_data_dir DDRD
//#define lcd_data PORTD
//#define lcd_cmd_dir DDRB
//#define lcd_cmd_data PORTB
//#define rs PB0
//#define rw PB1
//#define en PB2

typedef enum {LCD_4BIT,LCD_8BIT}LCD_DISPLAY_MODE_ID;

typedef struct {
	LCD_DISPLAY_MODE_ID LCD_DISPLAY_MODE;
	GPIO_PORT GPIO_PORT_DATA;
	char* DPINS_NUMEBER;
	GPIO_PORT GPIO_PORT_CMD;
	char rs;
	char rw;
	char en;
	u64 postion_pointer;
	char postion_row;
}
	LCD_ID;

LCD_ID init_lcd(LCD_DISPLAY_MODE_ID LCD_DISPLAY_MODE,GPIO_PORT GPIO_PORT_DATA, char* DPINS_NUMEBER,GPIO_PORT GPIO_PORT_CMD,char* CPINS_NUMEBER);
void lcd_cmd(LCD_ID LCD,unsigned char cmd);
void lcd_char(LCD_ID LCD,unsigned char chars);
void lcd_clear(LCD_ID* LCD);
void lcd_delete(LCD_ID* LCD,char number_of_chars_to_delete);
void lcd_string(LCD_ID* LCD,unsigned char* string);
void lcd_string_pos(LCD_ID* LCD,int row,int coulm,unsigned char* string);
void init_lcd8bit(LCD_ID LCD);
void init_lcd4bit(LCD_ID LCD);
void lcd_custom_char (LCD_ID* LCD,unsigned char loc, unsigned char *msg);
