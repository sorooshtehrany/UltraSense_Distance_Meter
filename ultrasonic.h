#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include <Arduino.h>

#define SHOWCASE_METHOD

class UltrasonicSensor {
private:
    int trigPin;
    int echoPin;

public:
    UltrasonicSensor(int trig, int echo);
    float measureDistance(bool inCentimeters = true);
	bool isObjectDetected(float thresholdDistance);

#ifdef SHOWCASE_METHOD
	  void showcaseMeasureDistance();
	  void showcaseObjectDetection(float thresholdDistance);
#endif
};

#endif