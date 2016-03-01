/*
 Robotics with the BOE Shield – LeftServoClockwise
 Generate a servo full speed clockwise signal on digital pin 13.
 */

#include <Servo.h>                           // Include servo library
 
Servo servoLeft; 
Servo servoRight;// Declare left servo

void setup()                                 // Built in initialization block
{ 
  servoLeft.attach(13);
  servoRight.attach(12);// Attach left signal to pin 13 
  servoLeft.writeMicroseconds(1700);         // 1.3 ms full speed clockwise
  servoRight.writeMicroseconds(1300);
  
}  
 
void loop()                                  // Main loop auto-repeats
{                                            // Empty, nothing needs repeating
  straight(1);
  delay(1000);
  turn90(true);
}

void straight(double velocity){
  double left = 1500 + velocity * 200;
  double right = 1500 - velocity * 200;
  servoLeft.writeMicroseconds(left);
  servoRight.writeMicroseconds(right);
}

void turn90(boolean left){
  if (left){
    servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
  delay(582);
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  } else {
    
  }
  
}


