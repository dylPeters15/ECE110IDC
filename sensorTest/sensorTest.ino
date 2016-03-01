#include <SoftwareSerial.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(A0);
  Serial.println(val);
  delay(500);
  /*if (digitalRead(2)){
    Serial.println("HIGH");
  } else {
    Serial.println("LOW");
  }*/
}
