//Trình tự hoạt động 
/*
Phân tích hàm lcd_data:
Mục đích:
Hàm này gửi dữ liệu 8-bit đến LCD ở chế độ 4-bit. Mỗi lần gửi, dữ liệu được chia thành 4 bit cao và 4 bit thấp.
Các bước thực hiện trong hàm:
RS = 1: Đặt chân RS (Register Select) thành 1, để LCD hiểu rằng đây là dữ liệu, không phải lệnh.
RD = 0: Đặt chân RD thành 0, báo hiệu ghi dữ liệu (write mode).
Gửi 4 bit cao: Chia 8 bit thành 4 bit cao (bits 7..4) và gửi chúng qua các chân dữ liệu d7, d6, d5, và d4.
Kích xung EN: Kích hoạt tín hiệu EN (Enable) để LCD chấp nhận dữ liệu.
Gửi 4 bit thấp: Gửi 4 bit thấp (bits 3..0) tương tự như trên.
Kích xung EN lần nữa: Kích hoạt EN lần nữa để LCD nhận 4 bit thấp.
Delay: Đợi một thời gian để LCD xử lý (ít nhất 2 ms).

Quá trình hoạt động khi in "HELLO":
Khi gọi lcd_puts("HELLO");, chương trình thực hiện như sau:

Gửi ký tự 'H':
data = 'H' = 0x48 (hex) = 0100 1000 (nhị phân).
Gửi 4 bit cao 0100:
d7 = 0, d6 = 1, d5 = 0, d4 = 0.
Kích xung EN.
Gửi 4 bit thấp 1000:
d7 = 1, d6 = 0, d5 = 0, d4 = 0.
Kích xung EN.

Gửi ký tự 'E':
data = 'E' = 0x45 (hex) = 0100 0101 (nhị phân).
Gửi 4 bit cao 0100:
d7 = 0, d6 = 1, d5 = 0, d4 = 0.
Kích xung EN.
Gửi 4 bit thấp 0101:
d7 = 0, d6 = 1, d5 = 0, d4 = 1.
Kích xung EN.

Gửi ký tự 'L':
data = 'L' = 0x4C (hex) = 0100 1100 (nhị phân).
Gửi 4 bit cao 0100:
d7 = 0, d6 = 1, d5 = 0, d4 = 0.
Kích xung EN.
Gửi 4 bit thấp 1100:
d7 = 1, d6 = 1, d5 = 0, d4 = 0.
Kích xung EN.

Gửi ký tự 'L' (lần 2):
Quy trình giống ký tự 'L' ở trên.

Gửi ký tự 'O':
data = 'O' = 0x4F (hex) = 0100 1111 (nhị phân).
Gửi 4 bit cao 0100:
d7 = 0, d6 = 1, d5 = 0, d4 = 0.
Kích xung EN.
Gửi 4 bit thấp 1111:
d7 = 1, d6 = 1, d5 = 1, d4 = 1.
Kích xung EN.

*/

#include "lcd.h"

// Biến lưu cấu hình các chân
static LCD_Pin rs, rd, en, d4, d5, d6, d7;

// Hàm thiết lập các chân của LCD
void lcd_set_pins(LCD_Pin rs_pin, LCD_Pin rd_pin, LCD_Pin en_pin, LCD_Pin d4_pin, LCD_Pin d5_pin, LCD_Pin d6_pin, LCD_Pin d7_pin)
{
    rs = rs_pin;
    rd = rd_pin;
    en = en_pin;
    d4 = d4_pin;
    d5 = d5_pin;
    d6 = d6_pin;
    d7 = d7_pin;

    // Cấu hình tất cả các chân làm output
    *rs.ddr |= (1 << rs.bit);
    *rd.ddr |= (1 << rd.bit);
    *en.ddr |= (1 << en.bit);
    *d4.ddr |= (1 << d4.bit);
    *d5.ddr |= (1 << d5.bit);
    *d6.ddr |= (1 << d6.bit);
    *d7.ddr |= (1 << d7.bit);
}

// Hàm gửi lệnh tới LCD
void lcd_command(uint8_t cmd)
{
    // RS = 0 (Chế độ lệnh)
    *rs.port &= ~(1 << rs.bit);
    *rd.port &= ~(1 << rd.bit);

    // Gửi 4 bit cao
    *d7.port = (*d7.port & ~(1 << d7.bit)) | ((cmd & 0x80) ? (1 << d7.bit) : 0);
    *d6.port = (*d6.port & ~(1 << d6.bit)) | ((cmd & 0x40) ? (1 << d6.bit) : 0);
    *d5.port = (*d5.port & ~(1 << d5.bit)) | ((cmd & 0x20) ? (1 << d5.bit) : 0);
    *d4.port = (*d4.port & ~(1 << d4.bit)) | ((cmd & 0x10) ? (1 << d4.bit) : 0);

    // Kích xung EN
    *en.port |= (1 << en.bit);
    _delay_us(1);
    *en.port &= ~(1 << en.bit);

    // Gửi 4 bit thấp
    *d7.port = (*d7.port & ~(1 << d7.bit)) | ((cmd & 0x08) ? (1 << d7.bit) : 0);
    *d6.port = (*d6.port & ~(1 << d6.bit)) | ((cmd & 0x04) ? (1 << d6.bit) : 0);
    *d5.port = (*d5.port & ~(1 << d5.bit)) | ((cmd & 0x02) ? (1 << d5.bit) : 0);
    *d4.port = (*d4.port & ~(1 << d4.bit)) | ((cmd & 0x01) ? (1 << d4.bit) : 0);

    // Kích xung EN lần nữa
    *en.port |= (1 << en.bit);
    _delay_us(1);
    *en.port &= ~(1 << en.bit);

    _delay_ms(2);
}

// Hàm gửi dữ liệu (ký tự) tới LCD
void lcd_data(uint8_t data)
{
    // RS = 1 (Chế độ dữ liệu)
    *rs.port |= (1 << rs.bit);
    *rd.port &= ~(1 << rd.bit);

    // Gửi 4 bit cao
    *d7.port = (*d7.port & ~(1 << d7.bit)) | ((data & 0x80) ? (1 << d7.bit) : 0);
    *d6.port = (*d6.port & ~(1 << d6.bit)) | ((data & 0x40) ? (1 << d6.bit) : 0);
    *d5.port = (*d5.port & ~(1 << d5.bit)) | ((data & 0x20) ? (1 << d5.bit) : 0);
    *d4.port = (*d4.port & ~(1 << d4.bit)) | ((data & 0x10) ? (1 << d4.bit) : 0);

    // Kích xung EN
    *en.port |= (1 << en.bit);
    _delay_us(1);
    *en.port &= ~(1 << en.bit);

    // Gửi 4 bit thấp
    *d7.port = (*d7.port & ~(1 << d7.bit)) | ((data & 0x08) ? (1 << d7.bit) : 0);
    *d6.port = (*d6.port & ~(1 << d6.bit)) | ((data & 0x04) ? (1 << d6.bit) : 0);
    *d5.port = (*d5.port & ~(1 << d5.bit)) | ((data & 0x02) ? (1 << d5.bit) : 0);
    *d4.port = (*d4.port & ~(1 << d4.bit)) | ((data & 0x01) ? (1 << d4.bit) : 0);

    // Kích xung EN lần nữa
    *en.port |= (1 << en.bit);
    _delay_us(1);
    *en.port &= ~(1 << en.bit);

    _delay_ms(2);
}

// Hàm khởi tạo LCD
void lcd_init(void)
{
    _delay_ms(20);  // Chờ LCD khởi động
    lcd_command(0x02);  // Chế độ 4-bit
    if (LCD_TYPE == LCD_16x2) {
        lcd_command(0x28);  // 2 dòng, ma trận 5x7 cho LCD 16x2
    } else {
        lcd_command(0x28);  // 4 dòng, ma trận 5x8 cho LCD 20x4
    }
    lcd_command(0x0C);  // Bật màn hình, tắt con trỏ
    lcd_command(0x06);  // Tăng con trỏ
    lcd_command(0x01);  // Xóa màn hình
    _delay_ms(2);
}

// Hàm xóa màn hình LCD
void lcd_clear(void)
{ 
     _delay_ms(2);
    lcd_command(0x01);
    //khúc này là tui bí quá nên viết như v :)) nên dùng hàm lcd_command(0x01); ở trên là tốt nhất
/*
    *rs.port = 0x00;
    *rd.port = 0x00;
    *en.port = 0x00;
    *d4.port = 0x00;
    *d5.port = 0x00;
    *d6.port = 0x00;
    *d7.port = 0x00;
    */
}

// Ghi chuỗi lên LCD
void lcd_puts(const char *str)
{
    while (*str)
    {
        lcd_data(*str++);
    }
}

// Ghi một ký tự lên LCD
void lcd_putchar(char c)
{
    lcd_data(c);
}

// Hàm đặt con trỏ LCD tại (x, y)
void lcd_gotoxy(uint8_t x, uint8_t y) {
     uint8_t pos;
    if (LCD_TYPE == LCD_16x2) {
        if (y == 0) {
            pos = 0x80 + x;  // Dòng 1
        } else if (y == 1) {
            pos = 0xC0 + x;  // Dòng 2
        }
    } else if (LCD_TYPE == LCD_20x4) {
        if (y == 0) {
            pos = 0x80 + x;  // Dòng 1
        } else if (y == 1) {
            pos = 0xC0 + x;  // Dòng 2
        } else if (y == 2) {
            pos = 0x94 + x;  // Dòng 3
        } else if (y == 3) {
            pos = 0xD4 + x;  // Dòng 4
        }
    }
    lcd_command(pos);  // Đặt con trỏ tại vị trí
}

