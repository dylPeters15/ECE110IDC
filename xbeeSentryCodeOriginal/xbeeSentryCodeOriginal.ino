#include <SoftwareSerial.h>
#define Rx 10 // DOUT to pin 10
#define Tx 11 // DIN to pin 11

SoftwareSerial Xbee (Rx, Tx);

void setup() {
  pinMode(7,INPUT);
  pinMode(5,OUTPUT);
  Serial.begin(9600); // Set to No line ending;
  Xbee.begin(9600); // type a char, then hit enter
  delay(500);
}
void loop() {
  /*if(Serial.available()) { // Is serial data available?
    char outgoing = Serial.read(); // Read character, send to XBee
    Xbee.print(outgoing);
}*/
if (digitalRead(7)){
  char outgoing = 's'; // Read character, send to XBee
    Xbee.print(outgoing);
}
  if(Xbee.available()) { // Is data available from XBee?
    char incoming = Xbee.read(); // Read character,
    Serial.println(incoming); // send to Serial Monitor
    digitalWrite(5,HIGH);
} else {
  digitalWrite(5,LOW);
}
  delay(50);
}
