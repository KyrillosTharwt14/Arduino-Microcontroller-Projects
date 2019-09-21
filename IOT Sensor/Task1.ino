#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp;
#include <ESP8266HTTPClient.h>

float mes ; 
float value ;
const char* ssid = "BME Students Lab 1 (2.4)";
const char* password = "mybmewifi";
WiFiServer server(80);
WiFiClient client;

String thingSpeakAddress= "http://api.thingspeak.com/update?";
String writeAPIKey;
String tsfield1Name;
String request_string;

HTTPClient http;

int i = 0 ; //for test graph mobile app
int j = 0 ; //for test graph mobile app
String t ;
String p ;
String a ;

void setup() {
  
  Serial.begin(115200);
  Wire.pins(2, 14);
  Wire.begin(2, 14);
  if (!bmp.begin()) {}
  WiFi.disconnect();
  // Connect to WiFi network
  WiFi.mode(WIFI_STA);
  Serial.println("start");
  WiFi.begin(ssid, password);
  Serial.println("");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  // Start TCP (HTTP) server
  server.begin();
  Serial.println("TCP server started");

}

void loop() {
  t = "T=" + String(bmp.readTemperature()) + " *C";
  p = "P=" + String(bmp.readPressure()) + " Pa";
  SendDataOnServer ();
  SendDataOnCloudDB (); 
}

void SendDataOnCloudDB ()
{
  
    /*i = i+10 ; 
    j= j+ 10 ; 
    String x = String (i) ;
    String y = String (i) ;*/
    if (client.connect("api.thingspeak.com",80))
    {
      request_string = thingSpeakAddress;
      request_string += "key=";
      request_string += "39EJ4I9C9ADBPLB3";
      request_string += "&";
      request_string += "field3";
      request_string += "=";
      request_string += String(bmp.readTemperature()) ;
      http.begin(request_string);
      http.GET();
      http.end();
      //for second sensor
      request_string = thingSpeakAddress;
      request_string += "key=";
      request_string += "39EJ4I9C9ADBPLB3";
      request_string += "&";
      request_string += "field4";
      request_string += "=";
      request_string += String(bmp.readPressure());
      http.begin(request_string);
      http.GET();
      http.end();
    }
    delay(500);
  }
void SendDataOnServer ()
{
  WiFiClient client = server.available();
  if (!client) { return; }
  //while(!client.available()){  delay(1); }
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  
  delay(2000);

  client.println(t);
  client.println(p);

  delay(1);
  }
