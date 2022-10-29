#include <AFMotor.h>

AF_DCMotor motorL(4, MOTOR12_64KHZ); // LEFT
AF_DCMotor motorR(3, MOTOR12_64KHZ); // RIGHT

int distancecm = 0;
const int trigPin = 10;
const int echoPin = 9;

long duration;
int distance;

void setup() {
  Serial.begin(9600);
  
  motorL.setSpeed(200);
  motorR.setSpeed(200);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}


void loop() {
  distancecm = mdistance();
  if (distance < 10) {
    motorL.run(FORWARD);
    motorR.run(BACKWARD);
    delay(250);
  } else {
    motorL.run(FORWARD);
    motorR.run(FORWARD);
  }
}

int mdistance() {
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  distance = microsecondsToCentimeters(duration);

  Serial.print("Distance: ");
  Serial.println(distance);
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
