 
int sensorPin = A0;    // select the input pin as 1 for sound sensor on sensor board and A0 of NodeMCU      
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() 
{
}

void loop() 
{
  Serial.begin(115200);
  
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  
 // Serial.println(sensorValue);
  
  delay(100);
  
  if(sensorValue>50)
  {
  Serial.println("Sound is Present");  
  delay(10);
  }
  else
  {
    Serial.println("Sound is not Present");
    delay(10);
  }

}

