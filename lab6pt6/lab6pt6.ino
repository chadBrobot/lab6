/*
Lab 6 part 4: 
Breann Thiessen and Jack Irishman
*/

#include <Wire.h>
#include <VL53L1X.h>
#include <CheapStepper.h>
VL53L1X sensor;
#define button 25 
#include <SPI.h>
#include <SD.h>

File myFile;

CheapStepper stepper (26,27,28,29); 
//CheapStepper stepper;
// here we declare our stepper using default pins:
// arduino pin <--> pins on ULN2003 board:
// 26 <--> IN1
// 27 <--> IN2
// 28 <--> IN3
// 29 <--> IN4
int rot = 1056;
boolean moveClockwise = true;
int printMe;
void setup()
{
  pinMode(button, INPUT);
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C
  stepper.setTotalSteps(1056);
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
void rotateStep(int angle){
  angle = map(angle, 0, 360, 0, rot);
  for (int s=0; s<angle; s++){    
    printMe = map(s, 0, rot, 0, 360);
    stepper.step(moveClockwise);
    int nStep = stepper.getStep();
    int cm = sensor.read()/10;
    myFile.print(cm);
    myFile.print("\t");
    myFile.println(printMe);
  }
  delay(1000);  
  moveClockwise = !moveClockwise;
  }

void loop()
{

  rotateStep(355);
  myFile.close();
  while(1){}
  
  /*
    int cm = sensor.read()/10;
    //
    delay(100);  
    Serial.print(s);
    Serial.print("\t");
    Serial.println(cm);*/
  
}
