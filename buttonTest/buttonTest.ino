

void setup() {
  // put your setup code here, to run once:
  pinMode(5,OUTPUT);
  pinMode(7,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(5,digitalRead(7));
  if (digitalRead(7)){
    Serial.println("asdf");
  }
}
