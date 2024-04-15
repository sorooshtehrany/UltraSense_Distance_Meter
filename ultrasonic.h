#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include <Arduino.h>

#define SHOWCASE_METHOD

class UltrasonicSensor {
private:
  int trigPin;
  int echoPin;
  float soundSpeedCalibration;
  float distanceCalibration;

public:
  UltrasonicSensor(int trig, int echo);
  float UltrasonicSensor::measureDistance(bool inCentimeters = true);
  bool isObjectDetected(float thresholdDistance);
  float filterSensorData();
  void setCalibration(float soundSpeed, float distance);

#ifdef SHOWCASE_METHOD
  void showcaseMeasureDistance();
  void showcaseObjectDetection(float thresholdDistance);
  void showcaseSensorDataFiltering();
#endif
};

#endif