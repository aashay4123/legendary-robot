 
int sensorPin = A0;    // select the input pin as 5 for Rain Sensor   (digital rain sensor)  
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() 
{



}

void loop() 
{
  
  Serial.begin(115200);
  // read the value from the sensor:
  
  sensorValue = analogRead(sensorPin);
  
  //Serial.println(sensorValue);
  // turn the ledPin on
  delay(100);
  if(sensorValue>965 || sensorValue>930)
  {
  Serial.println(" No Rain ");
  Serial.println(sensorValue);
  }
 else if(sensorValue>930)
 {
 Serial.println(" very very low Rainfall ");
 Serial.println(sensorValue);
 }
 else if(sensorValue>800)
 {
  Serial.println(" very low Rainfall ");
  Serial.println(sensorValue);
 }
 else if(sensorValue>700)
 {
   Serial.println(" slight Rainfall ");
  Serial.println(sensorValue);
 }
 else if(sensorValue>600)
 {
  Serial.println(" more than slight rainfall ");
  Serial.println(sensorValue);
 }
else if(sensorValue>500)
 {
  Serial.println(" Moderate Rainfall ");
  Serial.println(sensorValue);
 }
else if(sensorValue>400)
 {
  Serial.println(" Heavy ");
  Serial.println(sensorValue);
 }
delay(10);
}

