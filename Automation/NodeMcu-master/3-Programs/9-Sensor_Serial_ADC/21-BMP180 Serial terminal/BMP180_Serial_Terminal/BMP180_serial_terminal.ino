#include <Wire.h>
#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  if (!bmp.begin())
  {
    Serial.println("Pressure sensor BMP180 not found");
    while (1) {}
  }
}

void loop() {
  double temp[100];
  double pressure1[100];
  double alt[100];
  int i=0;
  int j = 0;
  double po = 1013.25;
  double t = 0;
  while (j < 10)
  {
    temp[j] = bmp.readTemperature();
    Serial.println("  ");
    Serial.print("Temperature reading  ");
    Serial.print(j);
    Serial.print("  ");
    Serial.print(temp[j]);
    delay(2000);
    
    alt[j] = bmp.readAltitude(101325);
    Serial.println("   ");
    Serial.print("Altitude reading: ");
    Serial.print(j);
    Serial.print("  ");
    Serial.print(alt[j]);
    
    double c1 = (alt[j] / (44330));
    double c = (1 - c1);
    double p = po * pow(c, 5.255);
    pressure1[j]=p;
    Serial.println("  ");
    Serial.print("pressure reading:  ");
    Serial.print(j);
    Serial.print("  ");
    Serial.print(pressure1[j]);
    j++;
    delay(2000);
  }
  
  for (i = 0; i < 10; i++)
  {
    t = t + temp[i];
  }
  double avgt = t / i;
  Serial.println("   ");
  Serial.print("Average temperature from 10 readings is: ");
  Serial.print(avgt);
  
  for (i=0;i<10;i++)
  {
    for(j=0;j<10;j++)
   { 
        if(pressure1[j]>pressure1[j+1])
      {
        double m=pressure1[j];
        pressure1[j]=pressure1[j+1];
        pressure1[j+1]=m;
     }
   }
 }
 Serial.println("   ");
 Serial.print("Minimum and maximum pressure are :");
 Serial.println(pressure1[0]);
 Serial.println(pressure1[j]);
delay(5000);
 }
 


