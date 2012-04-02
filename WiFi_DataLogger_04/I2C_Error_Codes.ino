

/*
THIS FUNCTION PRINTS I2C ERROR CODES FROM THE ATMEL CHIP
*/


void ERROR(int j){
  Serial.print("TWSR = ");
  Serial.print(TWSR,HEX);
  Serial.print(" - ");
  Serial.println(j);
}



//  these are (some) Status values sent from TWSR on completion of transmission
//  useful for error checking during this test
//#define START    0x08      // START sent           08h
//#define rSTART   0x10      // repeated START sent  10h
//#define ACK_S_W  0x18      // ACK after SLA W      18h
//#define NACK_S_W 0x20      // nACK after SLA W     20h
//#define ACK_D_W  0x28      // ACK after DATA W     28h
//#define NACK_D_W 0x30      // nACK after DATA W    30h
//#define ACK_S_R  0x40      // ACK after SLA R      40h
//#define NACK_S_R 0x48      // nACK after SLA R     48h
//#define ACK_D_R  0x50      // ACK after DATA R     50h
//#define NACK_D_R 0x58      // nACK after DATA R    58h
//#define R_START  0x10      // Repeated Start       10h
