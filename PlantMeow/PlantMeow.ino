#include <elapsedMillis.h>

/* ==========================================================
Project : Send Photo resistor values to computer
Author: ScottC / Edited by Ariellelellleeel
Created: 25th June 2011
Description: This sketch will make the arduino read Photo resistor
             values on analog pin A0. The analog readings will
             be dependent on the amount of light reaching the
             sensor. The Analog readings will be sent to the
             computer via the USB cable using Serial communication.
==============================================================
*/

int photoRPin = 0; 
int minLight;          //Used to calibrate the readings
int maxLight;          //Used to calibrate the readings
int avgLight;
int lightLevel;
elapsedMillis timeElapsed;

int lightMin = 850; // Sunny: 900s, sunny shadows: 840

void setup() {
 Serial.begin(9600);
 avgLight = 700;
}

void meow() {
 Serial.println(meow);
}

void loop(){
 //auto-adjust the minimum and maximum limits in real time
 lightLevel=analogRead(photoRPin);
 
 //Send the adjusted Light level result to Serial port (processing)
 Serial.println(lightLevel);

 if(avgLight < lightMin {
   if(lightLevel < lightMin) {
    meow();
   }
 }
 //slow down the transmission for effective Serial communication.
 delay(50);
}
