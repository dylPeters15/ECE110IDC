#include <SoftwareSerial.h>
#define Rx 10 // DOUT to pin 10
#define Tx 11 // DIN to pin 11

SoftwareSerial Xbee (Rx, Tx);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Begin");
  plebian();
  //master();
  //plebian();
//  Xbee.begin(9600);
//  char toSend = 'G';
//  for (int i = 0; i < 100000; i++){
//    Xbee.print(toSend);
//  }
  Serial.println("Done");
}

void loop() {
  // put your main code here, to run repeatedly:
  
//    if (in == 1){
//      int toSend = 155;
//      Xbee.print(toSend);
//      Serial.println("printed 155");
//    }
 // }
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
        Serial.print("int Sent: ");
        Serial.println(myResult);
        received = true;
      }
    }
  }
}

void master(){
  Xbee.begin(9600);
  int total = 0;
  int numGroups = 3;
  int myGroupNum = 3;
  boolean received = false;
  unsigned long startTime = millis();
  unsigned long timeOut = 60000;
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

  //add our own result
  
  
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

