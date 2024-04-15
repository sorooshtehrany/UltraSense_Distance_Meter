const int trigPin = 9; // Trig pin of SRF04 connected to digital pin 9
const int echoPin = 10; // Echo pin of SRF04 connected to digital pin 10
long duration; // Variable to store the duration of sound wave travel
int distance; // Variable to store the distance calculated from duration

void setup() {
  pinMode(trigPin, OUTPUT); // Set trigPin as output
  pinMode(echoPin, INPUT); // Set echoPin as input
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Send a 10 microsecond pulse to trigger the sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the duration of the echo signal
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance in centimeters
  distance = duration * 0.034 / 2;
  
  // Print the distance to serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(100); // Delay for stability
}