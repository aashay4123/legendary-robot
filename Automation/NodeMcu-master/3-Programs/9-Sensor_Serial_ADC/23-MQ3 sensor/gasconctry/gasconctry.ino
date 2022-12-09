void setup() {
    Serial.begin(115200);
}

void loop() {

    float R0;
    float sensor_volt;
    float RS_gas; // Get value of RS in a GAS
    float ratio; // Get ratio RS_GAS/RS_air
    float sensorValue;

     /*--- Get a average data by testing 100 times ---*/
    for(int x = 0 ; x < 100 ; x++)
    {
        sensorValue = sensorValue + analogRead(A0);
    }
    sensorValue = sensorValue/100.0;
    /*-----------------------------------------------*/
    
    //int sensorValue = analogRead(A0);
    Serial.print("sensor value= ");
    Serial.println(sensorValue);
    sensor_volt=(float)sensorValue/1024*5.0;
    RS_gas = (5.0-sensor_volt)/sensor_volt; 
    //R0 = RS_air/60.0; // The ratio of RS/R0 is 60 in a clear air from Graph 

    
    ratio = RS_gas/0.03;  // ratio = RS/R0
    /*-----------------------------------------------------------------------*/
    Serial.print("Rs/R0 = ");
    Serial.println(ratio);
    Serial.print("sensor_volt = ");
    Serial.println(sensor_volt);
    Serial.print("RS_ratio = ");
    Serial.println(RS_gas);
    

    Serial.print("\n\n");

    delay(1000);

    /*float y;
    float x;
    y=ratio;
    //y-1=-0.75*(x-0.4);
    x=((y-1)/(-0.75))+0.4;

    
    //if(y=2.1)
    Serial.print("The gas conc in mg/L is");
    Serial.println(x);*/

    float x1[10] = {0.1, 0.21, 0.4, 1, 1.7, 2.5, 4, 6, 8, 10};
    float y1[10] = {2.3, 1.7, 1, 0.55, 0.4, 0.3, 0.2, 0.16, 0.14, 0.12};
    float n = (sizeof(x1)/sizeof(float));
    Serial.println(n);
    float a1=0;
    float a2 = 0;
    float a3 = 0;
    float a4 = 0;
    for(int t=0; t<10; t++)
    {
      a1 = a1+x1[t];//summation(x)
      a2 = a2 + sq(x1[t]);  // summation(x^2)
      a3 = a3 + y1[t];   //summation(y);
      a4 = a4 +( x1[t]*y1[t]); //summation (x*y)
      //Serial.println(a1);
      //Serial.println(a2);
      //Serial.println(a3);
      //Serial.println(a4);
      
    }
    float a;
    float b;
    a = ((a3*a2)-(a1*a4))/((n*a2)-sq(a1));
    b = ((n*a4)-(a1*a3))/((n*a2)-sq(a1));

    Serial.println("a1=");
    Serial.println(a1);
    Serial.println(a2);
    Serial.println(a3);
    Serial.println(a4);
    Serial.println("a= ");
    Serial.println(a);
    Serial.println("b= ");
    Serial.println(b);
    Serial.println(n);
      //Serial.println(a3);
      //Serial.println(a4);

    float y2 = ratio;
    float x2 = (y2 - a)/b;
    Serial.print("The gas conc in mg/L is");
    Serial.println(x2);

    

}
