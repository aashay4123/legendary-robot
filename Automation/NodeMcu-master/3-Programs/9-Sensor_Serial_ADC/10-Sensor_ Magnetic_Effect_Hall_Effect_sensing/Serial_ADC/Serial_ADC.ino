 
int sensorPin = A0;    // Connect pin A0 of NodeMCU to Pin 17 of Sensor Board      
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
  sensorValue = analogRead(sensorPin);
  
  //Serial.println(sensorValue);

  if(sensorValue>975)
  {
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("No Magnetism is Present");
  delay(100);
  }
  else
  {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Magnetism is Present");
  delay(100);
  }
  
 
  
}

