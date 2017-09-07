/* PULSATING LAMP
*
* This sketch teaches the ins and outs of controlling the brightness of an LED. In this sketch
* the sine function is used to make values that then are sent to a digital pin using the analogWrite()
* statement and the pins ability to use pulse-width-modulation (PWM).
*/
int ledPin = 11; // Variable for the LED pin #
float sinVal; // A floating variable to store the sine function computation
int ledVal; // In integer value that can be sent to the LED pin
void setup() {
 pinMode(ledPin, OUTPUT); // Sets the LED pin to OUTPUT
}
void loop() {
 for (int x=0; x<180; x++) {
 sinVal = (sin(x*(3.1412/180))); // converts degrees to radians
 ledVal = int(sinVal*255); // changes the value from the sign function to an integer value
 analogWrite(ledPin, ledVal); // write the value to the LED to adjust its brightness
 delay(25);
 }
}

