#define LED 10                          //Pin to connect the LED

char cmd;

void setup() {
  pinMode(LED, OUTPUT);   
  Serial.begin(115200);                 //Set the baudrate of serial communication to 115200(Default for ESP8266)
  
  /*ESP8266 Configuration commands*/
  
  Serial.println("AT+RST");             // Reset ESP8266 to the defaults
  delay(2000);
  Serial.println("AT+CIPMUX=1");        //Enable multiple connections;compulsory for server operations
  delay(200);
  Serial.println("AT+CIPSERVER=1,60");  //Start a SERVER at port 60 on ESP8266
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
