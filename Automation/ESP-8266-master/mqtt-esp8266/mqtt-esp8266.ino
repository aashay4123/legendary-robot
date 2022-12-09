//#include <aJSON.h>
#include <WiFi.h>
#include<SPI.h>
#include<PubSubClient.h>
#include<string.h>

//initialization for wifi
IPAddress shieldIP, subnetMask, gatewayIP;
uint8_t rssi;

uint8_t networkId;
byte macAddr[6];
byte encryptionType;
char ssid[] = "aashay" ; //my cell phone name
char password[] = "connected";

WiFiClient wclient;
void callback(char* inTopic, byte* payload , unsigned int length);
byte server[] = {198 , 41 , 30 , 241};   //public MQTT broker given by eclipse since the board cannot directly to the cloud it requires a middle man which is eclipse

PubSubClient client(server, 1883, callback, wclient); //PubSubClient is a thread running in parallel with void loop

char* jsonPayload;

void setup() {

  /////Setup for Wifi//////
  Serial.begin(115200);
  Serial.print("Connecting to WIFI...");

  while (WiFi.begin(ssid, password) != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1);
  }
  Serial.print("");
  Serial.print("Wifi connected , Fetching Wifi sheild's IP Address:");
  while (WiFi.localIP() == INADDR_NONE) {
    Serial.print(".");
    delay(1);
  }
  shieldIP = WiFi.localIP();
  Serial.println(shieldIP);

  Serial.print("Access point name :");
  Serial.println(ssid);

  Serial.print("Signal Strength :");
  rssi = WiFi.RSSI();
  Serial.println(rssi);

  uint8_t networkId = WiFi.scanNetworks();
  Serial.print("Number of access point in range :");
  Serial.println(networkId);

  for (int i = 1; i <= networkId; i++) {
    Serial.print("Name of Access Points and Encryption type:");
    Serial.print(WiFi.SSID(i));
    Serial.print(",");
    encryptionType = WiFi.encryptionType(i);
    Serial.println(encryptionType, HEX);
  }

  subnetMask = WiFi.subnetMask();
  Serial.print("Subnet Mask: ");
  Serial.println(subnetMask);

  gatewayIP = WiFi.gatewayIP();
  Serial.print("Gateway IP address: ");
  Serial.println(gatewayIP);

  WiFi.macAddress(macAddr);
  Serial.print("Mac Address of shield: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(macAddr[i], HEX);
    if (i <= 4)
      Serial.print(':');
    else
      Serial.println();
  }
}

void loop() {

  if (!client.connected()) {
    Serial.println("Disconnected: Reconnecting ....");
    if (!client.connect("Msp432")) {
      Serial.println("connection failed");
    }
    else {
      Serial.println("Connection Success");
      if (client.subscribe("toMSP432")) {
        Serial.println("Subscription Successful");
      }
    }
  }


  int result, regressedData1;
  float regressedData;

  /*while(!ADC14_isBusy());

    result = ADC14_getResult(ADC_MEM6);
    //P2OUT = result >> 8;
    ADC14_toggleConversionTrigger();
    regressedData = ((result*0.789630809) + 2.98915859)/1000;
    Serial.println(regressedData);
    regressedData1 = ((result*0.789630809) + 2.98915859);
    P2 -> OUT = result>>8;
  */
  //convert to char array
  String str = (String)regressedData1;
  int str_len = str.length() + 2 ;//length with two extra characters one for decimal point and the other for null character

  char char_array[str_len];
  str.toCharArray(char_array, str_len); //putting the regressedData1 string str into char_array

  //Data processing
  char pot_reading[str_len];

  if (regressedData < 1) {
    pot_reading[0] = '0';
    pot_reading[1] = '.';

    for (int i = 2 ; i <= str_len; i++ ) {
      pot_reading[i] = char_array[i - 2];
    }
  }
  else {
    pot_reading[0] = char_array[0];
    pot_reading[1] = '.';
    for (int i = 2 ; i <= str_len; i++ ) {
      pot_reading[i] = char_array[i - 1];
    }

  }

  /*aJsonObject *root = aJson.createObject();
    aJsonObject *d = aJson.createObject();
    aJson.addItemToObject(root,"d",d);
    aJson.addStringToObject(d,"IbmCloudPotTarun","MSP432");
    aJson.addStringToObj//ect(d,"potValue",pot_reading);

    jsonPayload = aJson.print(root) + '\0';

    aJson.deleteItem(d);
    aJson.deleteItem(root);

  */
  //publish data to MQTT
  client.publish("sensorPotTarun", jsonPayload);

  client.loop(); // acts as thread.wait which allows the callback function of PubSubclient to run that is if a message has arrived from the broker
  delay(1000);

  //Serial.println(result);
  Serial.println(regressedData);
}

void callback(char* inTopic, byte* payload , unsigned int length)
{
  Serial.print("Message arrived on topic:");
  Serial.print(inTopic);
  Serial.print(". Message : ");
  String arrivedMessage;

  for (int i = 0; i < length ; i++ ) {
    Serial.print((char)(payload[i]));
    arrivedMessage += (char)(payload[i]);

  }
  if (arrivedMessage.equals("on"))
  {
    //      GPIO_setOutputHighOnPin(GPIO_PORT_P1,GPIO_PIN0);
  }
  if (arrivedMessage.equals("off"))
  {
    //        GPIO_setOutputLowOnPin(GPIO_PORT_P1,GPIO_PIN0);
  }
  Serial.println();
}

/*void turnOnLED(void)
  {
    GPIO_setOutputHighOnPin(GPIO_PORT_P1,GPIO_PIN0);
  }
  void turnOffLED(void)
  {
    GPIO_setOutputLowOnPin(GPIO_PORT_P1,GPIO_PIN0);
  }
*/
