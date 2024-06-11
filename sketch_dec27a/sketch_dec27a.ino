// Pin configuration
const int leftMotorPin1 = 2;
const int leftMotorPin2 = 4;
const int rightMotorPin1 = 7;
const int rightMotorPin2 = 8;
const int leftSensorPin = A0; // Analog input for left infrared sensor (HW201)
const int rightSensorPin = A1; // Analog input for right infrared sensor (HW201)
const int trigPin = A2; // Trigger pin for HC-SR04
const int echoPin = A3; // Echo pin for HC-SR04

void setup() {
  // Motor control pins
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  // Sensor pins
  pinMode(leftSensorPin, INPUT);
  pinMode(rightSensorPin, INPUT);

  // HC-SR04 pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  // Read sensor values
  int leftSensorValue = analogRead(leftSensorPin);
  int rightSensorValue = analogRead(rightSensorPin);

  // Read distance from HC-SR04
  int distance = getDistance();

  // Line following logic
  if (leftSensorValue < 500 && rightSensorValue > 500) {
    // Turn left
    turnLeft();
  } else if (leftSensorValue > 500 && rightSensorValue < 500) {
    // Turn right
    turnRight();
  } else {
    // Move forward
    moveForward();
  }

  // Obstacle avoidance logic
  if (distance < 10) {
    // Obstacle detected, stop and turn around
    stopRobot();
    delay(1000); // Adjust delay as needed
    turnAround();
  }
}

void moveForward() {
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
}

void turnLeft() {
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
}

void turnRight() {
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
}

void stopRobot() {
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, LOW);
}

void turnAround() {
  // Stop and turn around
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, LOW);

  // Turn around (e.g., reverse one motor)
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);

  delay(1000); // Adjust delay for turning around
  stopRobot();
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  return distance;
}
