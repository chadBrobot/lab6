/*
 * cheapStepper_simple.ino
 * ///////////////////////////////////////////
 * using CheapStepper Arduino library v.0.2.0
 * created by Tyler Henry, 7/2016
 * ///////////////////////////////////////////
 * 
 * this sketch illustrates basic step() functionality of the library:
 * the stepper performs a full rotation, pauses 1 second,
 * then does a full rotation in the other direction, and so on
 * 
 * //////////////////////////////////////////////////////
 */

// first, include the library :)

#include <CheapStepper.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4); 
CheapStepper stepper (26,27,28,29); 

//CheapStepper stepper;
// here we declare our stepper using default pins:
// arduino pin <--> pins on ULN2003 board:
// 26 <--> IN1
// 27 <--> IN2
// 28 <--> IN3
// 29 <--> IN4

 // let's create a boolean variable to save the direction of our rotation

#define button 25 
boolean moveClockwise = true;
int rot = 1056;
int potpin = A7;
#define led 14

void setup() {
  // let's just set up a serial connection and test print to the console
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  Serial.println("Ready to start moving!");
}

void rotateStep(int angle){
  angle = map(angle, 0, 359, 0, rot);
  for (int s=0; s<angle; s++){    
    stepper.step(moveClockwise);
    delay(5);
//    int nStep = stepper.getStep();
  }
//  delay(1000);  
  moveClockwise = !moveClockwise;
  }

void loop() {
  int val = analogRead(potpin);  // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 359);     // scale it to use it with the servo (value between 0 and 180
  lcd.setCursor(0,0);
  lcd.print("Angle: ");
  lcd.setCursor(0,1);
  lcd.print("       ");
  lcd.setCursor(0,1);
  lcd.print(val);
 
  int but = 1;
  but = digitalRead(button);
  delay(50);
  if (but == 0){
    rotateStep(val);
    digitalWrite(led, HIGH);
    delay(1000);
  }
  else{
  digitalWrite(led, LOW);
  }
}
