#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
 
#define melodyPin 5


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


 const int TxPin = 51;
 SoftwareSerial mySerial = SoftwareSerial(255,TxPin);

int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,
 
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
 
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,
 
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
 
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};
//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};



void setup() { 
 // Setup movement

pinMode(TxPin, OUTPUT);
digitalWrite(TxPin,HIGH);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);


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
    mySerial.begin(9600);
  delay(100);
  mySerial.write(12);                 // Clear             
  mySerial.write(17);                 // Turn backlight on
  delay(5);         
  mySerial.print("Black");
  mySerial.write(13);
    Serial.println("black (bronze)");
    Xbee.begin(9600);
    plebian('B');
    //master('B');
  } else if (red > 75 && red <= 175 && grn > 45 && grn <= 150 && blu > 75 && blu <= 275){ //blue was 225
    mySerial.begin(9600);
  delay(100);
  mySerial.write(12);                 // Clear             
  mySerial.write(17);                 // Turn backlight on
  delay(5);         
  mySerial.print("Grey");
  mySerial.write(13);
    Serial.println("Grey (silver)");
    Xbee.begin(9600);
    plebian('S');
    //master('S')
  } else if (red > 175 && grn > 150 && blu > 275){
    mySerial.begin(9600);
  delay(100);
  mySerial.write(12);                 // Clear             
  mySerial.write(17);                 // Turn backlight on
  delay(5);         
  mySerial.print("White");
  mySerial.write(13);
    Serial.println("White (gold)");
    Xbee.begin(9600);
    plebian('G');
    //master('G');
    
  } else {
    mySerial.begin(9600);
  delay(100);
  mySerial.write(12);                 // Clear             
  mySerial.write(17);                 // Turn backlight on
  delay(5);         
  mySerial.print(red);
  mySerial.print(" ");
  mySerial.print(grn);
  mySerial.print(" ");
  mySerial.print(blu);
  mySerial.write(13);
    Serial.println("Unknown color");
    Xbee.begin(9600);
    plebian('B');
    //master('B');
    
  }
  delay(100);
}

void plebian(char myResultIn){
  Xbee.begin(9600);
  char myResult = myResultIn;
  char myGroupNum = '2';
  boolean received = false;
  unsigned long start = millis();
  unsigned long timeOut = 60000;
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
  plebianReceive();
}

void plebianReceive(){
  Xbee.begin(9600);
  boolean performed = false;
  while (!performed){
    if (Xbee.available()){
      char in = Xbee.read();
      if (in == 'D'){
        mySerial.print("Dance");
        dance();
        performed = true;
      } else if (in == 'L') {
        mySerial.print("Light");
        lightShow();
        performed = true;
      } else if (in == 'T') {
        mySerial.print("Sing");
        sing(1);
        performed = true;
      }
    }
  }
  while (true){
    delay(500);
  }
}

void master(char myResultIn){
  Xbee.begin(9600);
  char myResult = myResult;
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
void spinRight(){
    servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
  delay(3000);
}
void spinLeft() {
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300);
  delay(3000);
}
void rightCircle(){
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1480);
  delay(2000);
}
void leftCircle(){
  servoRight.writeMicroseconds(1300);
  servoLeft.writeMicroseconds(1520);
  delay(2000);
}
void dance(){
  servoLeft.attach(13);
  servoRight.attach(12);
  rightCircle();
  leftCircle();
  spinRight();
  spinLeft();
  servoRight.detach();
  servoLeft.detach();
}
void lightShow(){
digitalWrite(6,HIGH);
digitalWrite(7,HIGH);
digitalWrite(8,HIGH);
digitalWrite(9,HIGH);
delay(250);
digitalWrite(6,LOW);
delay(250);
digitalWrite(7,LOW);
delay(250);
digitalWrite(8,LOW);
delay(250);
digitalWrite(9,LOW);
delay(250);
digitalWrite(6,HIGH);
digitalWrite(7,HIGH);
digitalWrite(8,HIGH);
digitalWrite(9,HIGH);
delay(250);
digitalWrite(6,LOW);
digitalWrite(7,LOW);
digitalWrite(8,LOW);
digitalWrite(9,LOW);
delay(250);
digitalWrite(6,HIGH);
digitalWrite(8,HIGH);
delay(250);
digitalWrite(6,LOW);
digitalWrite(7,HIGH);
digitalWrite(8,LOW);
digitalWrite(9,HIGH);
delay(250);
digitalWrite(6,HIGH);
digitalWrite(7,HIGH);
digitalWrite(8,LOW);
digitalWrite(9,LOW);
delay(250);
digitalWrite(6,LOW);
digitalWrite(7,LOW);
digitalWrite(8,HIGH);
digitalWrite(9,HIGH);
delay(250);
digitalWrite(6,LOW);
digitalWrite(7,LOW);
digitalWrite(8,LOW);
digitalWrite(9,LOW);
delay(250);
digitalWrite(6,HIGH);
digitalWrite(7,HIGH);
digitalWrite(8,HIGH);
digitalWrite(9,HIGH);
delay(250);
digitalWrite(6,LOW);
digitalWrite(7,LOW);
digitalWrite(8,LOW);
digitalWrite(9,LOW);
delay(250);
digitalWrite(6,HIGH);
digitalWrite(7,HIGH);
digitalWrite(8,HIGH);
digitalWrite(9,HIGH);
delay(250);
digitalWrite(9,LOW);
delay(250);
digitalWrite(8,LOW);
delay(250);
digitalWrite(7,LOW);
delay(250);
digitalWrite(6,LOW);
delay(250);
digitalWrite(6,HIGH);
digitalWrite(7,HIGH);
digitalWrite(8,HIGH);
digitalWrite(9,HIGH);
delay(250);
digitalWrite(6,LOW);
digitalWrite(7,LOW);
digitalWrite(8,LOW);
digitalWrite(9,LOW);
delay(250);
digitalWrite(6,HIGH);
digitalWrite(7,LOW);
digitalWrite(8,LOW);
digitalWrite(9,HIGH);
delay(250);
digitalWrite(6,LOW);
digitalWrite(7,HIGH);
digitalWrite(8,HIGH);
digitalWrite(9,LOW);
delay(250);
digitalWrite(6,HIGH);
digitalWrite(7,LOW);
digitalWrite(8,LOW);
digitalWrite(9,LOW);
delay(250);
digitalWrite(6,LOW);
digitalWrite(7,LOW);
digitalWrite(8,HIGH);
digitalWrite(9,LOW);
delay(250);
digitalWrite(6,LOW);
digitalWrite(7,HIGH);
digitalWrite(8,LOW);
digitalWrite(9,LOW);
delay(250);
digitalWrite(6,LOW);
digitalWrite(7,LOW);
digitalWrite(8,LOW);
digitalWrite(9,HIGH);
delay(250);
}
int song = 0;
 
void sing(int s) {
  // iterate over the notes of the melody:
  servoRight.detach();
  servoLeft.detach();
  song = s;
  if (song == 2) {
    Serial.println(" 'Underworld Theme'");
    int size = sizeof(underworld_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
 
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / underworld_tempo[thisNote];
 
      buzz(melodyPin, underworld_melody[thisNote], noteDuration);
 
      // to distinguish the notes, set a minimum time between them.*******************888*********************************8
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
 
      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);//*************************************************************************8
 
    }
 
  } else {
 
    Serial.println(" 'Mario Theme'");
    int size = sizeof(melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
 
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo[thisNote];
 
     buzz(melodyPin, melody[thisNote], noteDuration);//*******************************************************************888
 
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
 
      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);//************************************************************************8
 
    }
  }
}
 
void buzz(int targetPin, long frequency, long length) {
  //digitalWrite(6, HIGH);
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
  digitalWrite(6, LOW);
 
}
