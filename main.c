#include "i2c.h"
#include "LCD_I2C.h"

int i,j;
char intro[] = "                    HELLO WORLD                ";
int length = sizeof(intro) - 1;

void LCD_displacement() {
    for (i = 0; i <= length - 16; i++) {
        lcd_clear();
        for (j = 0; j < 16; j++) {       
            lcd_gotoxy(j, 0);               
            lcd_dwr(intro[i + j]);  
            _delay_us(100);     
        }
        _delay_ms(20);                      
    }
}

int main(void)
{
    i2c_init();
	i2c_start();
	i2c_write(0x70);
	lcd_init();
	
    while (1) 
    {
	   LCD_displacement();
    }
}

