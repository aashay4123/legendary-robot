#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include<String.h>

const char* ssid = "Aashay";
const char* password = "aashay123";
const char* mqtt_server = "broker.mqtt-dashboard.com";

WiFiClient espClient;
PubSubClient client(espClient);

const byte numChars = 100;
char receivedChars[numChars], msg[numChars]; // an array to store the received data
boolean newData = false;
String value[5];

const char* l1pub = "home/light_1/state";
const char* l2pub = "home/light_2/state";
const char* f1pub = "home/fan_1/state";
const char* f2pub = "home/fan_2/state";

const char* disp = "home/display";
const char* l1sub = "pub/room1/light_1";
const char* l2sub = "pub/room1/light_2";
const char* f1sub = "pub/room1/fan_1";
const char* f2sub = "pub/room1/fan_2";

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;

    }
  }
}

void upload(char msg[20]) {


  char* token = strtok(msg, "/");
  int i = 0;
  while (token != NULL) {
    value[i] = token;
    token = strtok(NULL, "/");
    i++;
    if (value[0] == "home") {
      if (value[1] == "Lgt_1") {
        if (value[2] == "onn") {
          client.publish(l1pub, "Light ON");
          delay(2);
        } else if (value[2] == "off") {
          client.publish(l1pub, "Light OFF");
          delay(2);
        }
      } else if (value[1] == "Lgt_2") {
        if (value[2] == "onn") {
          client.publish(l2pub, "Light ON");
          delay(2);
        } else if (value[2] == "off") {
          client.publish(l2pub, "Light OFF");
          delay(2);
        }
      } else if (value[1] == "fan_1") {
        if (value[2] == "onn") {
          client.publish(f1pub, "Fan ON");
          delay(2);
        } else if (value[2] == "off") {
          client.publish(f1pub, "Fan OFF");
          delay(2);
        }
      } else if (value[1] == "fan_2") {
        if (value[2] == "onn") {
          client.publish(f2pub, "Fan ON");
          delay(2);
        } else if (value[2] == "off") {
          client.publish(f2pub, "Fan OFF");
          delay(2);
        } else {
          client.publish(disp, msg);
          delay(2);
        }

      }
    }
  }
}
void callback(char* topic, byte * payload, unsigned int length) {

  for (int i = 0; i < length; i++) {

    msg[i] = (char)payload[i];
  }
  delay(2);
  Serial.print(msg);
  upload(msg);
}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe(f1sub);
      client.subscribe(f2sub);
      client.subscribe(l1sub);
      client.subscribe(l2sub);
      client.subscribe(disp);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  recvWithEndMarker();
  upload(receivedChars);
  memset(receivedChars, 0, sizeof(receivedChars));
}
