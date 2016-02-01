
/*This program enables your ESP8266 to communicate with your Arduino microcontroller.
 *We start a TCP server in ESP8266 and a TCP client is connected to the ESP8266 over wifi.
 *To connect a client device over WiFi, the ESP8266 is configured as an Access Point. The AP configuration shall be referred from the documentations
 *
 *In this program the brightness of an LED light is varied with a value from 0 to 9
 *The brightness of LED light shall be varied by sending a command # followed by a value from 0 to 9.
 */
#define LED 11                          //Pin to connect the LED

char data;
int brightness;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);                 //Set the baudrate of serial communication to 115200(Default for ESP8266)

  /*ESP8266 Configuration commands*/

  Serial.println("AT+RST");             // Reset ESP8266 to the defaults
  delay(2000);
  Serial.println("AT+CWMODE=2");      //To enable both Client and Accesspoint mode
  delay(200);
  Serial.println("AT+CIPMUX=1");        //Enable multiple connections;compulsory for server operations
  delay(200);
  Serial.println("AT+CIPSERVER=1,60");  //Start a SERVER at port 60 on ESP8266
  delay(200);
}

void loop() {
  while (Serial.available()) {
    data = Serial.read();
    if (data == '#')
    {
      delay(10);
      data = Serial.read();              //Read a character from serial buffer.
      delay(10);
      if (data > 47 && data < 58) {   //ASCII(0) = 48 & ASCII(9) = 57
        brightness = (data - 48) * 28;//PWM value ranges from 0 to 255 and mapping 0 to 9 to value between 0 and 255
        analogWrite(LED, brightness);
      }
    }
  }
}
