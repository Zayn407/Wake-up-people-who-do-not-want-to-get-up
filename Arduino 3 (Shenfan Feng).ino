/*
  Author Shenfan Feng

  Description: 
    The code for arduino 3 for group project
    show the time of alarm on first line and current time on second line.
    use I2C connect to the arduino 1
    when receive the signal of IR (number 3), the buzzer will stop.
    when receive the signal of IR (number 6), the alarm time will be reset.

    use UART send signal to arduino 4 when the buzzer is making noise.
*/

#include <LiquidCrystal.h>
#include <Wire.h>
#define SLAVE2_ADDR 8

int rd;
char buz = '0';
int aseconds = 10;
int aminutes = 0;
int ahours = 0;

// Set the pins for the LCD and buzzer
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2, buzzerPin = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// loser
int loserTones[] = {300, 400, 500, 600, 700, 800, 900};
int numloser = 7;
int toneloser = 71;


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);   // Initialize the LCD with 16 columns and 2 rows
  pinMode(buzzerPin, OUTPUT);  // Initialize the buzzer pin as an output
  Wire.begin(SLAVE2_ADDR);
  Wire.onReceive(receiveEvent);
}

void receiveEvent(){
  rd = Wire.read();
  // Serial.println(rd);
}

void loop() {
  unsigned long currentTime = millis();  // Get the current time in milliseconds
  unsigned int seconds = currentTime / 1000;  // Convert the time to seconds
  unsigned int minutes = seconds / 60;  // Convert the time to minutes
  unsigned int hours = minutes / 60;   // Convert the time to hours
  minutes = minutes % 60;  // Get the remaining minutes after subtracting the hours
  seconds = seconds % 60;  // Get the remaining seconds after subtracting the minutes

  // Reset the time to 0 after 24 hours
  if (hours >= 24) {
    hours = 0;
    minutes = 0;
    seconds = 0;
  }
  
  // Print the time on the LCD
  lcd.setCursor(3, 0);  // Move the cursor to the middle of the first row
  // lcd.print("Current Time");
  if (ahours < 10) {
    lcd.print("0");  // Add a leading zero for hours less than 10
  }
  lcd.print(ahours);
  lcd.print(":");
  if (aminutes < 10) {
    lcd.print("0");  // Add a leading zero for minutes less than 10
  }
  lcd.print(aminutes);
  lcd.print(":");
  if (aseconds < 10) {
    lcd.print("0");  // Add a leading zero for seconds less than 10
  }
  lcd.print(aseconds);
  
  lcd.setCursor(3, 1);  // Move the cursor to the middle of the second row
  if (hours < 10) {
    lcd.print("0");  // Add a leading zero for hours less than 10
  }
  lcd.print(hours);
  lcd.print(":");
  if (minutes < 10) {
    lcd.print("0");  // Add a leading zero for minutes less than 10
  }
  lcd.print(minutes);
  lcd.print(":");
  if (seconds < 10) {
    lcd.print("0");  // Add a leading zero for seconds less than 10
  }
  lcd.print(seconds);
  
  // Buzz the buzzer after 30 seconds
  if (hours==ahours&&minutes==aminutes&&seconds==aseconds){
    buz = '1';     
  }

  if (rd == 133){
    buz = '0';
    Serial.write(0);
  }

  if (rd == 165){
    delay(50);
    ahours = hours;
    aminutes = minutes;
    aseconds = seconds;
    aseconds += 10;
    if(aseconds > 60){
      aminutes ++;
      aseconds = aseconds%60;
    }
    delay(50);
  }

  Serial.write(buz);

  if (buz == '1') {
    lcd.setCursor(0, 0);  // Move the cursor to the first column of the first row
    lcd.print("Buzzer ON     "); // Display message on the LCD
  for (int i = 0; i < numloser; i++) {
    tone(buzzerPin, loserTones[i], toneloser);
    delay(toneloser);
  }
  noTone(buzzerPin);
    lcd.setCursor(0, 0);  // Move the cursor to the first column of the first row
    lcd.print("              "); // Clear the message on the LCD
  }
  
  delay(500);  // Wait for one second before updating the display again
}