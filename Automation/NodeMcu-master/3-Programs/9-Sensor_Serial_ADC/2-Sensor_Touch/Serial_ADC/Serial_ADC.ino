 
int sensorPin = A0;    // select the input pin as 8 for Touch sensor on sensor board (A0 on NodeMCU board)     
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup()
{
  // declare the ledPin as an OUTPUT:
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() 
{
  Serial.begin(115200);

  sensorValue = analogRead(sensorPin);

  digitalWrite(LED_BUILTIN, HIGH);

  digitalWrite(LED_BUILTIN, LOW);

  
  delay(1000);
  
  if(sensorValue > 988)
  {
    Serial.println("Currently sensor is Touched");
  }
  else 
   {
    Serial.println("Currently sensor is not Touched");
   }
   
  delay(1000);
  
}

