#include <Servo.h>
#include <SoftwareSerial.h>

#define leftSensor 2
#define centerSensor 3
#define rightSensor 4

#define leftServoPin 13
#define rightServoPin 12

#define black 0
#define grey 1
#define white 2

Servo leftServo;
Servo rightServo;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  Serial.println("test serial");
  
  leftServo.attach(leftServoPin);
  rightServo.attach(rightServoPin);

  followLine();
}

void loop() {
  // put your main code here, to run repeatedly:
  /*Serial.print("left sensor: ");
  Serial.println(rcTime(leftSensor));
  Serial.print("center sensor: ");
  Serial.println(rcTime(centerSensor));
  Serial.print("right sensor: ");
  Serial.println(rcTime(rightSensor));
  Serial.println();
  delay(1000);*/
}

void followLine(){
  while (true){
    fullForward();
    if (color(leftSensor) == black){
      //turn more left
      fullLeft();
    }
    if (color(rightSensor) == black){
      //turn more right
      fullRight();
    }
    if (color(centerSensor) == white){
      //freak out
    }
  }
}

void fullRight(){
  leftServo.writeMicroseconds(1700);
  rightServo.writeMicroseconds(1500);
}

void fullLeft(){
  leftServo.writeMicroseconds(1500);
  rightServo.writeMicroseconds(1300);
}

void fullForward(){
  leftServo.writeMicroseconds(1700);
  rightServo.writeMicroseconds(1300);
}

int color(int pin){
  long val = rcTime(pin);
  if (pin == leftSensor){
    if (val > 5000 && val < 1500){
      return black;
    }
    if (val > 50000 && val < 150000){
      return white;
    }
    return grey;
  } else if (pin == centerSensor){
    if (val > 12000 && val < 20000){
      return black;
    }
    if (val > 125000 && val < 200000){
      return white;
    }
    return grey;
  } else if (pin == rightSensor){
    if (val > 19000 && val < 26000){
      return black;
    }
    if (val > 150000 && val < 250000){
      return white;
    }
    return grey;
  }
}

long rcTime(int pin)                         // ..returns decay time
{                                            
  pinMode(pin, OUTPUT);                      // Charge capacitor
  digitalWrite(pin, HIGH);                   // ..by setting pin ouput-high
  delay(1);                                  // ..for 5 ms
  pinMode(pin, INPUT);                       // Set pin to input
  digitalWrite(pin, LOW);                    // ..with no pullup
  long time  = micros();                     // Mark the time
  while(digitalRead(pin));                   // Wait for voltage < threshold
  time = micros() - time;                    // Calculate decay time
  return time;                               // Return decay time
}
