/* YourDuino.com Example Software Sketch
   Small Stepper Motor and Driver V1.3 11/30/2013
   http://arduino-direct.com/sunshop/index.php?l=product_detail&p=126
   Shows 4-step sequence, Then 1/2 turn and back different speeds
   terry@yourduino.com */

#include <Stepper.h>

//---( Number of steps per revolution of INTERNAL motor in 4-step mode )---
#define STEPS_PER_MOTOR_REVOLUTION 32

//---( Steps per OUTPUT SHAFT of gear reduction )---
#define STEPS_PER_OUTPUT_REVOLUTION 32 * 64  //2048

/*-----( Declare objects )-----*/
// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to

//The pin connections need to be 4 pins connected
// to Motor Driver In1, In2, In3, In4  and then the pins entered
// here in the sequence 1-3-2-4 for proper sequencing
Stepper small_stepper(STEPS_PER_MOTOR_REVOLUTION, 8, 10, 9, 11);

int Steps2Take;

void setup() {
  // Nothing  (Stepper Library sets pins as outputs)
}

void loop() {
  Steps2Take  =  STEPS_PER_OUTPUT_REVOLUTION / 2;  // Rotate CW 1/2 turn
  small_stepper.setSpeed(700);
  small_stepper.step(Steps2Take);
  delay(1000);

  Steps2Take  =  - STEPS_PER_OUTPUT_REVOLUTION / 2;  // Rotate CCW 1/2 turn
  small_stepper.setSpeed(700);  // 700 a good max speed??
  small_stepper.step(Steps2Take);
  delay(1000);

}
