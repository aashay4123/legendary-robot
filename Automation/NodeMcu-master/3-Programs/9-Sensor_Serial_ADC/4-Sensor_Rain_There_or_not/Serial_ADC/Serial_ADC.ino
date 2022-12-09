 
int sensorPin = A0;    // select the input pin as 4 for Rain Sensor   (analog rain sensor)  
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
  // turn the ledPin on
  delay(100);
  if(sensorValue<35)
  {
    Serial.println(" It's Raining ");
    digitalWrite(LED_BUILTIN, HIGH);
  }
 else
 {
  Serial.println(" It's not Raining ");
  digitalWrite(LED_BUILTIN, LOW);
 }
delay(10);
}

