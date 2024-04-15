#include "ultrasonic.h" // Assuming you save the class in a separate file named UltrasonicSensor.h

// Define trig and echo pins
const int trigPin = 9;
const int echoPin = 10;

// Create an instance of UltrasonicSensor class
UltrasonicSensor ultrasonicSensor(trigPin, echoPin);

void setup() {
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  ultrasonicSensor.showcaseMeasureDistance();
  ultrasonicSensor.showcaseObjectDetection(30);
}