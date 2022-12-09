 
int sensorPin = A0;    // connect A0 of NodeMCU to 10th Pin of sensor board for Moisture Sensing (Good or Low Moisture (digital))     
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() 
{
  // declare the ledPin as an OUTPUT:
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() 
{
Serial.begin(115200);
// read the value from the sensor:

delay(100);

sensorValue = analogRead(sensorPin);
//Serial.println(sensorValue);

Serial.print(sensorValue);

if(sensorValue<400)
{
  Serial.println("Excellent Moisture Level");
}
else if(sensorValue<430)
{
  Serial.println("Very Very High Level of Moisture");
}
else if(sensorValue<450)
{
  Serial.println(" Very High Level of Moisture");
}
else if(sensorValue<500)
{
  Serial.println(" High Level of Moisture");
}
else if(sensorValue<600)
{
  Serial.println("less than High Level of Moisture");
}
else if(sensorValue<700)
{
  Serial.println("low Level of Moisture");
}
else if(sensorValue<800)
{
  Serial.println(" Very Low Level of Moisture");
}
else if(sensorValue<900)
{
  Serial.println("Very Very Low Level of Moisture");
}
else if(sensorValue<960)
{
  Serial.println("Little bit of Moisture");
}
else
{
  Serial.println("Little bit of Moisture");
}

Serial.println();

delay(1000);

}

