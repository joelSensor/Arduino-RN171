/*

ESTABLISH CONNECTION TO THE RN-171 WIFI MODULE USING AT COMMAND SET
SETS UP THE ARDUINO AS A FEED THROUGH FOR TERMINAL WINDOW
SCAN FOR AVAILABLE HUBS, EVALUATE SETTINGS, AND MORE

*/

#define PACHUBEFEED ""
#define APIKEY ""

#include <SoftwareSerial.h>  // use software serial to talk to RN-171

SoftwareSerial WiFi(5,4); // name and rx,tx pins. option to invert the logic here as well


char inByte;
char outByte;
unsigned int milliVolts;
                     
int RTS = 3;
int lastRTS = 0;

boolean test;


void setup(){
 Serial.begin(19200);
 WiFi.begin(9600); 
 pinMode(RTS,INPUT);  //pin 3 connected to WiFi RTS
 Serial.println("it's on!");
 getVoltage();
 getVoltage();
 delay(1000);
 
 Serial.print("entering command mode\t");
 WiFi.print("$$$");            // send the escape sequence
 if (verify('C')){             // look for C in CMD response
   Serial.println("success"); 
 }else{
   Serial.println("fail");
   Serial.print("test if already in command mode\t");
   WiFi.print("\r");           // send carriage return to clear the UART
   if (verify('E')){            // look for ERR response
     Serial.println("success");    // already in command mode
   }else{
     Serial.println("fail");  // something is truely fucked up
   }
 }
 delay(1000);
 Serial.print("setting uart mode\t");
 WiFi.print("set uart mode 1\r");
 if (verify('A')){
   Serial.println("success"); 
 }else{
   Serial.println("fail");
 }
 
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


void PUTdata(){
  
    String stuff = "Temperature,"+String(random(100))+"\nVoltage,"+milliVolts;
    WiFi.print("PUT /v2/feeds/");
    WiFi.print(PACHUBEFEED);
    WiFi.println(".csv HTTP/1.1");
    WiFi.println("Host: api.pachube.com");
    WiFi.print("X-PachubeApiKey: ");
    WiFi.println(APIKEY);
    WiFi.println("User-Agent: Arduino (WiFi RN-171)");
    WiFi.print("Content-Type: text/csv\nContent-Length: ");
    WiFi.println(stuff.length());
    WiFi.println("Connection: close");
    WiFi.println();
    WiFi.println(stuff);

}


void getVoltage(){
  ADMUX = 0x4E;                    // set reference to VAcc and input to 1.1V band-gap
  ADCSRA |= 0x40;                  // start conversion
  while(!ADIF){}                   // wait for conversion to finish
  int i = ADCL + (ADCH << 8);      // get ADC result
  milliVolts = (102400/i) * 11;    // calculate voltage

//  Serial.println(milliVolts);
}


