/* SERVO CONTROL
*
* This program utilizes the Arduino Servo Library to control a single servo motor with a potentiometer.
*
*/
#include <Servo.h> // Include the Arduino servo library when running this program.
Servo servo1; // Create a servo object called "servo1".
void setup() {
 servo1.attach(5); // Attaches the servo object just identified to Pin 5.
}
void loop() {
 int angle = analogRead(0); // Read the pot value from Pin A0
 angle=map(angle, 0, 1023, 0, 180); // Map the values from 0 to 180 degrees
 servo1.write(angle); // Write the angle to the servo (must be between 0 and 180 degrees)
 delay(15); // Delay of 15ms to allow servo to reach position
}
