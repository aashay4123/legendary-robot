#include <SPI.h>
#include <WiFi.h>
#include <WifiIPStack.h>
#include <Countdown.h>
#include <MQTTClient.h>

char ssid[] = "aashay";
char password[] = "aashay123";
char printbuf[100];
int arrivedcount = 0;
int value;
int rc = -1;
char pubtopic[] = "sub/smoke_sensor";
char subTopic[] = "pub/light_2";
const char* topic = "energia-sample";
#include "Adafruit_TMP006.h"
Adafruit_TMP006 tmp006(0x41);


void messageArrived(MQTT::MessageData& md)
{
  MQTT::Message &message = md.message;

  sprintf(printbuf, "Message %d arrived: qos %d, retained %d, dup %d, packetid %d\n",
          ++arrivedcount, message.qos, message.retained, message.dup, message.id);
  Serial.print(printbuf);
  sprintf(printbuf, "Payload %s\n", (char*)message.payload);
  Serial.print(printbuf);
  int topicLen = strlen(md.topicName.lenstring.data) + 1;
  char * topic = (char *)malloc(topicLen * sizeof(char));
  topic = md.topicName.lenstring.data;
  topic[topicLen] = '\0';

  int payloadLen = message.payloadlen + 1;
  char * payload = (char*)message.payload;
  payload[payloadLen] = '\0';

  String topicStr = topic;
  String payloadStr = payload;
  Serial.print(topic);
  Serial.print(payload);

  if (strstr(topic, "/cmd/blink") != NULL) {
    Serial.print("Command IS Supported : ");
    Serial.print(payload);
    Serial.print(payloadStr);
    Serial.println("\t.....");
  } else if (strstr(topic, "/cmd/settemp") != NULL) {
    Serial.print("temperature set to:");
    Serial.println(payload);
    char value1[2];
    value1[0] = payloadStr[15];
    value1[1] = payloadStr[16];
    value1[2] = '\0';

    Serial.print(value1);
    String str(value1);
    value = str.toInt();
    Serial.println(value);
  }
}

WifiIPStack ipstack;
MQTT::Client<WifiIPStack, Countdown> client = MQTT::Client<WifiIPStack, Countdown>(ipstack);

void connect()
{
  char hostname[] = "broker.mqtt-dashboard.com";
  int port = 1883;
  sprintf(printbuf, "Connecting to %s:%d\n", hostname, port);
  Serial.print(printbuf);
  int rc = ipstack.connect(hostname, port);
  if (rc != 1)
  {
    sprintf(printbuf, "rc from TCP connect is %d\n", rc);
    Serial.print(printbuf);
  }
  Serial.println("MQTT connecting");
  MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
  data.MQTTVersion = 3;
  data.clientID.cstring = (char*)"energia-sample";
  rc = client.connect(data);
  if (rc != 0)
  {
    sprintf(printbuf, "rc from MQTT connect is %d\n", rc);
    Serial.print(printbuf);
  }
  Serial.println("MQTT connected");

  rc = client.subscribe(topic, MQTT::QOS2, messageArrived);
  if (rc != 0)
  {
    sprintf(printbuf, "rc from MQTT subscribe is %d\n", rc);
    Serial.print(printbuf);
  }
  Serial.println("MQTT subscribed");
}

void setup()
{
  Serial.begin(115200);
  Serial.print("Attempting to connect to Network named: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");

  while (WiFi.localIP() == INADDR_NONE) {
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nIP Address obtained");
  Serial.println(WiFi.localIP());
  Serial.println("MQTT Hello example");
  connect();
  subscr();
}


void subscr() {
  Serial.print("Subscribing to topic: ");
  Serial.println(subTopic);
  // client.unsubscribe(subTopic);

  if ((rc = client.subscribe(subTopic, MQTT::QOS0, messageArrived)) != 0) {
    Serial.print("Subscribe failed with return code : ");
    Serial.println(rc);
  } else {
    Serial.println("Subscribe success\n");
  }
}
#if defined(__CC3200R1M1RGC__)
double getTemp() {
  return (double)tmp006.readObjTempC();
}
#else
double getTemp() {
  return 21.05;
}
#endif
void mq2_sensor() {
  arrivedcount = 0;
  float val = 24.4;
  char json[20] = "\0" ;
  sprintf ( json, "{value: %f}", val);
  //dtostrf(getTemp(), 1, 2, &json[43]);
  Serial.print("Publishing: ");
  Serial.println(json);
  MQTT::Message message;
  message.qos = MQTT::QOS0;
  message.retained = false;
  message.payload = json;
  message.payloadlen = strlen(json);
  rc = client.publish(pubtopic, message);
  if (rc != 0) {
    Serial.print("Message publish failed with return code : ");
    Serial.println(rc);
  }
  client.yield(1000);
}

void loop()
{
  if (!client.isConnected())
    connect();

  mq2_sensor();

}
/*
  void upload(char msg[20]) {
  char* token = strtok(msg, "/");
  int i = 0;
  while (token != NULL) {
    value[i] = token;
    token = strtok(NULL, "/");
    i++;
    if (value[0] == "home") {
      if (value[1] == "valve2") {
        if (value[2] == "onn") {
          client.publish(h2pubs, "supply2 ONN");
          delay(2);
          flowon = 1;
          digitalWrite(soloval, LOW);
        } else if (value[2] == "off") {
          client.publish(h2pubs, "supply2 OFF");
          delay(2);
          digitalWrite(soloval, HIGH);
          flowon = 0;
        }
      } else if (value[1] == "volume") {
        temp = value[2].toFloat();
        Serial.print(temp);
      }
    }
  }
  }*/
