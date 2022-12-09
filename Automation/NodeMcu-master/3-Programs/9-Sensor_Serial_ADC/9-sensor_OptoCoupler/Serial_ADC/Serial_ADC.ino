 
int sensorPin = A0;    // Connect A0 of NodeMCU to 19th pin that is optocoupler     
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
  delay(500);
  
  if(sensorValue<=80)
  {
  // turn the ledPin on
  //digitalWrite(LED_BUILTIN, HIGH);
  // stop the program for <sensorValue> milliseconds:
  //delay(sensorValue);

  Serial.println("Object not Present");
  }
  else
  {
  // turn the ledPin off:
  //digitalWrite(LED_BUILTIN, LOW);
  // stop the program for for <sensorValue> milliseconds:
  //delay(sensorValue);
  Serial.println("Object Present");
  }
  
  delay(500);
}

