/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
#include <NewPing.h>
#define TRIGGER_PIN  48  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     48  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#include "MedianFilterLib.h"

#include <SPI.h>
#include <SD.h>

File myFile;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int but;
int val;    // variable to read the value from the analog pin


MedianFilter<int> medianFilter(10);
void setup() {
  myservo.attach(9);       // attaches the servo on pin 9 to the servo object
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  Serial.begin(115200);

  
  if (!SD.begin(53)) {
    Serial.println("initialization failed!");
    while (1);
  }

  myFile = SD.open("test.txt", FILE_WRITE);
}

void loop() {
  int angle = 0;
  int median;
  while (angle <= 180){

    for(int i = 0; i < 10; i++){
      median = medianFilter.AddValue(sonar.ping_cm());
    }
    Serial.println(median);
    myFile.print(angle);
    myFile.print("\t");
    myFile.print(median);
    myFile.println();
    lcd.setCursor(0,0);
    lcd.print("CM: ");
    lcd.setCursor(0,1);
    lcd.print(median);
    delay(50);
    myservo.write(angle);                  // sets the servo position according to the scaled value
    delay(50);                           // waits for the servo to get there
    lcd.clear();
    myFile.println();
    angle++;
  }
  myFile.close();
}
