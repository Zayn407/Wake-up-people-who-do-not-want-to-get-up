/*
  Author1: Liwo Huang
  
  Description: 
  The code is working on arduino 2 for group project
  Arduino 2 is connect to arduino 1 by using commucation I2C
  LED will light on when receive sign from IR controller by press power button
  LED will light off when receive sign from IR controller by press power button again


*/

#include<Wire.h>
#define SLAVE1_ADDR 9
#define SLAVE2_ADDR 8
int LED = 8;
int rd;
bool LEDon = false;

void setup() {
  pinMode(LED,OUTPUT);
  Wire.begin(SLAVE1_ADDR);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

void receiveEvent(){
  rd = Wire.read();
  Serial.println(rd);
}

void loop(){
  if(rd == 93){
    if(LEDon == false){
      digitalWrite(LED,HIGH);
      LEDon = true;
    } else {
      digitalWrite(LED,LOW);
      LEDon = false;
    }
    rd = 0;
  }
}
