 
int sensorPin = A0;    // select the input pin for the potentiometer      
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  Serial.begin(115200);
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  Serial.print("LDR value ");
Serial.println(sensorValue);
  delay(1000);
}

