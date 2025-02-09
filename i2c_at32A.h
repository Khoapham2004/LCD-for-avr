/*thư viện được viết dựa trên 
https://www.youtube.com/watch?v=QyoLxOkJcKY
https://www.electronicwings.com/avr-atmega/atmega1632-i2c
https://www.hocavr.com/2018/06/bai-8-giao-tiep-twi-i2c.html
https://controllerstech.com/avr-7-i2c-master-part-3-interface-lcd1602-via-i2c/
lưu ý thư viện viết cho i2c của Atmega32A
*/
#ifndef I2C_H
#define I2C_H
#include <avr/io.h>


void i2c_init(){
	TWBR = 0x62;		//	Baud rate is set by calculating 
	TWCR = (1<<TWEN);	//Enable I2C
	TWSR = 0x00;		//Prescaler set to 1 

}
		//Start condition
void i2c_start(){
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA);	//start condition
	while (!(TWCR & (1<<TWINT)));				//check for start condition

}
		//I2C stop condition
void i2c_write(char x){				//Cpn esta funcion se escribe en el bus de TWDR
	TWDR = x;						//Move value to I2C
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
}

char i2c_read(){
	TWCR  = (1<<TWEN) | (1<<TWINT);	//Enable I2C and clear interrupt
	while (!(TWCR & (1<<TWINT)));	//Read successful with all data received in TWDR
	return TWDR;
}

#endif
