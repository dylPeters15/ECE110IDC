/*
 * FreqLeftIR
 * Based on Robotics with the BOE Shield - TestLeftIR
 * Sweeep through frequencies and use 9 samples to determine detection at each
 */
 
void setup()                                 // Built-in initialization block
{
  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone
 
  pinMode(10, INPUT);  pinMode(9, OUTPUT);   // Left IR LED & Receiver
 
  Serial.begin(9600);                        // Set data rate to 9600 bps
 
  for(int long irFreq = 30000; irFreq <= 50000; irFreq+=250)
  {
       int irLeft = 9;                           // Assume 9 detections to start
       for(int trial = 1; trial <= 9; trial++)   // Run 9 trials
       {
            irLeft -= irDetect(9, 10, irFreq);   // Check for object and 
                                                 // reduce count if not found
       }
       Serial.print(irFreq);                     // Print frequency
       Serial.print(": ");                       
       Serial.print(irLeft);                     // Print detection count
       Serial.println("/9 Detected");
       delay(100);                               // 0.1 second delay
  }
}  
 
void loop()                                  // Main loop auto-repeats
{
}
 
// IR Object Detection Function
 
int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  tone(irLedPin, frequency, 8);              // IRLED at frequency for at least 1 ms
  delay(1);                                  // Wait 1 ms
  int ir = digitalRead(irReceiverPin);       // IR receiver -> ir variable
  delay(10);                                 // Down time before recheck
  return ir;                                 // Return 1 no detect, 0 detect
}
