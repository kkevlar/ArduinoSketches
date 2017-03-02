/* USING A L293D MOTOR DRIVER IC
*
* This sketch uses an L293D Motor Driver IC to control a DC motor. A slide switch allows the user to control the direction
* of the motor's spin. Speed can be adjusted by adjusting the potentiometer. To change the direction of the motor, first
* set the speed to minimum with the potentiometer, then flick the switch.
*/
#define switchPin 2 // defines switch input as Pin 2 on the Arduino
#define motorPin1 3 // defines L293D Input 1 as Pin 3 on the Arduino
#define motorPin2 4 // defines L293D Input 2 as Pin 4 on the Arduino
#define speedPin 9 // defines L293D enable pin 1 as Pin 9 on the Arduino
#define potPin 0 // defines potentiometer on analog Pin 0
int Mspeed = 0; // creates an integer variable to hold the current speed value
void setup() {
 pinMode(switchPin, INPUT); // set switch pin as INPUT
 pinMode(motorPin1, OUTPUT); // set motorPin1 (which is pin 3) as OUTPUT
 pinMode(motorPin2, OUTPUT); // set motorPin1 (which is pin 4) as OUTPUT
 pinMode(speedPin, OUTPUT); // set motorPin1 (which is pin 3) as OUTPUT
}
void loop() {
 Mspeed = analogRead(potPin)/4; // read the speed value from the potentiometer; reading converted to 0-255 for
//analogWrite output
 analogWrite (speedPin, Mspeed); // write speed to Enable 1 pin
 if (digitalRead(switchPin)==HIGHjk) { // If the switch is HIGH, rotate motor clockwise
 digitalWrite(motorPin1, LOW); // set Input 1 of the L293D low
 digitalWrite(motorPin2, HIGH); // set Input 2 of the L293D high
 }
 else { // if the switch is LOW, rotate motor anti-clockwise
 digitalWrite(motorPin1, HIGH); // set Input 1 of the L293D low
 digitalWrite(motorPin2, LOW); // set Input 2 of the L293D high
 }
}
