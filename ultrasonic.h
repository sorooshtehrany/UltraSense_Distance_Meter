#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include <Arduino.h>

class UltrasonicSensor {
private:
    int trigPin;
    int echoPin;

public:
    UltrasonicSensor(int trig, int echo);
    float measureDistance(bool inCentimeters = true);
	void showcaseMeasureDistance();
};

#endif