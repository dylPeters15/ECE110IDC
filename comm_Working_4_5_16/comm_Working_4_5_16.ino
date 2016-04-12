#include <SoftwareSerial.h>
#define Rx 11 // DOUT to pin 11
#define Tx 10 // DIN to pin 10

SoftwareSerial Xbee (Rx, Tx);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  master('G');
  //plebian('G');
}

void loop() {
  // put your main code here, to run repeatedly:
}


void plebian(char myResult){
  Xbee.begin(9600);
  char myGroupNum = '2';
  while (true){
    if (Xbee.available()){
      char in = Xbee.read();
      if (in == myGroupNum){
        Xbee.print(myResult);
        Serial.print("int Sent: ");
        Serial.println(myResult);
      } else if (in == 'D'){
        mySerial.print("Dance");
        dance();
        fullStop();
      } else if (in == 'L') {
        mySerial.print("Light");
        lightShow();
        fullStop();
      } else if (in == 'T') {
        mySerial.print("Sing");
        sing(1);
        fullStop();
      }
    }
  }
}

void fullStop(){
  while (true){
    delay(500);
  }
}




void master(char myResultIn){
  Xbee.begin(9600);
  char myResult = myResultIn;
  int total = 0;
  int numGroups = 3;
  int myGroupNum = 3;
  boolean received = false;
  unsigned long startTime = millis();
  unsigned long timeOut = 10000;
  for (int i = 1; i <= numGroups; i++){
    received = false;
    if (i != myGroupNum){
      startTime = millis();
      while (!received && millis()-startTime<timeOut){
        Xbee.print(i);
        delay(150);
        if (Xbee.available()){
          char charReceived = Xbee.read();
            received = true;
            if (charReceived == 'G'){
            digitalWrite(4, HIGH);
            total += 2;
          } else if (charReceived == 'S'){
            total += 1;
          } else { //charReceived == 'B'
            total += 0;
            //Serial.println("It sent a B");
          }
          Serial.print("Char received: ");
          Serial.println(charReceived);
        }
      }
    }
  }
  Serial.println("At end of for loop");
  if (myResult == 'G'){
    total += 2;
  } else if (myResult = 'S'){
    total += 1;
  } else {
    total += 0;
  }
  total %= 3;
  Serial.print("Final Result Sent: ");
  if (total == 0){ //bronze, dance
    Xbee.print("D");
    Serial.println("D");
  } else if (total == 1){ //silver, light show
    Xbee.print("L");
    Serial.println("L");
  } else { // gold, play tune
    Xbee.print("T");
    Serial.println("T");
  }
}

