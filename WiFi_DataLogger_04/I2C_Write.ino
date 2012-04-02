
/*
THIS FUNCTION WRITES A BYTE TO THE I2C BUSS
*/

void I2C_Write(byte address,byte command,byte data){  

  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);    //send START (clear TWINT)
  while (!(TWCR & (1<<TWINT)));              //wait for TWINT to set
  if ((TWSR & 0xF8) != 0x08){ERROR(1);}      //barf TWSR if not as expected
  TWDR = address;                            //load address int TWDR
  TWCR = (1<<TWINT)|(1<<TWEN);               //clear TWINT and start transmission
  while (!(TWCR & (1<<TWINT)));              //wait for TWINT to set
  if ((TWSR & 0xF8) != 0x18){ERROR(2);}      //barf TWSR if not as expected
  TWDR = command;                            //load data into TWDR        
  TWCR = (1<<TWINT)|(1<<TWEN);               //clear TWINT and start transmission
  while (!(TWCR & (1<<TWINT)));              //wait for TWINT to set
  if ((TWSR & 0xF8) != 0x28){ERROR(3);}      //barf TWSR if not as expected
  TWDR = data;                               //load data into TWDR        
  TWCR = (1<<TWINT)|(1<<TWEN);               //clear TWINT and start transmission
  while (!(TWCR & (1<<TWINT)));              //wait for TWINT to set
  if ((TWSR & 0xF8) != 0x28){ERROR(4);}      //barf TWSR if not as expected
  TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);    //transmit STOP

}
