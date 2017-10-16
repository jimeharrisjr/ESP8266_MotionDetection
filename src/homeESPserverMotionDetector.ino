
/*
  Based upon the ESP8266 sample code in the Arduino ESP8266 libraries
  https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi
  Your WiFi credentials and IFTTT.com maker key and event info are 
  placed in cred.h 

 */


#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include <ESP8266Ping.h>

int val;
// Read cred.h to define the WiFi and IFTTT credentials
#include "cred.h"


// TCP server at port 80 will respond to HTTP requests
WiFiServer server(80);

void setup(void)
{ 
  
  
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  // This is weird, but because the detector is Active HIGH, and ESP8266 needs IO's high, make GPIO 0 LOW
  // And attach that to the NPN transistor as the new GND
  pinMode(2, INPUT);
  pinMode(0, OUTPUT);
  digitalWrite(0, LOW);
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.println("");  
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // These lines are mainly for troubleshooting from the Arduino IDE Serial Monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC address: ");
  Serial.print(WiFi.macAddress());
  Serial.println("");
  boolean p;


}

void loop(void)
{
  val = digitalRead(2);
  if(val==0) {
     // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
   if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return;
    }
  
  // We now create a URI for the request
  // construct the POST request
  // This POST request is customized for IFTTT Maker
  

  String p;
  p = "POST /trigger/";
  p += event;
  p += "/with/key/";
  p += key;
  p += " HTTP/1.1\r\n";
  p += "Host: maker.ifttt.com\r\n";

  Serial.print("Requesting URL: ");
  Serial.println(p);

  // This will send the request to the server
  client.print(p + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(10000);

  // Read all the lines of the reply from server and print them to Serial
  Serial.println("Respond:");
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  }  
}
  


