/*thư viện được viết dựa trên 
https://www.youtube.com/watch?v=QyoLxOkJcKY
https://www.electronicwings.com/avr-atmega/atmega1632-i2c
https://www.hocavr.com/2018/06/bai-8-giao-tiep-twi-i2c.html
https://controllerstech.com/avr-7-i2c-master-part-3-interface-lcd1602-via-i2c/
lưu ý thư viện viết cho i2c của Atmega328p
*/

#include <avr/io.h>

void i2c_init(){
    TWSR = 0x00;           // Set the prescaler to 1 (no division)
    TWBR = 0x62;           // Set the I2C baud rate (calculated based on F_CPU and desired baud rate)
    TWCR = (1<<TWEN);      // Enable I2C
}

// Start condition
void i2c_start(){
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA);   // Generate START condition
    while (!(TWCR & (1<<TWINT)));                   // Wait for the START condition to be transmitted
}

// I2C stop condition
void i2c_stop(){
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);   // Generate STOP condition
    while (!(TWCR & (1<<TWINT)));                  // Wait for the STOP condition to be transmitted
}

// Write byte to I2C bus
void i2c_write(char x){
    TWDR = x;                                      // Load the byte to be transmitted
    TWCR = (1<<TWINT) | (1<<TWEN);                 // Start the transmission
    while (!(TWCR & (1<<TWINT)));                  // Wait for transmission to finish
}

// Read byte from I2C bus
char i2c_read(){
    TWCR = (1<<TWINT) | (1<<TWEN);                 // Enable I2C and clear interrupt flag
    while (!(TWCR & (1<<TWINT)));                  // Wait for data to be received
    return TWDR;                                   // Return received data
}
