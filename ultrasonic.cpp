#include "ultrasonic.h"

UltrasonicSensor::UltrasonicSensor(int trig, int echo) : trigPin(trig), echoPin(echo) {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

float UltrasonicSensor::measureDistance(bool inCentimeters) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);

    if (inCentimeters) {
        // Calculate distance in centimeters
        return duration * 0.034 / 2;
    } else {
        // Calculate distance in inches
        return duration * 0.0133 / 2;
    }
}

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

    delay(1000); // Delay for stability
}