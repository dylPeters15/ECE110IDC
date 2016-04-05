#include <SoftwareSerial.h>
#define Rx 10 // DOUT to pin 10
#define Tx 11 // DIN to pin 11

SoftwareSerial Xbee (Rx, Tx);

void setup() {
  Serial.begin(9600); // Set to No line ending;
  Xbee.begin(9600); // type a char, then hit enter
  delay(500);
}
void loop() {
if (Serial.available()){
  char outgoing = 's'; // Read character, send to XBee
    Xbee.print(Serial.read());
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
