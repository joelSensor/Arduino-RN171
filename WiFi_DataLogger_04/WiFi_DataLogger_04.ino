/*

ESTABLISH CONNECTION TO THE RN-171 WIFI MODULE USING AT COMMAND SET
SETS UP THE ARDUINO AS A FEED THROUGH FOR TERMINAL WINDOW
SCAN FOR AVAILABLE HUBS, EVALUATE SETTINGS, AND MORE

*/

#define PACHUBEFEED ""
#define APIKEY ""

#include <SoftwareSerial.h>  // use software serial to talk to RN-171
#include <avr/sleep.h>


//#define TCN75A 0x4F  // I2C address for temp sensor
#define TCN75A  0x9E
#define Config  0x01  // ADDRESS OF TCN75A CONFIG REGISTER

SoftwareSerial WiFi(5,4); // name and rx,tx pins. option to invert the logic here as well
//  temp sensor variables
byte decimalLeft;
byte decimalRight;
int TempData;
int Celcius;
int Resolution;
volatile int cycles = 0;
int lastCycles = 0;

char inByte;
char outByte;
unsigned int milliVolts;
                     
int conState;
int lastConState = 0;

boolean test;


void setup(){
 Serial.begin(19200);
 WiFi.begin(9600); 
 pinMode(3,INPUT);  //pin 3 connected to WiFi GPIO6 which goes high when connected to remote host
 Serial.println("it's on!");
 getVoltage();
 getVoltage();
 I2C_Write(TCN75A,0x01,0x20);  // set the resolution. later set hysteresis, etc
 
 
 set_sleep_mode(SLEEP_MODE_PWR_DOWN);     // sleep mode is set here Power Down uses the least current
 
 delay(1000);
 
// Serial.print("entering command mode\t");
// WiFi.print("$$$");            // send the escape sequence
// if (verify('C')){             // look for C in CMD response
//   Serial.println("success"); 
// }else{
//   Serial.println("fail");
//   Serial.print("test if already in command mode\t");
//   WiFi.print("\r");           // send carriage return to clear the UART
//   if (verify('E')){            // look for ERR response
//     Serial.println("success");    // already in command mode
//   }else{
//     Serial.println("fail");  // something is truely fucked up
//   }
// }
// delay(1000);
// Serial.print("setting uart mode\t");
// WiFi.print("set uart mode 1\r");
// if (verify('A')){
//   Serial.println("success"); 
// }else{
//   Serial.println("fail");
// }
 
// Serial.print("exit command mode\t");
// WiFi.print("exit\r");
// if (verify('X')){
//   Serial.println("success"); 
// }else{
//   Serial.println("fail");
// }
 
 Serial.println("GOTO loop");
}// end of setup


void loop(){    // loop acts as feed-through to IDE serial window

  while (WiFi.available()>0){
    inByte = WiFi.read();
    Serial.print(inByte);
   }
  
  while (Serial.available()>0){
    outByte = Serial.read();
    WiFi.print(outByte);
    }
 
 
  if (digitalRead(3) == HIGH){
    
    Serial.println("getVoltage");
    getVoltage();
    Serial.println("getTemp");
    TempData = I2C_Read(TCN75A,0x00);
    Celcius = highByte(TempData);
    Resolution = 25 * (lowByte(TempData) >> 6);
    Serial.print(Celcius);
    Serial.print(".");
    Serial.print(Resolution);
    Serial.println("*C");
    Serial.print(milliVolts);
    Serial.println(" mV");
    PUTdata();
    delay(1000);
    system_sleep();
    delay(500);
  }else{
    system_sleep();
    delay(500);
  }

   
}// end of loop


boolean verify(char toMatch){
  unsigned long timer = millis() + 5000;  // 5 second timer on UART response
  char match;
  while(millis() < timer){                // using a timer so as not to hang
    if (WiFi.available()){                // SoftwareSerial needs TLC
      match = WiFi.read();           
//      Serial.println(match);         // debugging
      if(toMatch == match){
        timer = millis() + 2000;
        while(millis() < timer){     // this part reads out
          match = WiFi.read();       // the rest of the response transmission
          if (match == '\n'){        // to clear the SoftSerial buffer
            return true;             // leaves version# "<2.32>" in buffer
            }
          }
      }
    }
  }
        return false;
  }  // end of verify function





void getVoltage(){
  ADMUX = 0x4E;                    // set reference to VAcc and input to 1.1V band-gap
  ADCSRA |= 0x40;                  // start conversion
  while(!ADIF){}                   // wait for conversion to finish
  int i = ADCL + (ADCH << 8);      // get ADC result
  milliVolts = (102400/i) * 11;    // calculate voltage

//  Serial.println(milliVolts);
}


