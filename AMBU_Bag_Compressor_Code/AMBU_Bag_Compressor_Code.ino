#include <SoftwareSerial.h>
#include <Servo.h>
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Servo arm;
  arm.attach(2);
  int breathInterval = analogRead(A1);
    breathInterval = map(breathInterval, 0, 1023, 1000, 7000);
  int servoDepth = analogRead(A2);
    servoDepth = map(servoDepth, 0, 1023, 0, 180);
  int servoSpeed = analogRead(A3);
    servoSpeed = map(servoSpeed, 0, 1023, 0, 30);
  int setBreathAmount = analogRead(A4);
    setBreathAmount = map(setBreathAmount, 0, 1023, 0, 5);
  int servoPos = 0;
  int loopRun = analogRead(A0);
  int loopRound = 0;

  Serial.print("Interval: "); Serial.print(breathInterval); Serial.print("\t");
  Serial.print("Depth: "); Serial.print(servoDepth); Serial.print("\t");
  Serial.print("Speed: "); Serial.print(servoSpeed); Serial.print("\t");
  Serial.print("Amount: "); Serial.print(setBreathAmount); Serial.println("\t");

  while(loopRun = 0) {
    //starts the program when button is pressed
    int breathAmount = 0; 
    while(breathAmount <= setBreathAmount) {
      for (servoPos = servoPos; servoPos < servoDepth; servoPos -= servoSpeed){
        arm.write(servoPos);
        delay(15);
      }
      for (servoPos = servoPos; servoPos >= servoDepth; servoPos += servoSpeed){
        arm.write(servoPos);
        delay(breathInterval);
      }
      breathAmount = breathAmount + 1;
    }
  }
}
