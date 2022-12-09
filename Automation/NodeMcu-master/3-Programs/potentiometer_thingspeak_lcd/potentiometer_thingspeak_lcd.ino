#include <ESP8266WiFi.h>
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 4, en = 0, d4 = 14, d5 = 12, d6 = 13, d7 = 15;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int sensorPin = A0;    // select the input pin for the potentiometer      
int sensorValue = 0;// variable to store the value coming from the sensor
float disp;
float x;
String apiKey = "aaaaaaaaaaaaaaaaaa";     //  Enter your Write API key from ThingSpeak

const char* ssid =  "aashay";     // replace with your wifi ssid  
const char* pass =  "12345678";  //   replace with your wifi PWD
const char* server = "api.thingspeak.com";
WiFiClient client;
void setup() {
  Serial.begin(115200);
       delay(10);// put your setup code here, to run once:
  pinMode(D4, OUTPUT); //A
  digitalWrite(D4, LOW);
  pinMode(D5, OUTPUT); //B
  digitalWrite(D5, LOW);
  pinMode(D6, OUTPUT); //C
  digitalWrite(D6, LOW);
WiFi.begin(ssid, pass);  
while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
        // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
}

void loop() {
 sensorValue = analogRead(sensorPin);  
  Serial.println(sensorValue);
  delay(100);
  disp = (sensorValue*6.5)/1020;
    // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
 
  if ((0<sensorValue)&&(sensorValue<10))
  {
    Serial.println(disp);
    Serial.println(" FULL GATE OPEN ");
    x = 1;
   lcd.setCursor(0, 0);
  lcd.print(disp);
  lcd.print("      ");
   lcd.setCursor(0, 1);
  lcd.print(" FULL GATE OPEN ");
  }
  else if((130<sensorValue)&&(sensorValue<150))
  {
  Serial.println(disp);
  Serial.println(" 3/4th GATE OPEN ");
  x = 0.75;
    lcd.setCursor(0, 0);  
    lcd.print(disp);
    lcd.print("      ");
 lcd.setCursor(0, 1);
  lcd.print(" 3/4th GATE OPEN ");
  }
  else if((275<sensorValue)&&(sensorValue<291))
  {
  Serial.println(disp);
  Serial.println(" HALF GATE OPEN ");
  x = 0.5;
    lcd.setCursor(0, 0);
    lcd.print(disp);
    lcd.print("      ");
   lcd.setCursor(0, 1);
  lcd.print(" HALF GATE OPEN ");
  }
  else if((420<sensorValue)&&(sensorValue<438))
  {
  Serial.println(disp);
  Serial.println(" 1/4th GATE OPEN, do not proceed further ");
  x = 0.25;
   lcd.setCursor(0, 0);
    lcd.print(disp);
    lcd.print(" STOP ");
   lcd.setCursor(0, 1);
  lcd.print(" 1/4th GATE OPEN ");
  }
  else
  {
  Serial.println(disp);
  Serial.println(" . ");
   lcd.setCursor(0, 0);
    lcd.print(disp);
    lcd.print("      ");
   lcd.setCursor(0, 1);
  lcd.print(" BETWEEN-2GATES ");
  }
  delay(500);
  if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(sensorValue);
                             postStr +="&field2=";
                             postStr += String(x);
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
                             Serial.println("%. send to thingspeak.");
 // put your main code here, to run repeatedly:

}
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
  delay(100);
}
