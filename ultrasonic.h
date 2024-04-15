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
  float UltrasonicSensor::measureDistance(bool inCentimeters = true, float soundSpeedCalibration = 1.0, float distanceCalibration = 1.0);
	bool isObjectDetected(float thresholdDistance);
	float filterSensorData();

#ifdef SHOWCASE_METHOD
	  void showcaseMeasureDistance();
	  void showcaseObjectDetection(float thresholdDistance);
	  void showcaseSensorDataFiltering();
#endif
};

#endif