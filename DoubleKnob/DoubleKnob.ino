/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo

int potpin = A0;  // analog pin used to connect the potentiometer
int potpin2 = A1;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
int val2;    // variable to read the value from the analog pin

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(10);
}

void loop() {
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 180, 0);     // scale it to use it with the servo (value between 0 and 180)

  val2 = analogRead(potpin2);            // reads the value of the potentiometer (value between 0 and 1023)
  val2 = map(val2, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)

  myservo.write(val);                  // sets the servo position according to the scaled value
  myservo2.write(val2);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
}
