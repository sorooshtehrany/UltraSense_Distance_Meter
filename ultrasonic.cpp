#include "ultrasonic.h"

// Constructor: Initializes the UltrasonicSensor object with trig and echo pins
UltrasonicSensor::UltrasonicSensor(int trig, int echo) : trigPin(trig), echoPin(echo) {
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
float UltrasonicSensor::measureDistance(bool inCentimeters = true, float soundSpeedCalibration = 1.0, float distanceCalibration = 1.0){
    // Send trigger signal
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Measure echo duration
    long duration = pulseIn(echoPin, HIGH);

    // Calculate distance based on duration and calibration factors
    if (inCentimeters) {
        // Calculate distance in centimeters with calibration factors
        return (duration * 0.034 * soundSpeedCalibration) / (2 * distanceCalibration);
    } else {
        // Calculate distance in inches with calibration factors
        return (duration * 0.0133 * soundSpeedCalibration) / (2 * distanceCalibration);
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
        sum += measureDistance(1.0, 1.0);
        count++;
    }

    // Calculate the average distance
    float averageDistance = sum / count;
    return averageDistance;
}

#ifdef SHOWCASE_METHOD

// Showcases the measurement of distance in centimeters and inches
void UltrasonicSensor::showcaseMeasureDistance() {
    // Measure distance in centimeters (default)
    float distance_cm = measureDistance(1.0,1.0);

    // Measure distance in inches
    float distance_in = measureDistance(false, 1.0, 1.0);

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