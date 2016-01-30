
/*This program enables your ESP8266 to communicate with your Arduino microcontroller. 
 *We start a TCP server in ESP8266 and a TCP client is connected to the ESP8266 over wifi.
 *To connect a client device over WiFi, the ESP8266 is configured as an Access Point. The AP configuration shall be referred from the documentations  
 *
 *In this program an LED light is turned ON when a client sends the command #N 
 *The LED light can be turned OFF by send a command # followed by any characters.
 */
 
#define LED 10                          //Pin to connect the LED

char cmd;

void setup() {
  pinMode(LED, OUTPUT);   
  Serial.begin(115200);                 //Set the baudrate of serial communication to 115200(Default for ESP8266)
  
  /*ESP8266 TCP server configuration commands*/
  
  Serial.println("AT+RST");             //Reset ESP8266 to the defaults
  delay(2000);
  Serial.println("AT+CIPMUX=1");        //Enable multiple connections;compulsory for server operations
  delay(200);
  Serial.println("AT+CIPSERVER=1,60");  //Start a TCP SERVER at port 60 on ESP8266
  delay(200);
}

void loop() {
  while (Serial.available()){
    cmd = Serial.read();
    if (cmd == '#')
    {
      delay(10);
      cmd = Serial.read();//Read a character from serial buffer.
      delay(10);
      if (cmd == 'N')
        digitalWrite(LED, HIGH);
      else
        digitalWrite(LED, LOW);
    }
  }
}
