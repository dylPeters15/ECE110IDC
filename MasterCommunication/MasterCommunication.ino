#include <SoftwareSerial.h>
#define Rx 10 // DOUT to pin 10
#define Tx 11 // DIN to pin 11

SoftwareSerial Xbee (Rx, Tx);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //master();
  //plebian();
}

void loop() {
  // put your main code here, to run repeatedly:
}

void plebian(){
  Xbee.begin(9600);
  char myResult = 'G';
  char myGroupNum = '1';
  boolean received = false;
  unsigned long start = millis();
  unsigned long timeOut = 10000;
  while (!received&&millis()-start<timeOut){
    if (Xbee.available()){
      char in = Xbee.read();
      if (in == myGroupNum){
        Xbee.print(myResult);
        Serial.print("Char Sent: ");
        Serial.println(myResult);
        received = true;
      }
    }
  }
}

void master(){
  Xbee.begin(9600);
  int total = 0;
  int numGroups = 5;
  int myGroupNum = 5;
  boolean received = false;
  unsigned long startTime = millis();
  unsigned long timeOut = 10000;
  for (int i = 1; i <= numGroups; i++){
    received = false;
    if (i != myGroupNum){
      startTime = millis();
      while (!received&&millis()-startTime<timeOut){
        Xbee.print(i);
        if (Xbee.available()){
          char charReceived = Xbee.read();
          received = true;
          if (charReceived == 'G'){
            total += 2;
          } else if (charReceived == 'S'){
            total += 1;
          } else { //charReceived == 'B'
            total += 0;
          }
          Serial.print("Char received: ");
          Serial.println(charReceived);
        }
      }
    }
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

