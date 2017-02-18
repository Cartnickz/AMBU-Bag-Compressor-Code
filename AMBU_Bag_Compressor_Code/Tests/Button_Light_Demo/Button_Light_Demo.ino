
const int powerButtonPin = 8;
const int ledPin = 2;

int buttonState = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(ledPin, OUTPUT);
pinMode(powerButtonPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(powerButtonPin);
  if (buttonState == 1){
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  Serial.print(buttonState); Serial.print("\t");
}
