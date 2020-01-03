#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h> 
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>

#define ONE_WIRE_BUS 5
#define DHT11_PIN 4

const char* ssid = "ssid"; 
const char* password = "password"; 

const char* host = "https://young-ocean-79520.herokuapp.com"; //edit the host adress, ip address etc. 
String url;

DHT dht;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
char temperatureCString[7];
char temperatureCStringMax[7];
char temperatureCStringMin[7];
char temperatureFString[7];
float tempC;
float tempCmin;
float tempCmax;
 
void setup() { 
  Serial.begin(115200); 

  dht.setup(DHT11_PIN);
  DS18B20.begin();
  
  delay(10); // We start by connecting to a WiFi network 
  Serial.println(); 
  Serial.println(); Serial.print("Connecting to "); 
  Serial.println(ssid); 
  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default, would try to act as both a client and an access-point and could cause network-issues with your other WiFi-devices on your WiFi-network. */ 
  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500); 
    Serial.print("."); 
  } 
  Serial.println(""); 
  Serial.println("WiFi connected"); 
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());

  
} 

 void getTemperature() {
  //float tempC;
  float tempF;
  do {
    DS18B20.requestTemperatures(); 
    tempC = DS18B20.getTempCByIndex(0);
    dtostrf(tempC, 2, 2, temperatureCString);
    tempF = DS18B20.getTempFByIndex(0);
    dtostrf(tempF, 3, 2, temperatureFString);
    delay(100);
  } while (tempC == 85.0 || tempC == (-127.0));
}
  
void loop() { 
  delay(5000); 
  getTemperature();
  int humidity_temporary = dht.getHumidity();
  int dht_temp= dht.getTemperature();

  if(dht.getStatusString() == "OK") {
      Serial.print(humidity_temporary);
      Serial.println("%");
      Serial.print(dht_temp);
      Serial.println("C");
      String humidity = String(humidity_temporary);
      Serial.println("Temp: "); Serial.println(temperatureCString);
      String temp_temp = String(temperatureCString);
      url = "/" + temp_temp + "/" + humidity + "/01";
      Serial.println("Temp: "); Serial.println(url);

      Serial.print("connecting to "); 
      Serial.println(host); // Use WiFiClient class to create TCP connections 
      WiFiClient client; 
      const int httpPort = 8000;

      Serial.print("Requesting URL: "); 
      Serial.println(url); //Post Data 
      String postData = "adcreading"; 
      String address = host + url; 
      HTTPClient http; 
      http.begin(address, "083b717202436ecaed428693ba7edf81c4bc6230"); 
      http.addHeader("Content-Type", "application/x-www-form-urlencoded"); 
      auto httpCode = http.POST(postData); 
      Serial.println(httpCode); //Print HTTP return code 
      String payload = http.getString(); 
      Serial.println(payload); //Print request response payload 
      http.end(); //Close connection Serial.println(); 
      Serial.println("closing connection");
    }
    

  ESP.deepSleep(30e7);
  //delay(50000);
}
