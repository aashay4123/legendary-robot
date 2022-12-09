#include <ESP8266WiFi.h>
#include <PubSubClient.h> 

//-------- Customise these values -----------
const char* ssid = "<yourSSID>";
const char* password = "<yourPassword>";

#define ORG "quickstart" // "quickstart" or use your organisation
#define DEVICE_ID "Test1s"      
#define DEVICE_TYPE "ESP8266" // your device type or not used for "quickstart"
#define TOKEN "xxxxxxxxxxxxx" // your device token or not used for "quickstart"
//-------- Customise the above values --------

char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[] = "iot-2/evt/status/fmt/json";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

WiFiClientSecure wifiClient;
PubSubClient client(server, 8883, wifiClient);

void setup() {
  Serial.begin(115200); Serial.println();

  Serial.print("Connecting to "); Serial.print(ssid);
  if (strcmp (WiFi.SSID().c_str(), ssid) != 0) {
     WiFi.begin(ssid, password);
  }
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }  
  Serial.println("");
  Serial.print("WiFi connected, IP address: "); Serial.println(WiFi.localIP());

  Serial.println("View the published data on Watson at: "); 
  if (ORG == "quickstart") {
    Serial.println("https://quickstart.internetofthings.ibmcloud.com/#/device/" DEVICE_ID "/sensor/");
  } else {
    Serial.println("https://" ORG ".internetofthings.ibmcloud.com/dashboard/#/devices/browse/drilldown/" DEVICE_TYPE "/" DEVICE_ID);
  }
}

void loop() {
   if (!!!client.connected()) {
      Serial.print("Reconnecting client to "); Serial.println(server);
      while ( ! (ORG == "quickstart" ? client.connect(clientId) : client.connect(clientId, authMethod, token))) {
        Serial.print(".");
        delay(500);
     }
     Serial.println();
   }

  String payload = "{\"d\":{\"myName\":\"ESP8266.Test5\",\"counter\":";
  payload += millis() / 1000;
  payload += "}}";
  
  Serial.print("Sending payload: "); Serial.println(payload);
    
  if (client.publish(topic, (char*) payload.c_str())) {
    Serial.println("Publish ok");
  } else {
    Serial.println("Publish failed");
  }

  delay(5000);
}

