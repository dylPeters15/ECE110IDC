#include <Servo.h>
#include <SoftwareSerial.h>


bool i = true;
Servo servoLeft;
Servo servoRight;
int counter = 0;
//int measurement = 0;
const int leftQTI = 2;
const int centerQTI = 3;
const int rightQTI = 4;

boolean leftOnLine = 0;
boolean centerOnLine = 0;
boolean rightOnLine = 0;

void setup() { 
 

// Setup movement
  Serial.begin(9600);
  servoLeft.attach(13);
  servoRight.attach(12);

  delay(200);
  
  
}


void loop() {

   Serial.print("Left");
Serial.println(RCTime(2));
Serial.print("Mid");
  Serial.println(RCTime(3));
  Serial.print("Right");
  Serial.println(RCTime(4));
  
  
  leftOnLine = (RCTime(leftQTI)>30);
    centerOnLine = (RCTime(centerQTI)>30);
    rightOnLine = (RCTime(rightQTI)>30);
   
 //while (i==true){
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
        forward();
       // servoLeft.detach();
       // servoRight.detach();
       // i = false;
  }
  else {
      forward();
  }
 // }
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
  delay(670);
}
void turnAround() {
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300);
  delay(1350);
}
