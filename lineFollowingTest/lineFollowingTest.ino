#include <Servo.h>
#include <SoftwareSerial.h>

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


#include <Wire.h>           // Reference the I2C Library

void setup() { 
 
  Serial.begin(9600);    // Set data rate to 9600 bps
  delay(200);            // Powering on delay time adjustment
  Wire.begin();          // Initialize I2C Interface

// Setup movement
  Serial.begin(9600);
  servoLeft.attach(13);
  servoRight.attach(12);

  delay(200);
}


void loop() {
  /*forward();
  delay(2000);
  slightLeft();
  delay(2000);
  slightRight();
  delay(2000);
  fullLeft();
  delay(2000);
  fullRight();
  delay(2000);
  reverse();
  delay(2000);
  stopMoving();
  delay(2000);
  left90();
  //delay(2000);
  right90();
  //delay(2000);
  turnAround();
  //delay(2000);*/
  Serial.print("Left");
  Serial.println(RCTime(2));
  Serial.print("Mid");
  Serial.println(RCTime(3));
  Serial.print("Right");
  Serial.println(RCTime(4));
  
  leftOnLine = (RCTime(leftQTI)>40);
    centerOnLine = (RCTime(centerQTI)>40);
    rightOnLine = (RCTime(rightQTI)>40);
  
  if (!leftOnLine && !centerOnLine && !rightOnLine) {
    reverse();
  } 
  else if (leftOnLine && centerOnLine && !rightOnLine) {
    slightLeft();
    //Look at two cases, see which is more likely to happen.
  }
  else if (!leftOnLine && centerOnLine && rightOnLine) {
    slightRight();
    //Look at the two cases, see which is more likely to happen.
  }
  else if (leftOnLine && !centerOnLine && !rightOnLine) {
    fullLeft();
    
    //Do a slight left, a forward, then a right, then measure again.
  }
  else if (!leftOnLine && centerOnLine && !rightOnLine) {
    forward();
  }
  else if (!leftOnLine && !centerOnLine && rightOnLine) {
    fullRight();
    
    
    ///Do a slight right here, a forward, then a left, then measure again.
  }
  else if(leftOnLine && centerOnLine && rightOnLine) {
        stopMoving();
  }
  else {
      forward();
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
  //Do more here.
  servoRight.writeMicroseconds(1443);
  delay(50);
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
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
  delay(1350);
}

