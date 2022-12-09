BMP180 Serial monitor
1. Download Adafruit BMP085 BMP180 libraries from https://github.com/adafruit/Adafruit-BMP085-Library
2. Download the wire.h library for I2C interface communication between BMP180 and arduino from https://github.com/esp8266/Arduino/blob/master/libraries/Wire/Wire.h
3. Include both libraries in the sketch
4. Initialization: Include sensor specific libraries i.e wire.h, Adafruit BMP085.(Sketch>> include library>> add .zip file)
5. Set baud rate(115200) and check for sensor connectivity using bmp.begin() function
6. BMP180 is a digital barometric pressure sensor which also gives the temperature value which affects the pressure.
   Read the temperature. Take 10 readings and store the same in a temperature array. Display each reading on the serial monitor.
7. Read altitude and take N-number of readings. Store readings in altitude array. Display each reading serially.
8. Calculate the pressure using the international barometric formula and store in a pressure array. Display each calculated reading serially. 
   Refer BMP180 datasheet for the international barometric formula https://cdn-shop.adafruit.com/datasheets/BST-BMP180-DS000-09.pdf 
9. Calculate and display the average temperature serially.
10. Find the minimum and maximum pressure readings using any sorting algorithm such as bubble sort, and display the same serially.
