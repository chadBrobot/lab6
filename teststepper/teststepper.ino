/*
Lab 6 part 4: 
Breann Thiessen and Jack Irishman
*/

#include <Wire.h>
#include <VL53L1X.h>
#include <Stepper.h>
VL53L1X sensor;
#define button 25 
#include <SPI.h>
#include <SD.h>

File myFile;

//CheapStepper stepper;
// here we declare our stepper using default pins:
// arduino pin <--> pins on ULN2003 board:
// 26 <--> IN1
// 27 <--> IN2
// 28 <--> IN3
// 29 <--> IN4
int rot = 1056;
boolean moveClockwise = false;
Stepper myStepper(1056,26,27,28,29);
 
void setup()
{
   myStepper.setSpeed(60);
  pinMode(button, INPUT);
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1);
  }
   if (!SD.begin(53)) {
    Serial.println("initialization failed!");
    while (1);
  }
  
  sensor.setDistanceMode(VL53L1X::Long);
  sensor.setMeasurementTimingBudget(50000);
  sensor.startContinuous(50);
   myFile = SD.open("pencily.txt", FILE_WRITE);
}

void loop()
{
  myStepper.step(1056);
  delay(1000);
  myStepper.step(-1056);
  delay(1000);
  //rotateStep(359);
  
  /*
    int cm = sensor.read()/10;
    //Serial.println(cm);
    delay(100);  
    Serial.print(s);
    Serial.print("\t");
    Serial.println(cm);*/
  
}
