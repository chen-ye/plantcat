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

elapsedMillis timeElapsed;

// LED stuff
int ledPin = 10;
int ledOn = false;

// Light Stuff
int photoRPin = 0; 
int lightLevel;

int lightMin = 300; //850; // Sunny: 900s, sunny shadows: 840

int lightAvg;

// Temp Stuff
int tempPin = 1;
int temp;

int tempMin = 0;
int tempMax = 100;


void setup() {
 Serial.begin(9600);
 pinMode(ledPin, OUTPUT);
 lightAvg = analogRead(photoRPin);
}

void loop(){
 // LIGHT READING
 lightLevel = analogRead(photoRPin);

 lightAvg = (lightAvg + lightLevel)/2;

 //Serial.print("Current lightLevel: ");
 //Serial.print(lightLevel);
 //Serial.println();
 
 //Send the adjusted Light level result to Serial port (processing)
 //Serial.println(lightAvg);


 // TEMPERATURE READING 
 temp = analogRead(tempPin);
 
 // Convert to Celsius
 float voltage = (temp * 5.0)/1023.0;
 Serial.print(voltage); Serial.println(" volts");

 float temperatureC = ((voltage*1000) - 500) / 10 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 //Serial.print(temperatureC); Serial.println(" degrees C");

 // EMOTION
 if (lightAvg >= lightMin && ledOn) {
    digitalWrite(ledPin, LOW);
    ledOn = false;
 } else if (lightAvg < lightMin && !ledOn) {
    digitalWrite(ledPin, HIGH);
    ledOn = true;
 }
 
 //slow down the transmission for effective Serial communication.
 delay(50);
}
