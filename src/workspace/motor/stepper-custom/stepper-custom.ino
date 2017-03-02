/* BASIC STEPPER CONTROL
*
* This sketch demonstrates the basic control of a stepper motor using the L293D motor
* driver IC. While the stepper motors in use have 32 steps / one revolution, they are also
* geared 1/16, meaning that when the motor goes around once, the output shaft only goes around 1/16th
* of a rotation. Rotations must be multiplied by 16 when one wishes to
* specify the rotation of the actual output shaft.
*
*/
#include <Stepper.h> // Includes the stepper.h library for use.
#define STEPS 512 // Steps value tells Arduino how many steps / one revolution.
Stepper stepper(STEPS, 4, 5, 6, 7); // Create a stepper object on pins 4, 5, 6 and 7
void setup() {
}
void loop() {
 stepper.setSpeed(60); // Set the stepper speed to 60 RPM.
 stepper.step(STEPS*3); // Have the motor turn through 512 steps (one revolution).
  delay(1000);
  stepper.setSpeed(30);
  stepper.step(STEPS * -.75);
  delay(2000);
}
