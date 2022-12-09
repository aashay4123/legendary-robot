 
int sensorPin = A0;    // Connect A0 pin of NodeMCU  to 14th pin of Sensor Board       
int sensorValue = 0;   //  variable to store the value coming from the sensor

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() 
{
  
  Serial.begin(115200);
  sensorValue = analogRead(sensorPin);
  
  if(sensorValue<50)
  {
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println(" No Vibration ");
  delay(100);  
  }
  else
  {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println(" There is a Vibration ");
  delay(100);
  }
  
}

