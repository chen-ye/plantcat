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
int HAPPY = 10;
int NEUTRAL = 11;
int SAD = 12;
int currentState = NEUTRAL;
int newState;

// Light Stuff
int photoRPin = 0; 
int lightLevel;
int lightHappiness = 0;

int lightMin = 300; //850; // Sunny: 900s, sunny shadows: 840

// Temp Stuff
int tempPin = 1;
int temp;

int tempMin = 0;
int tempMax = 100;

// Happiness
float happiness = 0;
float oldMult = 0.9;
float newMult = 0.1;


void setup() {
 Serial.begin(9600);
 pinMode(HAPPY, OUTPUT);
 pinMode(NEUTRAL, OUTPUT);
 pinMode(SAD, OUTPUT);
}

void loop(){
 // LIGHT READING
 lightLevel = analogRead(photoRPin);

 Serial.print("Current lightLevel: ");
 Serial.print(lightLevel);
 Serial.println();

 // TEMPERATURE READING 
 temp = analogRead(tempPin);
 
 // Convert to Celsius
 float voltage = (temp * 5.0)/1023.0;
// Serial.print(voltage); Serial.println(" volts");

 float temperatureC = ((voltage*1000) - 500) / 10 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 //Serial.print(temperatureC); Serial.println(" degrees C");

 // LIGHT
 if (lightLevel >= lightMin) {
    lightHappiness = 1;
 } else if (lightLevel < lightMin) {
    lightHappiness = -1;
 }

 // HAPPINESS
 happiness = happiness * oldMult + lightHappiness * newMult;

 // Make sure happiness stays within range
 if (happiness > 1) {
  happiness = 1;
 } else if (happiness < -1) {
  happiness = -1;
 }

 Serial.print("Happiness: ");
 Serial.print(happiness);
 Serial.println();

 if (happiness < -0.5) {
  newState = SAD;
 } else if (happiness > 0.5) {
  newState = HAPPY;
 } else {
  newState = NEUTRAL;
 }

 // CHANGE STATE IN LEDS
 if (newState != currentState) {
    currentState = newState;
    if (currentState == SAD) {
      digitalWrite(SAD, HIGH);
      digitalWrite(NEUTRAL, LOW);
      digitalWrite(HAPPY, LOW);
    } else if (currentState == NEUTRAL) {
      digitalWrite(SAD, LOW);
      digitalWrite(NEUTRAL, HIGH);
      digitalWrite(HAPPY, LOW);
    } else {
      digitalWrite(SAD, LOW);
      digitalWrite(NEUTRAL, LOW);
      digitalWrite(HAPPY, HIGH);
    }
 }
 
 delay(1000);
}
