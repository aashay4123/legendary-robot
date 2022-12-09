#include <FS.h> // FOR SPIFFS
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
static const int wifiType = 0; // 0:Station  1:AP

//AP mode configuration
const char *AP_ssid = "web";
//Default is no password.If you want to set password,put your password here
const char *AP_password = "12345678";


int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

//Station mode you should put your ssid and password
const char *ssid = "wifi"; // Put your SSID here
const char *password = "12345678"; // Put your PASSWORD here

static IPAddress ip(192, 168, 1, 203); // static IP used for browser access: http://IPaddress
static IPAddress gateway(192, 168, 1, 1);
static IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80);

String Data = "";



void handleNotFound() {
  sensorValue = analogRead(sensorPin);
  String ipStr = WiFi.localIP().toString();
  if (wifiType == 1) // AP mode = 1
  {
    ipStr = WiFi.softAPIP().toString();
  }


  Serial.print("server uri: " ); Serial.println(server.uri());
  Data += String(sensorValue) + "<br>"; 
  //// default HTML
  String message = "<html><head>\n";
  message += "</head><body>\n";
  message += "<h1>Analog Data by Emtron</h1>\n";
  message += "<p>" + Data + "</p>";
  message += "</body></html>\n";
  server.send(200, "text/html", message);

}

void setup() {
  Serial.begin(115200);
  if (wifiType == 0) {
    if (!strcmp(ssid, "SSID")) {
      Serial.println("Please set your SSID");
    }
    if (!strcmp(password, "PASSWORD")) {
      Serial.println("Please set your PASSWORD");
    }
    // Connect to WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    
    Serial.println("WiFi connected");
    Serial.println("");
    Serial.print("ip: ");
    Serial.println(WiFi.localIP());
  } else if (wifiType == 1) {
    Serial.println();
    Serial.println();
    Serial.print("Share AP: ");
    Serial.println(AP_ssid);
    Serial.print("The password is: ");
    Serial.println(AP_password);

    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_ssid, AP_password);
    Serial.println("");
    Serial.println("AP ip");
    Serial.println(WiFi.softAPIP());
  }

    server.onNotFound(handleNotFound);
    server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:  
  server.handleClient();
  
}
