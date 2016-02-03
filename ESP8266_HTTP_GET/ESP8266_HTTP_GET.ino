/*
 * This program shows how to read data from the http response of a http GET request and turn ON/OFF an LED based on the data
 * ESP8266 is joined to a router with the given ROUTER_SSID and ROUTER_PASSWORD 
 * The URL http://idiotic.me/tests/http_test.php responds with # followed by a 0 or 1 in random.
 */
#define LED 11  //Pin to connect the LED

char data;

void setup() {
  pinMode(LED, OUTPUT);   
  Serial.begin(115200); //Set the baudrate to 115200(Default for ESP8266)
  
  /*ESP8266 Configuration commands*/
  Serial.println("AT+RST"); // Reset ESP8266 to the defaults
  delay(2000);
  Serial.println("AT+CWMODE=1");      //To enable ONLY Client mode
  delay(200);
  Serial.println("AT+CIPMUX=1");      //To enable multiple connections, compulsory for server operations
  delay(200);
  Serial.println("AT+CWJAP=\"ROUTER_SSID\",\"ROUTER_PASSWORD\""); // Connect to a router.
  delay(1000);
}

void loop() {
   while (Serial.available()) {
    Serial.read();
    delay(10);
  }
  delay(500);
  Serial.println("AT+CIPSTART=4,\"TCP\",\"idiotic.me\",80"); //Establishing TCP connection with the server(idiotic.me) on port 80
  Serial.flush(); //Waits for the transmission of outgoing serial data to complete
  while (!Serial.available()) {}
  while (Serial.available()) {
    data = Serial.read(); //Reads any response for the AT command. We are not using this data anywhere in this tutorial.
    delay(10);
  }
  delay(200);
  Serial.println("AT+CIPSEND=4,43"); // Initiating sending data by setting a link ID(4) and length for the request (42)
  Serial.flush();
  while (!Serial.available()) {}
  while (Serial.available()) {
    data = Serial.read();
    delay(10);
  }
  Serial.println("GET http://idiotic.me/tests/http_test.php"); // GET request of length 42
  Serial.flush();
  while (!Serial.available()) {}
  if (Serial.available()) {
    if (Serial.find("#")) { //Looking for the starting character(#) of the expected command data in the http response
      int i = 0;
      while (!Serial.available()) {} // Wait loop for serial read
      delay(10);
      data = Serial.read();
      if(data == '1'){
        digitalWrite(LED,HIGH);
      }else{
        digitalWrite(LED,LOW);
      }
    }
  }
}
