//Authors: Jack Casey Campbell and Breann Thiessen
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
#include <NewPing.h>
#define TRIGGER_PIN  32  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     32  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#include "MedianFilterLib.h"

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int but;
int val;    // variable to read the value from the analog pin
int foundDist = 200;
int foundAng =0;
int shoot [180];
MedianFilter<int> medianFilter(10);

void setup() {
  myservo.attach(9);       // attaches the servo on pin 9 to the servo object
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  Serial.begin(115200);
  lcd.setCursor(0,0);
  lcd.print("Angle: ");
}
void loop() {
  int angle = 0;
  int median;
  int prevRead = sonar.ping_cm();
  int currRead;
  while (angle <= 180){
  
    for(int i = 0; i < 10; i++){
      currRead = sonar.ping_cm();
      if(currRead - prevRead < 25){
         median = medianFilter.AddValue(sonar.ping_cm());    
         prevRead = currRead;
      }    
    }
    shoot[angle] = median;
    if(foundDist>median && median > 3){
      foundDist = median;
      foundAng = angle;
      Serial.println(foundDist);
      Serial.println(foundAng);
    }
   

    lcd.setCursor(0,1);
    lcd.print(foundAng);
    delay(50);
    myservo.write(angle);                  // sets the servo position according to the scaled value
    delay(50);                           // waits for the servo to get there
    //lcd.clear();
    angle++;
  }
  int nextMin;
  for(int i = 0; i < 180; i++){
      if(foundDist + (foundDist *0.1) > shoot[i]){
        nextMin = i;
      }  
    }
  Serial.println(foundAng);
  Serial.println(nextMin);
  foundAng = ((nextMin + foundAng) /2);
  myservo.write(foundAng);
  while(1){}  
}
