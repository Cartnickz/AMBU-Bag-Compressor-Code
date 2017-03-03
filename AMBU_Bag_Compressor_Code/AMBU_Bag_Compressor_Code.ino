#include <SoftwareSerial.h>
#include <Servo.h>
#include <LiquidCrystal.h>

const int armPin = 6;
const int powerButtonPin = 13;
const int ledPin = 5;
const int piezoPin = 3;

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int breathAmount = 0;

int pos = 90;

Servo arm;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  arm.attach(armPin);
  pinMode(ledPin, OUTPUT);
  pinMode(powerButtonPin, INPUT);
  
  lcd.begin(20,4);
  lcd.setCursor(0,0);
  lcd.print("Interval:");
  lcd.setCursor(0,1);
  lcd.print("Depth:");
  lcd.setCursor(0,2);
  lcd.print("Speed:");
  lcd.setCursor(0,3);
  lcd.print("Breaths:");
}

void loop() {
  // put your main code here, to run repeatedly:

int loopRun = digitalRead(powerButtonPin);

int breathInterval = analogRead(A1);
  breathInterval = map(breathInterval, 0, 1023, 1000, 7000);
int servoDepth = analogRead(A2);
  servoDepth = map(servoDepth, 0, 1023, 10, 90);
int servoSpeed = analogRead(A3);
  servoSpeed = map(servoSpeed, 0, 1023, 1, 20);
int setBreathAmount = analogRead(A4);
    setBreathAmount = map(setBreathAmount, 0, 1023, 0, 5);

  Serial.print("Interval: "); Serial.print(breathInterval); Serial.print("\t"); delay(5);
  Serial.print("Depth: "); Serial.print(servoDepth); Serial.print("\t"); delay(5);
  Serial.print("Speed: "); Serial.print(servoSpeed); Serial.print("\t"); delay(5);
  Serial.print("Amount: "); Serial.print(setBreathAmount); Serial.print("\t"); delay(5);
  Serial.print("Position: "); Serial.print(arm.read()); Serial.println("\t"); delay(20);

  lcd.setCursor(10,0);
  lcd.print(breathInterval / 1000);
  lcd.setCursor(10,1);
  lcd.print(servoDepth);
  lcd.setCursor(10,2);
  lcd.print(servoSpeed);
    if (servoSpeed < 10) {
      lcd.setCursor(11,2);
      lcd.print(" ");
    }
  lcd.setCursor(10,3);
  lcd.print(setBreathAmount + 1);

  digitalWrite(ledPin, LOW);

  if (loopRun == LOW){
    //starts the program when button is pressed
    breathAmount = 0;
    digitalWrite(ledPin, HIGH);
    
    tone(piezoPin, 330, 200);
    delay(200);
    tone(piezoPin , 660, 200);
   
  
    while (breathAmount <= setBreathAmount) {
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
  
   tone(piezoPin, 660, 200);
   delay(200);
   tone(piezoPin, 262, 200);
  }
}
