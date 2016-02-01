/*
 *This program changes the brightness of an LED through serial commands for a value from 0 to 9
 *The brightness of LED light shall be varied by sending a value between 0 and 9 over serial comm
 */

#define LED 11                      //LED is connected to Pin 11

char data;
int brightness;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(LED, OUTPUT);             // initialize digital pin 13 as an output.
  Serial.begin(115200);             // Setting baudrate to 115200 bits per second
}

// the loop function runs over and over again forever
void loop() {
  while (Serial.available()) {
    data = Serial.read();           //To read serial from internal buffer
    if (data > 47 && data < 58) {   //ASCII(0) = 48 & ASCII(9) = 57
      brightness = (data - 48) * 28;//PWM value ranges from 0 to 255 and mapping 0 to 9 to value between 0 and 255
      analogWrite(LED, brightness); 
    }
  }
}
