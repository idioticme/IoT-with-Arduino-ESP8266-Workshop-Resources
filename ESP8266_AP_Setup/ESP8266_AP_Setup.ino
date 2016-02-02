/*This program configures Access Point in the ESP8266 with the given SSID,PASSWORD,CHANNEL,ENCRYPTION_MODE, IP
 *And the ESP8266 can be joined to a router with the given ROUTER_SSID and ROUTER_PASSWORD 
 *On connecting to the AP and sending command # returns the IP & MAC of the device as in the AP as well as the joined router network
 */
#define LED 11  //Pin to connect the LED.

char data, str[100];
boolean flag = false;

//Setup run ONLY once
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);               //Default baudrate of ESP8266

  ////ESP8266 Configuration commands
  Serial.println("AT+RST");           // To reset ESP8266 to default value
  delay(2000);
  Serial.println("AT+CWMODE=3");      //To enable both Client and Accesspoint mode
  delay(200);
  Serial.println("AT+CWSAP=\"SSID\",\"PASSWORD\",6,4");        //To set accesspoint parameters SSID,PASSWORD,CHANNEL,ENCRYPTION_MODE
  delay(500);
  Serial.println("AT+CIPAP=\"192.168.4.1\"");        //To set IP of Access point
  delay(500);
  Serial.println("AT+CIPMUX=1");      //To enable multiple connections, compulsory for server operations
  delay(200);
  Serial.println("AT+CIPSERVER=1,60");//To start a SERVER at port 60 on ESP8266
  delay(200);
  Serial.println("AT+CWJAP=\"ROUTER_SSID\",\"ROUTER_PASSWORD\""); // Connect to a router.
  delay(1000);
}

void loop() {
  int i = 0;
  while (Serial.available())
  {
    data = Serial.read();
    if (data == '#')
    {
      flag = true;
    }
    delay(10);
  }
  if (flag) {
    delay(100);
    Serial.println("AT+CIFSR");
    while (!Serial.available()) {}
    while (Serial.available()) {
      if (Serial.find("AIP,")) {
        while (!Serial.available()) {}
        delay(10);
        data = Serial.read();
        while (data != '\r' && i < 19) {
          str[i] = data;
          i++;
          while (!Serial.available()) {}
          delay(10);
          data = Serial.read();
        }
        str[i] = ',';
        i++;
        Serial.find("AMAC,");
        while (!Serial.available()) {}
        delay(10);
        data = Serial.read();
        while (data != '\r' && i < 50) {
          str[i] = data;
          i++;
          while (!Serial.available()) {}
          delay(10);
          data = Serial.read();
        }
        str[i] = '\r';
      }
    }
    delay(500);
    Serial.print("AT+CIPSEND=0,");
    Serial.println(i + 2);
    delay(20);
    for (int j = 0; j < i ; j++) {
      Serial.print(str[j]);
      delay(10);
    }
    Serial.println();
    flag = false;
  }
}
