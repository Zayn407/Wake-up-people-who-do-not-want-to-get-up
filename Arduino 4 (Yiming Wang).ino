/*
  Author: Yiming Wang
  Description:
  The code for Arduino 4 for group project
  
  use UART cummunication to connect with Arduino 3
  When it receives a signal from Arduino 3, it will begin to count down 300 seconds. 
  During that time, it will continue counting down with the buzzer is on. 
  When the buzzer is off, it will reset to 300 seconds for the next time's use
*/

// 4 digit 7 segment library
#include "SevSeg.h"

// Set up our display
SevSeg sevseg; 

// Number to display
#define totalCount 300;
int counter = totalCount;

// How long to delay
#define delayTime 1000

char m;

void setup()
{
  
  // My display has 4 digits
  byte numDigits = 4;
  
  // These are the arduino pins that switch
  // between these 4 digits
  byte digitPins[] = {6,3,2,12};
  
  // These refer to the segments/LEDs of 
  // each digit
  byte segmentPins[] = {5,13,10,8,7,4,11,9};
  
  // Strictly speaking should be using 330ohm resistors 
  bool resistorsOnSegments = false;
  
  // Your display will either be common anode or cathode
  byte hardwareConfig = COMMON_CATHODE;
  
  // Start the display
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  
  // Set brightness between 0 and 100
  sevseg.setBrightness(30);
  
  // Blank the display
  sevseg.blank();

  Serial.begin(9600);
}


void loop() {
  // unsigned long currentTime = millis();  // Get the current time in milliseconds
  // static unsigned long time = millis();

  sevseg.setNumber(counter, 0);
  if (Serial.available() > 0) {
    m = Serial.read();
    Serial.println(m);
  }
  // Serial.println(5);
  if (m == '1' ) {
      // if (Serial.available() > 0) {
      //   m = Serial.read();
      //   Serial.println(m);
      // }
    static unsigned long time = millis();
    // If the current millis is > 100 since timer ...
    if (millis() - time >= delayTime) {
      // Set the display 
      // Blink the decimal point
      if(counter % 2 == 0) {
        sevseg.setNumber(counter, 0);
      } else {
        sevseg.setNumber(counter, -1);
      }
      
      // Decrement the counter
      // until 0
      if( counter > 0 ) {
        counter--;
      } else {
        // Reset back to start        
        counter = totalCount;
        loop();
      }

      // if (m == '0') {
      //   counter = 300;
      //   Serial.println(100);
      //   sevseg.refreshDisplay(); 
      //   loop();
      // }
      
      // Update the timer
      time = millis();

    } 
    // Update the display
    // Must run repeatedly
    sevseg.refreshDisplay(); 
  }
  else {
        counter = 300;
        // Serial.println(100);
        // sevseg.refreshDisplay(); 
    }


  sevseg.refreshDisplay(); 
}

