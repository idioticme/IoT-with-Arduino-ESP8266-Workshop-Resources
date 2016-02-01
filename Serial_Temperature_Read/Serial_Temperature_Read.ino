/*
  Read temperature using LM35 temperature sensor and output the value over serial comm.
 */

float temp;                         //Variable to process temperature value
int count, temperature;             

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);             // Setting baudrate to 115200 bits per second
}

// the loop function runs over and over again forever
void loop() {
  count = 0;
  temp = 0;
  while ( count < 11 )
  {
    temp += analogRead(A0);         //To digital value of read voltage at pin A0, ranges from 0 to 1023
    count++;
    delay(100);
  }
  temp /= count;
  temp *= 0.488281;                 //To convert digital value into actual temperature in ºC
  temperature = int(temp);
  Serial.print("Temperature = ");   //To print through serial
  Serial.print(temperature);               //Appending temp value to the serial print sequence
  Serial.println(" *C");             //Appending the degree celsius unit to the serial print sequence
}
