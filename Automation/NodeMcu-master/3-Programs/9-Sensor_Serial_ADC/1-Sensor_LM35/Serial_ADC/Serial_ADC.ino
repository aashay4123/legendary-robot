 
int sensorPin = A0;    // Connect A0 to PIN18 (LM35) of the IoT board     
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  Serial.begin(115200);
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin)/4;
  Serial.print("Room Temperature : ");
  Serial.print(sensorValue);
  Serial.print(" C");
  Serial.println();
  delay(1000);
 }

