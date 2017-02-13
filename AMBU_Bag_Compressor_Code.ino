#include <Servo.h>
  int servoSpeed == 0;
  int servoDepth == 0;
  int servoPos == 0;
  int breathInterval == 2;
  int setBreathAmount == 2;
  int loopRun == 0;
  Servo arm;
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  arm.attach(A5);
}

void loop() {
  // put your main code here, to run repeatedly:
  breathInterval = analogRead(A1);
  breathInterval = map(breathInterval, 0, 1023, 1, 8);
 
  servoDepth = analogRead(A2);
  servoDepth = map(servoDepth, 0, 1023, 0, 180);
 
  servoSpeed = analogRead(A3);
  servoSpeed = map(servoSpeed, 0, 1023, 0, 30);
 
  setBreathAmount = analogRead(A4);
  setBreathAmount = map(setBreathAmount, 0, 1023, 0, 5);
 
  loopRun = analogRead(A0);
  int loopRound = 0;
  
  while(loopRun == 1) {
    //starts the program when button is pressed
    int breathAmount == 0; 
    while(breathAmount <= setBreathAmount) {
      while (servoPos < servoDepth) {
        
      }
    }
  }
}
