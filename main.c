#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "i2c.h"
#include "LCD_I2C.h"

int i,j;
char intro[] = "                    HELLO WORLD                ";
int length = sizeof(intro) - 1;
void LCD_displacementLCD() {
    for (i = 0; i <= length - 16; i++) {
        lcd_clear();
        for (j = 0; j < 16; j++) {       
            lcd_gotoxy(j, 0);               
            lcd_putchar(intro[i + j]);  
            _delay_us(100);     
        }
        _delay_ms(200);                      
    }
}
void LCD_displacementI2C() {
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
    lcd_set_pins(
        (LCD_Pin){&PORTB, &DDRB, PB0},  
        (LCD_Pin){&PORTB, &DDRB, PB1},  
        (LCD_Pin){&PORTB, &DDRB, PB2},  
        (LCD_Pin){&PORTB, &DDRB, PB3},  
        (LCD_Pin){&PORTL, &DDRL, PL0},  
        (LCD_Pin){&PORTL, &DDRL, PL1},  
        (LCD_Pin){&PORTL, &DDRL, PL2}   
    );

    lcd_init();
	
    i2c_init();
	i2c_start();
	i2c_write(0x70);
	lcd_init();
	
    while (1) 
    {
	  LCD_displacementLCD();
	  LCD_displacementI2C();
	    
    }
}

