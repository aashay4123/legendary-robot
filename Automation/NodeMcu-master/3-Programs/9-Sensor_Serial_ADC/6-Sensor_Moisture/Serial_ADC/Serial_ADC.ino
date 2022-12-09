 
int sensorPin = A0;    // connect A0 of NodeMCU to 9th Pin of sensor board for Moisture Sensing (Good or Low Moisture)     
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  Serial.begin(115200);
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  //Serial.println(sensorValue);


  delay(100);
 

  if(sensorValue<50)
  {
    Serial.println("Good Moisture level");
  }
  else
  {
    Serial.println("Low  Moisture level ");
  }
  delay(100);
}

