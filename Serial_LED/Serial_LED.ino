/*
  This program is to control an LED through serial commands. 
*/

#define LED 11              //LED is connected to Pin 11

char data;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(LED, OUTPUT);     // initialize digital pin 11 as an output.
  Serial.begin(115200);     // Setting baudrate to 115200 bits per second
}

// the loop function runs over and over again forever
void loop() {
  while (Serial.available()) {
    data = Serial.read();   //To read serial from internal buffer
    if (data == 'N')
      digitalWrite(LED, HIGH);  // turn the LED on (HIGH is the voltage level)
    else
      digitalWrite(LED, LOW);   // turn the LED off by making the voltage LOW
  }
}
