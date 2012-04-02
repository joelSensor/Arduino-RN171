

/*
THIS FUNCTION READS TWO BYTES FROM THE I2C BUSS
RETURNS AN INT WITH HIGH AND LOW BYTES MSB FIRST
*/


int I2C_Read(byte address,byte command){  
  byte data_L;
  byte data_H;
  int data;  
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);      //send START (clear TWINT)
    while (!(TWCR & (1<<TWINT)));              //wait for TWINT to set
    if ((TWSR & 0xF8) != 0x08){ERROR(5);}      //barf TWSR if not as expected
  TWDR = address;                              //load address int TWDR
  TWCR = (1<<TWINT)|(1<<TWEN);                 //clear TWINT and start transmission
    while (!(TWCR & (1<<TWINT)));              //wait for TWINT to set
    if ((TWSR & 0xF8) != 0x18){ERROR(6);}      //barf TWSR if not as expected
  TWDR = command;                              //load command into TWSR
  TWCR = (1<<TWINT)|(1<<TWEN);                 //clear TWINT and start transmission
    while (!(TWCR & (1<<TWINT)));              //wait for TWINT to set
    if ((TWSR & 0xF8) != 0x28){ERROR(7);}      //barf TWSR if not as expected
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);      //send repeated START (clear TWINT)
    while (!(TWCR & (1<<TWINT)));              //wait for TWINT to set
    if ((TWSR & 0xF8) != 0x10){ERROR(8);}      //barf TWSR if not as expected
  address ++;                                  //set READ bit in address byte
  TWDR = address;                              //load READ address into TWDR
  TWCR = (1<<TWINT)|(1<<TWEN);                 //clear TWINT, start transmission
    while (!(TWCR & (1<<TWINT)));              //wait for TWINT to set
    if ((TWSR & 0xF8) != 0x40){ERROR(9);}      //barf TWSR if not as expected
  TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);       //clear TWINT, start transmission, enable ACK
    while (!(TWCR & (1<<TWINT)));              //wait for TWINT to set
    if ((TWSR & 0xF8) != 0x50){ERROR(10);}     //barf TWSR if not as expected
  data_H = TWDR;                               //read TWDR into data High Byte 
  TWCR = (1<<TWINT)|(1<<TWEN);                 //clear TWINT, start read transmission
    while (!(TWCR & (1<<TWINT)));              //wait for TWINT to set
    if ((TWSR & 0xF8) != 0x58){ERROR(11);}     //barf TWSR if not as expected
  data_L = TWDR;                               //read TWDR into data Low Byte
  TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);      //transmit STOP
  data = data_H;
  data = (data << 8) + data_L;
  return data;
}
