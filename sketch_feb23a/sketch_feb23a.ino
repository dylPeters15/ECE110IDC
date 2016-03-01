#include <Servo.h>

Servo servoLeft;
Servo servoRight;

void setup() {
  // put your setup code here, to run once:
  servoLeft.attach(13);
  servoLeft.attach(12);
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1700);
  //straight(1);
}

void loop() {
  // put your main code here, to run repeatedly:
}

/*void straight(double velocity){
  double left = 1500 + velocity * 200;
  double right = 1500 - velocity * 200;
  servoLeft.writeMicroseconds(left);
  servoRight.writeMicroseconds(right);
}

void turn90(boolean left){
  
}*/

