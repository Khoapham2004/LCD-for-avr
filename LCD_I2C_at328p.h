/*thư viện được viết dựa trên 
https://www.youtube.com/watch?v=QyoLxOkJcKY
https://www.electronicwings.com/avr-atmega/atmega1632-i2c
https://www.hocavr.com/2018/06/bai-8-giao-tiep-twi-i2c.html
https://controllerstech.com/avr-7-i2c-master-part-3-interface-lcd1602-via-i2c/
lưu ý thư viện viết cho i2c của Atmega328p
*/
#ifndef LCD_I2C_H
#define LCD_I2C_H
#include <avr/io.h>
#include <util/delay.h>  // Include the delay library for _delay_ms

// Function prototypes
void lcd_init();			// LCD Initializing Function
void lcd_clear();
void toggle();				// Latching function of LCD
void lcd_cmd_hf(char v1);   // Function to send half-byte command to LCD
void lcd_cmd(char v2);		// Function to send Command to LCD
void lcd_dwr(char v3);		// Function to send data to LCD
void lcd_msg(char *c);		// Function to Send String to LCD
void lcd_lef_sh();			// Left Shifting Function
void lcd_rig_sh();			// Right Shifting Function
void lcd_gotoxy(uint8_t row, uint8_t col);  // Function to move cursor to specific position

// Latching function for the LCD
void toggle() {
    TWDR |= 0x02;  // Set Enable pin high to latch data
    TWCR = (1 << TWINT) | (1 << TWEN); // Enable TWI and clear interrupt
    while (!(TWCR & (1 << TWINT)));  // Wait for completion of the TWI operation
    _delay_ms(1);  // Small delay for stability
    TWDR &= ~0x02;  // Set Enable pin low
    TWCR = (1 << TWINT) | (1 << TWEN); // Enable TWI and clear interrupt
    while (!(TWCR & (1 << TWINT)));  // Wait for completion of the TWI operation
}

// Function to send a half byte command to LCD
void lcd_cmd_hf(char v1) {
    TWDR &= ~0x01;  // Set RS pin low (command mode)
    TWCR = (1 << TWINT) | (1 << TWEN);  // Enable TWI and clear interrupt
    while (!(TWCR & (1 << TWINT)));  // Wait for completion of the TWI operation
    TWDR &= 0x0F;  // Clear the higher 4 bits
    TWCR = (1 << TWINT) | (1 << TWEN);  // Enable TWI and clear interrupt
    while (!(TWCR & (1 << TWINT)));  // Wait for completion of the TWI operation
    TWDR |= (v1 & 0xF0);  // Mask and send the higher 4 bits
    TWCR = (1 << TWINT) | (1 << TWEN);  // Enable TWI and clear interrupt
    while (!(TWCR & (1 << TWINT)));  // Wait for completion of the TWI operation
    toggle();
}

// Function to send a command to the LCD
void lcd_cmd(char v2) {
    TWDR &= ~0x01;  // Set RS pin low (command mode)
    TWCR = (1 << TWINT) | (1 << TWEN);  // Enable TWI and clear interrupt
    while (!(TWCR & (1 << TWINT)));  // Wait for completion of the TWI operation
    TWDR &= 0x0F;  // Clear the higher 4 bits
    TWCR = (1 << TWINT) | (1 << TWEN);  // Enable TWI and clear interrupt
    while (!(TWCR & (1 << TWINT)));  // Wait for completion of the TWI operation
    TWDR |= (v2 & 0xF0);  // Mask and send the higher 4 bits
    TWCR = (1 << TWINT) | (1 << TWEN);  // Enable TWI and clear interrupt
    while (!(TWCR & (1 << TWINT)));  // Wait for completion of the TWI operation
    toggle();
    
    TWDR &= 0x0F;  // Clear the higher 4 bits
    TWCR = (1 << TWINT) | (1 << TWEN);  // Enable TWI and clear interrupt
    while (!(TWCR & (1 << TWINT)));  // Wait for completion of the TWI operation
    TWDR |= ((v2 & 0x0F) << 4);  // Mask and send the lower 4 bits
    TWCR = (1 << TWINT) | (1 << TWEN);  // Enable TWI and clear interrupt
    while (!(TWCR & (1 << TWINT)));  // Wait for completion of the TWI operation
    toggle();
}

// Function to send data to the LCD
void lcd_dwr(char v3) {
    TWDR |= 0x01;  // Set RS pin high (data mode)
    TWCR = (1 << TWINT) | (1 << TWEN);  // Enable TWI and clear interrupt
    while (!(TWCR & (1 << TWINT)));  // Wait for completion of the TWI operation
    TWDR &= 0x0F;  // Clear the higher 4 bits
    TWCR = (1 << TWINT) | (1 << TWEN);  // Enable TWI and clear interrupt
    while (!(TWCR & (1 << TWINT)));  // Wait for completion of the TWI operation
    TWDR |= (v3 & 0xF0);  // Mask and send the higher 4 bits
    TWCR = (1 << TWINT) | (1 << TWEN);  // Enable TWI and clear interrupt
    while (!(TWCR & (1 << TWINT)));  // Wait for completion of the TWI operation
    toggle();
    
    TWDR &= 0x0F;  // Clear the higher 4 bits
    TWCR = (1 << TWINT) | (1 << TWEN);  // Enable TWI and clear interrupt
    while (!(TWCR & (1 << TWINT)));  // Wait for completion of the TWI operation
    TWDR |= ((v3 & 0x0F) << 4);  // Mask and send the lower 4 bits
    TWCR = (1 << TWINT) | (1 << TWEN);  // Enable TWI and clear interrupt
    while (!(TWCR & (1 << TWINT)));  // Wait for completion of the TWI operation
    toggle();
}

// Function to initialize the LCD
void lcd_init() {
    lcd_cmd_hf(0x30);  // Initialize LCD in 8-bit mode
    lcd_cmd_hf(0x30);  // Second initialization command
    lcd_cmd_hf(0x20);  // Third initialization command to set 4-bit mode
    lcd_cmd(0x28);     // Set 4-bit interface mode
    lcd_cmd(0x0C);     // Display ON, Cursor OFF
    lcd_cmd(0x01);     // Clear the display
    lcd_cmd(0x06);     // Cursor auto-increment
    lcd_cmd(0x80);     // Set the cursor to the first line, first position
}

// Function to display a string on the LCD
void lcd_msg(char *c) {
    while (*c != 0) {
        lcd_dwr(*c++);  // Send the string to LCD
    }
}

// Function for right shift
void lcd_rig_sh() {
    lcd_cmd(0x1C);  // Command for right shift
    _delay_ms(400);  // Wait for a moment
}

// Function for left shift
void lcd_lef_sh() {
    lcd_cmd(0x18);  // Command for left shift
    _delay_ms(200);  // Wait for a moment
}

void lcd_clear() {
    lcd_cmd(0x01);  // Lệnh xóa màn hình LCD
    _delay_ms(2);   // Đợi LCD xử lý (~1.64ms)
}


// Function to move cursor to a specific position (gotoxy)
void lcd_gotoxy(uint8_t x, uint8_t y) {
    uint8_t position;
    /*
    if (    row == 0) {
        position = col;  // First row
    } else if (row == 1) {
        position = 0x40 + col;  // Second row
    } else {
        return;  // Invalid row (only 2 rows available)
    }

    lcd_cmd(0x80 | position);  // Set the cursor to the specified position
    */

    // Kiểm tra và xác định vị trí LCD
    if (y == 0) {
        position = 0x80 + x; // Đặt con trỏ ở dòng 1
    } else {
        position = 0xC0 + x; // Đặt con trỏ ở dòng 2
    }
    
    // Gửi lệnh đến LCD để di chuyển con trỏ
    lcd_cmd(position); 
}
#endif
