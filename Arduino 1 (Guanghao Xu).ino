/* 
  Author Guanghao Xu

  Description:
     This part of the program is for the first arduino (master). We use the I2C protocol 
     to connect the four arduinos together. This part mainly involves using a receiver to
     receive infrared remote control signals, and then distributing the signals to other arduinos.  
     Use pin7 for receiving signals.

     When the power key signal is read, it is passed to the second Arduino to turn on and off the
     fluorescent lamp. When the number key 3 is read, have the third arduino turn off the alarm clock. 
    When the number key 6 is read, have the third arduino set the alarm clock.
*/


#include "IRremote.h"
#include <Wire.h>
#define SLAVE1_ADDR 9
#define SLAVE2_ADDR 8
#define SLAVE3_ADDR 7

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  Wire.begin();
}

void loop(){
  if (irrecv.decode(&results)){
    Serial.println(results.value, HEX);
    // delay(50);
    Wire.beginTransmission(SLAVE1_ADDR);
    Wire.write(results.value);
    Wire.endTransmission();
    Wire.beginTransmission(SLAVE2_ADDR);
    Wire.write(results.value);
    Wire.endTransmission();
    Wire.beginTransmission(SLAVE3_ADDR);
    Wire.write(results.value);
    Wire.endTransmission();
    irrecv.resume();
  }
}
