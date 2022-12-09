




#include <ESP8266WiFi.h>
#include <Adafruit_BMP085.h>
 
String apiKey = "GR367GE9CROSI38Z";  //  Replace with your Write API key from ThingSpeak

const char *ssid =  "WiFi ssid";  // Enter your wifi ssid and password.
const char *pass =  "password";
const char* server = "api.thingspeak.com";



Adafruit_BMP085 bmp;



WiFiClient client;

void setup() 
{
       Serial.begin(115200);
       delay(10);
       bmp.begin();

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

      float p = bmp.readPressure();
      float t = bmp.readTemperature();
      float alt = bmp.readAltitude(101325);

                if (isnan(p) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }

                        if (client.connect(server,80))          //  "184.106.153.149" or api.thingspeak.com
                      {
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(p);
                             postStr +="&field3=";
                             postStr += String(alt);
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
                             Serial.print(" hPa, Pressure: ");
                             Serial.print(p);
                             Serial.print(" m, Altitude: ");
                             Serial.print(alt);
                             Serial.println("%. Send to Thingspeak.");
                         }
          client.stop();

         Serial.println("Waiting...");

  // thingspeak needs minimum 15 sec delay between updates,  here set to 30 seconds
  delay(10000);
}

