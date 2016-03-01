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
}

