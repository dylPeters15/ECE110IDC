#include <Servo.h>
#include <SoftwareSerial.h>

const int leftQTI = 2;
const int centerQTI = 3;
const int rightQTI = 4;
const int speaker = 5;
const int redLED1 = 6;
const int yellowLED1 = 7;
const int redLED2 = 8;
const int yellowLED2 = 9;
#define Rx 10 // DOUT to pin 10
#define Tx 11 // DIN to pin 11
const int sio = 53;      // ColorPAL connected to pin 2
const int unused = 14;    // Non-existant pin # for SoftwareSerial

const int sioBaud = 4800;
const int waitDelay = 200;

// Received RGB values from ColorPAL
int red;
int grn;
int blu;

SoftwareSerial Xbee (Rx, Tx);

// Set up two software serials on the same pin.
SoftwareSerial serin(sio, unused);
SoftwareSerial serout(unused, sio);

Servo servoLeft;
Servo servoRight;

boolean leftOnLine = 0;
boolean centerOnLine = 0;
boolean rightOnLine = 0;

void setup() { 
 // Setup movement


pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
/*
tone(5,5000,1000);
digitalWrite(6,HIGH);
digitalWrite(7,HIGH);
digitalWrite(8,HIGH);
digitalWrite(9,HIGH);
*/
//delay(100000);

 
  Serial.begin(9600);
  servoLeft.attach(13);
  servoRight.attach(12);
  delay(200);
}


void loop() {

   Serial.print("Left  ");
  Serial.print(RCTime(2));
  Serial.print("  Mid  ");
  Serial.print(RCTime(3));
  Serial.print("  Right  ");
  Serial.println(RCTime(4));
  
  
    leftOnLine = (RCTime(leftQTI)>30);
    centerOnLine = (RCTime(centerQTI)>30);
    rightOnLine = (RCTime(rightQTI)>30);
   
  if (!leftOnLine && !centerOnLine && !rightOnLine) {
    forward();
  } 
  else if (leftOnLine && centerOnLine && !rightOnLine) {
    slightLeft();
  }
  else if (!leftOnLine && centerOnLine && rightOnLine) {
    slightRight();
  }
  else if (leftOnLine && !centerOnLine && !rightOnLine) {
    fullLeft();
  }
  else if (!leftOnLine && !centerOnLine && rightOnLine) {
    fullRight();
  }
  
  else if (!leftOnLine && centerOnLine && !rightOnLine) {
    forward();
  }
  
  else if(leftOnLine && centerOnLine && rightOnLine) {
        stopMoving();
        right90();
        forward1();
        //servoLeft.writeMicroseconds(1500);
       // servoRight.writeMicroseconds(1500);
       servoRight.detach();
       servoLeft.detach();
       senseColor();
  }
  else {
      forward();
  }
}

void senseColor(){
  Serial.begin(9600);
  Xbee.begin(9600); // type a char, then hit enter
  reset();          // Send reset to ColorPal
  serout.begin(sioBaud);
  pinMode(sio, OUTPUT);
  serout.print("= (00 $ m) !"); // Loop print values, see ColorPAL documentation
  serout.end();       // Discontinue serial port for transmitting

  serin.begin(sioBaud);         // Set up serial port for receiving
  pinMode(sio, INPUT);

  
  while (true){
    readData();
    if (Xbee.available()){
      Serial.println(Xbee.read());
      delay(100);
    }
    if (Serial.available()){
      Xbee.println(Serial.read());
      delay(100);
    }
  }
}

// Reset ColorPAL; see ColorPAL documentation for sequence
void reset() {
  delay(200);
  pinMode(sio, OUTPUT);
  digitalWrite(sio, LOW);
  pinMode(sio, INPUT);
  while (digitalRead(sio) != HIGH);
  pinMode(sio, OUTPUT);
  digitalWrite(sio, LOW);
  delay(80);
  pinMode(sio, INPUT);
  delay(waitDelay);
}

void readData() {
  char buffer[32];
  //Serial.println("asdf");
  //printColor();
  if (serin.available() > 0) {
    
    // Wait for a $ character, then read three 3 digit hex numbers
    buffer[0] = serin.read();
    if (buffer[0] == '$') {
      for(int i = 0; i < 9; i++) {
        while (serin.available() == 0);     // Wait for next input character
        buffer[i] = serin.read();
        if (buffer[i] == '$')               // Return early if $ character encountered
          return;
      }
      parseAndPrint(buffer);
      delay(10);
    }
  }
}

// Parse the hex data into integers
void parseAndPrint(char * data) {
  sscanf (data, "%3x%3x%3x", &red, &grn, &blu);
  char buffer[32];
  sprintf(buffer, "R%4.4d G%4.4d B%4.4d", red, grn, blu);
  //Serial.println(buffer);
  Serial.print(red);
  Serial.print("   ");
  Serial.print(grn);
  Serial.print("   ");
  Serial.println(blu);
  printColor();
}

void printColor(){
  
  if (red <= 75 && grn <= 45 && blu <= 75){
    Serial.println("black (bronze)");
    Xbee.println("b");
    digitalWrite(6,HIGH);
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
    digitalWrite(9,LOW);
    Xbee.begin(9600);
    while (true){
      Xbee.println("b");
    }
  } else if (red > 75 && red <= 175 && grn > 45 && grn <= 125 && blu > 75 && blu <= 225){
    Serial.println("Grey (silver)");
    Xbee.println("g)");
    digitalWrite(6,HIGH);
    digitalWrite(7,HIGH);
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
    Xbee.begin(9600);
    while (true){
      Xbee.println("g");
    }
  } else if (red > 175 && grn > 125 && blu > 225){
    Serial.println("White (gold)");
    Xbee.println("w");
    digitalWrite(6,HIGH);
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
    Xbee.begin(9600);
    while (true){
      Xbee.println("w");
    }
  } else {
    Serial.println("Unknown color");
    Xbee.println("u");
    digitalWrite(6,HIGH);
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
    digitalWrite(9,HIGH);
    Xbee.begin(9600);
    while (true){
      Xbee.println("black");
    }
  }
  delay(100);
}


long RCTime(int sensorIn){
   long duration = 0;
   pinMode(sensorIn, OUTPUT);     // Make pin OUTPUT
   digitalWrite(sensorIn, HIGH);  // Pin HIGH (discharge capacitor)
   delay(1);                      // Wait 1ms
   pinMode(sensorIn, INPUT);      // Make pin INPUT
   digitalWrite(sensorIn, LOW);   // Turn off internal pullups
   while(digitalRead(sensorIn)){  // Wait for pin to go LOW
      duration++;
   }
   return duration;
}

void forward() {
  servoLeft.writeMicroseconds(1557);
  servoRight.writeMicroseconds(1443);
  delay(50);
}
void forward1() {
  servoLeft.writeMicroseconds(1557);
  servoRight.writeMicroseconds(1443);
  delay(2000);
}
void slightLeft() {
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1450);
}
void slightRight() {
  servoLeft.writeMicroseconds(1550);
  servoRight.writeMicroseconds(1500);
}
void fullLeft() {
  servoLeft.writeMicroseconds(1450);
  servoRight.writeMicroseconds(1450);
}
void fullRight() {
  servoLeft.writeMicroseconds(1550);
  servoRight.writeMicroseconds(1550);
}
void reverse() {
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1700);
}
void stopMoving() {
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}
void left90() {
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300);
  delay(670);
}

void right90() {
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
  delay(600);
}
void turnAround() {
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300);
  delay(1350);
}
