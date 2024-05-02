#include <DHT.h>  // Including library for dht
#include <ESP8266WiFi.h>
String apiKey = "HVJ69ZHYDTCAKW0X";     //  Enter your Write API key from ThingSpeak
const char *ssid =  "iQOO Neo7 Pro";     // replace with your wifi ssid and wpa2 key
const char *pass =  "Alfred1022";
const char* server = "api.thingspeak.com";
#define DHTPIN 14         //pin where the dht11 is connected
DHT dht(DHTPIN, DHT11);
WiFiClient client;
void setup() 
{
       Serial.begin(115200);
       delay(10);
       dht.begin();
       Serial.println("Connecting to ");
       Serial.println(ssid);

       WiFi.begin(ssid, pass);
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
}
void loop() 
{
      float h = dht.readHumidity();
      float t = dht.readTemperature();
              if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }
                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                             postStr += "\r\n\r\n";
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
          Serial.println("Waiting...");
  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}









#include <ESP8266WiFi.h> 
#include <DHT.h> 
#include <ThingSpeak.h> 
#include "MQ135.h"  
 
const char *ssid =  "Aaaaaaa";   
const char *pass =  "temppassword"; 
DHT dht(D5, DHT11); 
WiFiClient client; 
long myChannelNumber = 2410078; 
const char myWriteAPIKey[] = "LFOH0VKLJZAVFRJ6"; 
MQ135 gasSensor = MQ135(A0);  
int val;  
int sensorPin = A0;  
int sensorValue = 0;  
 
void setup() { 
  pinMode(sensorPin, INPUT);  
  // put your setup code here, to run once: 
  Serial.begin(115200); 
  WiFi.begin(ssid, pass); 
  while(WiFi.status() != WL_CONNECTED) 
  { 
    delay(200); 
    Serial.print(".."); 
  } 
  Serial.println(); 
  Serial.println("NodeMCU is connected!"); 
  Serial.println(WiFi.localIP()); 
  dht.begin(); 
  ThingSpeak.begin(client); 
} 
void loop() { 
  // put your main code here, to run repeatedly: 
  float h = dht.readHumidity(); 
  float t = dht.readTemperature(); 
  val = analogRead(A0);  
  Serial.print ("raw = ");  
  Serial.println (val);  
  float zero = gasSensor.getRZero();  
  Serial.print ("rzero: ");  
  Serial.println (zero);  
  float ppm = gasSensor.getPPM();  
  Serial.print ("ppm: ");  
  Serial.println (ppm);  
  Serial.println("raw: " + (String) val); 
  Serial.println("Rzero: " + (String) zero); 
   Serial.println("PPM: " + (String) ppm); 
  ThingSpeak.writeField(myChannelNumber, 1, val, myWriteAPIKey); 
  ThingSpeak.writeField(myChannelNumber, 2, zero, myWriteAPIKey); 
   ThingSpeak.writeField(myChannelNumber, 3, ppm, myWriteAPIKey); 
  Serial.println("Temperature: " + (String) t); 
  Serial.println("Humidity: " + (String) h); 
  ThingSpeak.writeField(myChannelNumber, 4, t, myWriteAPIKey); 
  ThingSpeak.writeField(myChannelNumber, 5, h, myWriteAPIKey); 
  delay(100); 
} 