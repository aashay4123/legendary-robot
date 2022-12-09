#include <DHT.h>
#include <DHT_U.h>
#include <aJSON.h>
#include <SPI.h>
#include <WiFi.h>
#include <WifiIPStack.h>
#include <Countdown.h>
#include <MQTTClient.h>

char ssid[] = "TIonly";
char password[] = "donalduck";
//char ssid[] = "Pranav";
//char password[] = "pranav123";


int changeit;
int moisture , changesm, innertemp, humidity, lux;
int changem, changemt, changeh, changei, changel;
int value;

#define MQTT_MAX_PACKET_SIZE 100
#define IBMSERVERURLLEN  64
#define IBMIOTFSERVERSUFFIX "messaging.internetofthings.ibmcloud.com"


char organization[] = "mwxcba";
char typeId[] = "wifi_module";
char pubtopic[] = "iot-2/evt/status/fmt/json";
char subTopic[] = "iot-2/cmd/+/fmt/json";
char deviceId[] = "cc3200";
char clientId[64];
char mqttAddr[IBMSERVERURLLEN];
char authMethod[] = "use-token-auth";
char authToken[] = "aashay123";

int mqttPort = 1883;
const int moisture_pin = 33;
const int tec1 = 2, tec2 = 3;
const int fan1 = 4, fan2 = 5;
const int exhaust1 = 14, exhaust2 = 15;
const int led1 = 14, led2 = 15;
const int cled = 39, cexhaust = 40;
const int pump1 = 7, pump2 = 6;
const int ledPin = RED_LED;
MACAddress mac;

#ifdef TARGET_IS_CC3101
#include <Wire.h>
#include "Adafruit_TMP006.h"
Adafruit_TMP006 tmp006(0x41);
#endif

WifiIPStack ipstack;
MQTT::Client<WifiIPStack, Countdown, MQTT_MAX_PACKET_SIZE> client(ipstack);

// The function to call when a message arrives
void callback(char* topic, byte* payload, unsigned int length);
void messageArrived(MQTT::MessageData& md);
void heating();
void cooling();
void watering();
void exhaust();
void light();
double getTemp();

void setup() {
  uint8_t macOctets[6];

  Serial.begin(115200);
  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to Network named: ");
  // print the network name (SSID);
  Serial.println(ssid);
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) {
    // print dots while we wait to connect
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");

  while (WiFi.localIP() == INADDR_NONE) {
    // print dots while we wait for an ip addresss
    Serial.print(".");
    delay(300);
  }

  // We are connected and have an IP address.
  Serial.print("\nIP Address obtained: ");
  Serial.println(WiFi.localIP());

  mac = WiFi.macAddress(macOctets);
  Serial.print("MAC Address: ");
  Serial.println(mac);

  Serial.println(deviceId);

  sprintf(clientId, "d:%s:%s:%s", organization, typeId, deviceId);
  sprintf(mqttAddr, "%s.%s", organization, IBMIOTFSERVERSUFFIX);

#ifdef __CC3200R1M1RGC__
  if (!tmp006.begin()) {
    Serial.println("No sensor found");
    while (1);
  }
#endif
  pinMode(moisture_pin, INPUT);
  pinMode(tec1, OUTPUT);
  pinMode(tec2, OUTPUT);
  pinMode(fan1, OUTPUT);
  pinMode(fan2, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(pump1, OUTPUT);
  pinMode(pump2, OUTPUT);
  pinMode(exhaust1, OUTPUT);
  pinMode(exhaust2, OUTPUT);
  pinMode(cexhaust,OUTPUT);
}
void heating() {

  digitalWrite(tec1 , HIGH);
  digitalWrite(tec2 , LOW);
  Serial.print("heating started");
}
void cooling() {

  digitalWrite(tec1, LOW);
  digitalWrite(tec2, HIGH);
  Serial.print("cooling started");
}
void watering() {
  digitalWrite(pump1, HIGH);
  digitalWrite(pump2, LOW);
  delay(3000);
  digitalWrite(pump1, LOW);
  Serial.print("done wateringing");
}
void light(int var) {
  digitalWrite(led1 , HIGH);
  digitalWrite(led2 , LOW);
  analogWrite(cled , var);
  delay(1000);
  Serial.print("luxon");
}

void exhaust() {
  digitalWrite(exhaust1, HIGH);
  digitalWrite(exhaust2, LOW);
  analogWrite(cexhaust, 100);
  delay(1000);
  Serial.print("exhaust on");
  digitalWrite(exhaust1, LOW);
}


//void loop() {
//
//  int rc = -1;
//  if (!client.isConnected()) {
//    Serial.print("Connecting to ");
//    Serial.print(mqttAddr);
//    Serial.print(":");
//    Serial.println(mqttPort);
//    Serial.print("With client id: ");
//    Serial.println(clientId);
//
//    while (rc != 0) {
//      rc = ipstack.connect(mqttAddr, mqttPort);
//    }
//
//    MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;
//    connectData.MQTTVersion = 3;
//    connectData.clientID.cstring = clientId;
//    connectData.username.cstring = authMethod;
//    connectData.password.cstring = authToken;
//    connectData.keepAliveInterval = 10;
//
//    rc = -1;
//    while ((rc = client.connect(connectData)) != 0)
//      ;
//    Serial.println("Connected\n");
//
//    Serial.print("Subscribing to topic: ");
//    Serial.println(subTopic);
//
//    // Unsubscribe the topic, if it had subscribed it before.
//    client.unsubscribe(subTopic);
//    // Try to subscribe for commands
//    if ((rc = client.subscribe(subTopic, MQTT::QOS0, messageArrived)) != 0) {
//      Serial.print("Subscribe failed with return code : ");
//      Serial.println(rc);
//    } else {
//      Serial.println("Subscribe success\n");
//    }
//  }
//  // innertemp = DHT.readTemperature();
//  //  humidity = DHT.readHumidity();
//  MQTT::Message message;
//  message.qos = MQTT::QOS0;
//
////  if (changeit != getTemp())
////  {
////    char json[56] = "{\"d\":{\"myName\":\"TILaunchPad\",\"temperature\":";
////    dtostrf(getTemp(), 1, 2, &json[43]);
////    json[48] = '}';
////    json[49] = '}';
////    json[50] = '\0';
////    Serial.print("Publishing: ");
////    Serial.println(json);
////    message.retained = false;
////    message.payload = json;
////    message.payloadlen = strlen(json);
////    rc = client.publish(pubtopic, message);
////    if (rc != 0) {
////      Serial.print("Message publish failed with return code : ");
////      Serial.println(rc);
////    }
//  }
//  changeit = getTemp();
  innertemp = 20.25;
  //humidity = 30.24;
  if (changeit != innertemp)
  {
    char msg[56] = "{\"d\":{\"myName\":\"incubator\",\"temperature\":";

    dtostrf(innertemp, 1, 2, &msg[43]);
    msg[48] = '}';
    msg[49] = '}';
    msg[50] = '\0';
    Serial.print("Publishing: ");
    Serial.println(msg);
    message.retained = false;
    message.payload = msg;
    message.payloadlen = strlen(msg);
    rc = client.publish(pubtopic, message);
    if (rc != 0) {
      Serial.print("Message publish failed with return code : ");
      Serial.println(rc);
    }
    changeit = innertemp;
    // Wait for one second before publishing again
    // This will also service any incoming messages
    client.yield(1000);
  }
  if (changeh != humidity)
  {
    char msg1[56] = "{\"d\":{\"cc3200\":\"TILaunchPad\",\"humidity\":";

    dtostrf(humidity, 1, 2, &msg1[43]);
    msg1[48] = '}';
    msg1[49] = '}';
    msg1[50] = '\0';
    Serial.print("Publishing: ");
    Serial.println(msg1);
    message.retained = false;
    message.payload = msg1;
    message.payloadlen = strlen(msg1);
    rc = client.publish(pubtopic, message);
    if (rc != 0) {
      Serial.print("Message publish failed with return code : ");
      Serial.println(rc);
    }
    client.yield(1000);
  }
  changeh = humidity;
  int soilmois = 20;
  if (changesm != soilmois)
  {
    char msg2[56] = "{\"d\":{\"cc3200\":\"TILaunchPad\",\"soilmoisture\":";

    dtostrf(innertemp, 1, 2, &msg2[43]);
    msg2[48] = '}';
    msg2[49] = '}';
    msg2[50] = '\0';
    Serial.print("Publishing: ");
    Serial.println(msg2);
    message.retained = false;
    message.payload = msg2;
    message.payloadlen = strlen(msg2);
    rc = client.publish(pubtopic, message);
    if (rc != 0) {
      Serial.print("Message publish failed with return code : ");
      Serial.println(rc);
    }
    client.yield(1000);
  }
  changesm != soilmois;
}

void loop() {

  int rc = -1;
  if (!client.isConnected()) {
    Serial.print("Connecting to ");
    Serial.print(mqttAddr);
    Serial.print(":");
    Serial.println(mqttPort);
    Serial.print("With client id: ");
    Serial.println(clientId);
    
    while (rc != 0) {
      rc = ipstack.connect(mqttAddr, mqttPort);
    }

    MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;
    connectData.MQTTVersion = 3;
    connectData.clientID.cstring = clientId;
    connectData.username.cstring = authMethod;
    connectData.password.cstring = authToken;
    connectData.keepAliveInterval = 10;
    
    rc = -1;
    while ((rc = client.connect(connectData)) != 0)
      ;
    Serial.println("Connected\n");
    
    Serial.print("Subscribing to topic: ");
    Serial.println(subTopic);
    
    // Unsubscribe the topic, if it had subscribed it before.
    client.unsubscribe(subTopic);
    // Try to subscribe for commands
    if ((rc = client.subscribe(subTopic, MQTT::QOS0, messageArrived)) != 0) {
      Serial.print("Subscribe failed with return code : ");
      Serial.println(rc);
    } else {
      Serial.println("Subscribe success\n");
    }
  }

  char json[56] = "{\"d\":{\"myName\":\"TILaunchPad\",\"temperature\":";

  dtostrf(getTemp(),1,2, &json[43]);
  json[48] = '}';
  json[49] = '}';
  json[50] = '\0';
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
  
  // Wait for one second before publishing again
  // This will also service any incoming messages
  client.yield(1000);
}
void callback(char* topic, byte * payload, unsigned int length) {
  Serial.println("Message has arrived");

  char * msg = (char *)malloc(length * sizeof(char));
  int count = 0;
  for (count = 0 ; count < length ; count++) {
    msg[count] = payload[count];
  }
  msg[count] = '\0';
  Serial.println(msg);

  if (length > 0) {
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
  }

  free(msg);
}

void messageArrived(MQTT::MessageData & md) {
  Serial.print("Message Received\t");
  MQTT::Message &message = md.message;
  int topicLen = strlen(md.topicName.lenstring.data) + 1;
  //    char* topic = new char[topicLen];
  char * topic = (char *)malloc(topicLen * sizeof(char));
  topic = md.topicName.lenstring.data;
  topic[topicLen] = '\0';

  int payloadLen = message.payloadlen + 1;
  //    char* payload = new char[payloadLen];
  char * payload = (char*)message.payload;
  payload[payloadLen] = '\0';

  String topicStr = topic;
  String payloadStr = payload;

  //Command topic: iot-2/cmd/blink/fmt/msg

  if (strstr(topic, "/cmd/blink") != NULL) {
    Serial.print("Command IS Supported : ");
    Serial.print(payload);
    Serial.print(payloadStr);
    Serial.println("\t.....");

    pinMode(ledPin, OUTPUT);

    //Blink twice
    for (int i = 0 ; i < 2 ; i++ ) {
      digitalWrite(ledPin, HIGH);
      delay(250);
      digitalWrite(ledPin, LOW);
      delay(250);
    }
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
    if (value > innertemp) {
      heating();
    } else {
      cooling();
    }
  }
}

// getTemp() function for MSP430F5529
#if defined(__MSP430F5529)
// Temperature Sensor Calibration-30 C
#define CALADC12_15V_30C  *((unsigned int *)0x1A1A)
// Temperature Sensor Calibration-85 C
#define CALADC12_15V_85C  *((unsigned int *)0x1A1C)

double getTemp() {
  return (float)(((long)analogRead(TEMPSENSOR) - CALADC12_15V_30C) * (85 - 30)) /
         (CALADC12_15V_85C - CALADC12_15V_30C) + 30.0f;
}

// getTemp() function for Stellaris and TivaC LaunchPad
#elif defined(TARGET_IS_SNOWFLAKE_RA0) || defined(TARGET_IS_BLIZZARD_RB1)

double getTemp() {
  return (float)(147.5 - ((75 * 3.3 * (long)analogRead(TEMPSENSOR)) / 4096));
}

// getTemp() function for cc3200
#elif defined(__CC3200R1M1RGC__)
double getTemp() {
  return (double)tmp006.readObjTempC();
}
#else
double getTemp() {
  return 21.05;
}
#endif
