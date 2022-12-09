#include <ESP8266WiFi.h>
#include "HTTPSRedirect.h"
#include <Wire.h>

// Fill ssid and password with your network credentials
const char* ssid = "Aashay";
const char* password = "aashay1234";

const char* host = "script.google.com";
const int httpsPort = 443;
const char *GScriptId = "AKfycbyZmwcdxDpGY-QyH5KjDEXca-zbWSQbtGji0IMeWTVO6np2QSo/";

// Write to Google Spreadsheet
String url = host + String("/macros/s/") + GScriptId + "exec?tag=adc_A0&value=";

String payload = "";

HTTPSRedirect* client = nullptr;
// used to store the values of free stack and heap
// before the HTTPSRedirect object is instantiated
// so that they can be written to Google sheets
// upon instantiation

const int analog_ip = A0; 
int inputVal  = 1;        

void setup() {
  Serial.begin(115200);
  Serial.flush();
    
  Serial.println();
  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);
  Wire.begin(D1,D2);
  // flush() is needed to print the above (connecting...) message reliably, 
  // in case the wireless connection doesn't go through
  Serial.flush();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Use HTTPSRedirect class to create a new TLS connection
  client = new HTTPSRedirect(httpsPort);
  client->setPrintResponseBody(true);
  client->setContentTypeHeader("application/json");
  
  Serial.print("Connecting to ");
  Serial.println(host);

  // Try to connect for a maximum of 5 times
  bool flag = false;
  for (int i=0; i<5; i++){
    int retval = client->connect(host, httpsPort);
    if (retval == 1) {
       flag = true;
       break;
    }
    else
      Serial.println("Connection failed. Retrying...");
  }

  if (!flag){
    Serial.print("Could not connect to server: ");
    Serial.println(host);
    Serial.println("Exiting...");
    return;
  }
  
  payload = "tag=aaaa&value=12";
  client->POST(url, host, payload, false);
  client->GET(url, host); 
}

void loop() {
  static int connect_count = 0;
  static bool flag = false;
  String myString = String(inputVal);  
  String FinalStringToSend;
  FinalStringToSend = url + myString;

  
  if (client != nullptr){
    if (!client->connected()){
      client->connect(host, httpsPort);
      payload= "";
       Serial.println("POST Data to Sheet");
//      FinalStringToSend = url + myString;
  Serial.println("POST url :" + FinalStringToSend);
  client->POST(FinalStringToSend, host, payload);
    }
  }
  else{
  Serial.println(" >> Failed to POST data");
  }
  Serial.println("GET url :"+FinalStringToSend);
  client->GET(FinalStringToSend, host);

  delay(500);
                          
}
