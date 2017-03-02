#include <SoftwareSerial.h>
#include <Servo.h>

const int powerButtonPin = 13;
const int ledPin = 12;

int breathAmount = 0;

int pos = 90;

Servo arm;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  arm.attach(11);
  pinMode(ledPin, OUTPUT);
  pinMode(powerButtonPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

int loopRun = digitalRead(powerButtonPin);

int breathInterval = analogRead(A1);
  breathInterval = map(breathInterval, 0, 1023, 1000, 7000);
int servoDepth = analogRead(A2);
  servoDepth = map(servoDepth, 0, 1023, 10, 90);
int servoSpeed = analogRead(A3);
  servoSpeed = map(servoSpeed, 0, 1023, 0, 20);
int setBreathAmount = 3; //*analogRead(A4);
    setBreathAmount = map(setBreathAmount, 0, 1023, 0, 5);

  Serial.print("Interval: "); Serial.print(breathInterval); Serial.print("\t");
  Serial.print("Depth: "); Serial.print(servoDepth); Serial.print("\t");
  Serial.print("Speed: "); Serial.print(servoSpeed); Serial.print("\t");
  Serial.print("Amount: "); Serial.print(setBreathAmount); Serial.print("\t");
  Serial.print("Position: "); Serial.print(arm.read()); Serial.println("\t");
  
  digitalWrite(ledPin, LOW);

  if (loopRun == HIGH){
    //starts the program when button is pressed
    breathAmount = 0;
    digitalWrite(ledPin, HIGH);
    
    tone(10, 330, 200);
    delay(200);
    tone(10, 660, 200);
   
  
    while (breathAmount <= 3) {
      Serial.print("Breath: "); Serial.print(breathAmount); Serial.print("\t");
      for (pos = 90; pos >= servoDepth; pos -= servoSpeed){
        arm.write(pos);
        Serial.print("Depth: "); Serial.print(servoDepth); Serial.print("\t");
        Serial.print("Position: "); Serial.print(arm.read()); Serial.println("\t"); ;
        delay(100);
      } 
      if (pos = servoDepth) {
        arm.write(90);
        delay(50);
      }
      breathAmount = breathAmount + 1;
      delay(breathInterval);
    }
  
   tone(10, 660, 200);
   delay(200);
   tone(10, 262, 200);
  }
}
