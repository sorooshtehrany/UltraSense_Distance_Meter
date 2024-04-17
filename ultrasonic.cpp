#include "ultrasonic.h"

#define CM_TO_US_FACTOR 58
#define INCH_TO_US_FACTOR 148

// Constructor for the UltrasonicSensor class.
//
// @param trig The pin number for the trigger pin of the ultrasonic sensor.
// @param echo The pin number for the echo pin of the ultrasonic sensor.
//              Defaults:
//                - soundSpeedCalibration: 1.0 (no calibration)
//                - distanceCalibration: 1.0 (no calibration)
UltrasonicSensor::UltrasonicSensor(int trig, int echo) : trigPin(trig), echoPin(echo), soundSpeedCalibration(1.0), distanceCalibration(1.0) {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

// Measure distance using the ultrasonic sensor with optional calibration parameters.
//
// @param inCentimeters Indicates whether to return the distance in centimeters (true) or inches (false).
// @param soundSpeedCalibration Calibration factor for adjusting the speed of sound, considering environmental conditions.
//                              Default value: 1.0 (no calibration).
// @param distanceCalibration  Calibration factor for fine-tuning distance measurements.
//                              Default value: 1.0 (no calibration).
// @return The measured distance in centimeters or inches, based on the 'inCentimeters' parameter.
float UltrasonicSensor::measureDistance(bool inCentimeters = true) {
    // Send trigger signal
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Measure echo duration with a timeout slightly longer than 36ms
    long duration = pulseIn(echoPin, HIGH, 40 * 1000); // 40ms timeout

    // Check if no echo was received
    if (duration == 0) {
        return -1.0; // Return a special value to indicate no detection
    }
	
    // Calculate distance based on duration and calibration factors
    if (inCentimeters) {
        // Calculate distance in centimeters with calibration factors
        return (duration / CM_TO_US_FACTOR) * (soundSpeedCalibration * distanceCalibration);
    }
    else {
        // Calculate distance in inches with calibration factors        
        return (duration / INCH_TO_US_FACTOR) * (soundSpeedCalibration * distanceCalibration);
    }
}

// Checks if an object is detected within a certain threshold distance
// Parameters:
// - thresholdDistance: The distance threshold for object detection
// Returns: True if an object is detected, otherwise false
bool UltrasonicSensor::isObjectDetected(float thresholdDistance) {
    // Measure distance
    float distance = measureDistance();
    // Check if distance is less than or equal to threshold
    return distance <= thresholdDistance;
}

// Filters sensor data by averaging distances measured within a 100ms window
// Returns: The average distance measured within the window
float UltrasonicSensor::filterSensorData() {
    unsigned long startTime = millis();
    unsigned long endTime = startTime + 100; // 100ms window

    float sum = 0;
    int count = 0;

    // Measure distance repeatedly and calculate the sum
    while (millis() < endTime) {
        sum += measureDistance();
        count++;
    }

    // Calculate the average distance
    float averageDistance = sum / count;
    return averageDistance;
}

// Set calibration values for the ultrasonic sensor.
//
// @param soundSpeed The calibration factor for adjusting the speed of sound, considering environmental conditions.
// @param distance The calibration factor for fine-tuning distance measurements.
void UltrasonicSensor::setCalibration(float soundSpeed, float distance) {
    soundSpeedCalibration = soundSpeed;
    distanceCalibration = distance;
}

#ifdef SHOWCASE_METHOD

// Showcases the measurement of distance in centimeters and inches
void UltrasonicSensor::showcaseMeasureDistance() {
    // Measure distance in centimeters (default)
    float distance_cm = measureDistance();

    // Measure distance in inches
    float distance_in = measureDistance(false);

    // Print the distances to serial monitor
    Serial.print("Distance in centimeters: ");
    Serial.print(distance_cm);
    Serial.println(" cm");

    Serial.print("Distance in inches: ");
    Serial.print(distance_in);
    Serial.println(" inches");
    Serial.println("-----------------------------------");
    delay(1000); // Delay for stability
}

// Showcases object detection based on a given threshold distance
void UltrasonicSensor::showcaseObjectDetection(float thresholdDistance) {
    bool objectDetected = isObjectDetected(thresholdDistance);

    // Print object detection result to serial monitor
    Serial.print("Object detected: ");
    Serial.println(objectDetected ? "True" : "False");
    Serial.println("-----------------------------------");

    delay(1000); // Delay for stability
}

// Showcases sensor data filtering by printing the average distance within a 100ms window
void UltrasonicSensor::showcaseSensorDataFiltering() {
    // Get filtered sensor data
    float filteredData = filterSensorData();

    // Print filtered sensor data to serial monitor
    Serial.print("Filtered sensor data: ");
    Serial.print(filteredData);
    Serial.println(" cm");
    Serial.println("-----------------------------------");
    delay(1000); // Delay for stability
}
#endif