/*
*    Sweep area with servo-mounted
*    4-pin ultrasonic sensor and
*    send data to serial (to draw a graph)
*/

#include <Servo.h>

Servo servo;
int pos = 0;          //servo position
int degs = 1;         //number of degrees to move per cycle
int dir = 1;          //direction (1 or -1)

int vccPin = 2;       //attach pin 2 to VCC
int pingPin = 3;      //attach pin 3 to Trig
int echoPin = 4;      //attach pin 4 to Echo
int gndPin = 5;       //attach pin 5 to GND

void setup() {
  pinMode(vccPin, OUTPUT);
  pinMode(gndPin, OUTPUT);
  
  servo.attach(9);
  
  Serial.begin(9600);
}

void loop()
{
  long duration, cm;
  
  pos = pos + (degs * dir);
  servo.write(pos);
  if (pos == 180 || pos == 0) {
    dir *= -1;
  }
  
  digitalWrite(vccPin, HIGH);
 
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);

  Serial.print(pos);
  Serial.print(" ");
  Serial.println(cm);
  
  delay(100);
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
