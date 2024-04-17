#include "ultrasonic.h"

// Define trig and echo pins
const int trigPin = 9;
const int echoPin = 10;

// Create an instance of UltrasonicSensor class
UltrasonicSensor ultrasonicSensor(trigPin, echoPin);

void setup() {
  Serial.begin(9600); // Initialize serial communication  
  ultrasonicSensor.setCalibration(1.0, 0.9918);
}

void loop() {
  ultrasonicSensor.showcaseMeasureDistance();
  ultrasonicSensor.showcaseObjectDetection(30);
  ultrasonicSensor.showcaseSensorDataFiltering();
}