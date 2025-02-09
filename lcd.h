/*

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

*/
#ifndef LCD_H
#define LCD_H

#include <avr/io.h>
#include <util/delay.h>

// Cấu trúc lưu thông tin ánh xạ của một chân LCD
typedef struct {
    volatile uint8_t *port;  // Thanh ghi PORT (PORTA, PORTB, ...)
    volatile uint8_t *ddr;   // Thanh ghi DDR (DDRA, DDRB, ...)
    uint8_t bit;             // Vị trí bit trên cổng
} LCD_Pin;

// Định nghĩa các thông số LCD (có thể thay đổi)
#define LCD_16x2   0
#define LCD_20x4   1

// Chọn loại LCD
#define LCD_TYPE   LCD_16x2  // Có thể đổi thành LCD_20x4


// Hàm thiết lập các chân của LCD
void lcd_set_pins(LCD_Pin rs_pin, LCD_Pin rd_pin, LCD_Pin en_pin, LCD_Pin d4_pin, LCD_Pin d5_pin, LCD_Pin d6_pin, LCD_Pin d7_pin);
void lcd_command(uint8_t cmd);               // Gửi lệnh tới LCD
void lcd_data(uint8_t data);                 // Gửi dữ liệu (ký tự) tới LCD
void lcd_init(void);                         // Khởi tạo LCD
void lcd_clear(void);                        // Xóa màn hình LCD
void lcd_gotoxy(uint8_t x, uint8_t y);       // Đặt con trỏ LCD tại (x, y)
void lcd_puts(const char *str);              // Gửi chuỗi tới LCD
void lcd_putchar(char c);                    // Gửi một ký tự tới LCD

#endif
