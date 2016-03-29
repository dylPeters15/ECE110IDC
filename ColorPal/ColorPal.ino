/* ColorPal Sensor Example for Arduino
  Author: Martin Heermance, with some assistance from Gordon McComb
  This program drives the Parallax ColorPAL color sensor and provides
  serial RGB data in a format compatible with the PC-hosted 
  TCS230_ColorPAL_match.exe color matching program.
*/

#include <SoftwareSerial.h>

const int sio = 10;			// ColorPAL connected to pin 2
const int unused = 14; 		// Non-existant pin # for SoftwareSerial
const int sioBaud = 4800;
const int waitDelay = 200;

// Received RGB values from ColorPAL
int red;
int grn;
int blu;

// Set up two software serials on the same pin.
SoftwareSerial serin(sio, unused);
SoftwareSerial serout(unused, sio);

void setup() {
  Serial.begin(9600);
  reset();				  // Send reset to ColorPal
  serout.begin(sioBaud);
  pinMode(sio, OUTPUT);
  serout.print("= (00 $ m) !"); // Loop print values, see ColorPAL documentation
  serout.end();			  // Discontinue serial port for transmitting

  serin.begin(sioBaud);	        // Set up serial port for receiving
  pinMode(sio, INPUT);
}

void loop() {
  readData();
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
  //Serial.print("red: ");
  Serial.print(red);
  Serial.print("   ");
  //Serial.print("Green: ");
  
  Serial.print(grn);
  Serial.print("   ");
  //Serial.print("Blue: ");
  Serial.println(blu);
  printColor();
}

void printColor(){
  if (red > 15 && red < 60 && grn > 5 && grn < 45 && blu > 15 && blu < 75){
    Serial.println("black (bronze)");
  } else if (red > 100 && red < 175 && grn > 65 && grn < 125 && blu > 125 && blu < 225){
    Serial.println("Grey (silver)");
  } else if (red > 180 && red < 275 && grn > 130 && grn < 200 && blu > 240 && blu < 350){
    Serial.println("White (gold)");
  } else {
    Serial.println("Unknown color");
  }
  delay(50);
}

