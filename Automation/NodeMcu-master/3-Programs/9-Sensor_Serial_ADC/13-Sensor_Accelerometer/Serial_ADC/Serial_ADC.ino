//const int xPin = A0;    //x-axis of the Accelerometer
  const int yPin = A0;    //x-axis of the Accelerometer
//const int zPin = A0;    //x-axis of the Accelerometer

/*void setup() 
{
  // initialize serial communications at 9600 bps:
  Serial.begin(115200);
}

void loop() 
{ 
  int x = analogRead(xPin);
  delay(1000);
  Serial.print("X-axis : ");
  Serial.println(x);
}*/


void setup() 
{
  // initialize serial communications at 9600 bps:
  Serial.begin(115200);
}

void loop() 
{ 
  int Y = analogRead(yPin);
  delay(1000);
  Serial.print("Y-axis : ");
  Serial.println(Y);
}

/*
void setup() 
{
  // initialize serial communications at 9600 bps:
  Serial.begin(115200);
}

void loop() 
{ 
  int z = analogRead(zPin);
  delay(1000);
  Serial.print("Z-axis : ");
  Serial.println(z);
}
*/
