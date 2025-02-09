library LCD for AVR (atmega32/16, atmega328p....)


Thư viện được viết dựa trên :

https://www.hocavr.com/ 
https://www.electronicwings.com/avr-atmega/interfacing-lcd-16x2-in-4-bit-mode-with-atmega-16-32-
https://github.com/Hossam-Elbahrawy/16x2-LCD

Thư viện cơ bản cho LCD 16x2 và 20x4 (8 bit)
Các chân cần sử dụng RS RW EN D4 D5 D6 D7
// Cách config các chân tại file chính của chương trình kèm theo hàm lcd_init();
lcd_set_pins(
        (LCD_Pin){&PORTD, &DDRD, PD0},  // RS     //PORTD.0
        (LCD_Pin){&PORTD, &DDRD, PD1},  // RD     //PORTD.1
        (LCD_Pin){&PORTD, &DDRD, PD2},  // EN     //PORTD.2
        (LCD_Pin){&PORTD, &DDRD, PD3},  // D4     //PORTD.3
        (LCD_Pin){&PORTD, &DDRD, PD4},  // D5     //PORTD.4
        (LCD_Pin){&PORTD, &DDRD, PD5},  // D6     //PORTD.5
        (LCD_Pin){&PORTD, &DDRD, PD6}   // D7     //PORTD.6
    );
Lưu ý khi sử dụng với 20x4 thì vào thư viện lcd.h thay đổi #define LCD_TYPE   LCD_16x2 thành #define LCD_TYPE   LCD_20x4
