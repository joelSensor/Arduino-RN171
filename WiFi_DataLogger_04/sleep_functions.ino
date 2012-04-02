


void system_sleep() {
  attachInterrupt(1,wakeUp,CHANGE);
  Serial.println("sleeping");
  delay(100);
//  digitalWrite(powerGate,HIGH);            // pull MOSFET high to turn off the rest of the circuit
  ADCSRA |= (0<<ADEN);                     // disable ADC
  sleep_enable();                          // enable sleeping
  
    sleep_mode();                          // activate system sleep
    // sleeping ... 
    
  sleep_disable();                         // disable sleep  
  ADCSRA |= (1<<ADEN);                     // switch ADC on 
  delay(100);
  Serial.print("waking up ");
  Serial.print(cycles);
  Serial.print("\t");
  Serial.println(digitalRead(3));
//  digitalWrite(powerGate,LOW);             // turn on rest of circuit
  detachInterrupt(1);
}


// External Interrupt on pin 3 will wake arduino from sleep

void wakeUp(){
    cycles++;
}
