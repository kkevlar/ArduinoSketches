/* SIMPLE MOTOR CONTROL
*
* This sketch uses a T120 Darlington transistor and a 10k Ohm potentiometer to control the speed of a DC motor.
*
* Analog Pin A0 reads the input from the potentiometer. When the potentiometer's wiper is at the negative leg (all
* the way turned down), all of the available 5V of potential are taken across the resistor. AO then reads a value of 0V.
* The motor is then sent a voltage of 0V -- and doesn't run. Conversely, when the potentiometer's wiper is at the positive
* leg, Pin A0 sees 1023 (5V). When divided by 4, this is 255, the value sent by PWM to the motor to run.
*
*/
int potPin = 0; // Analog in 0 connected to the potentiometer
int transistorPin = 9; // PWM Pin 9 connected to the base of the transistor
int potValue = 0; // value returned from the potentiometer
void setup() {
  Serial.begin(9600);
 pinMode(transistorPin, OUTPUT); // set the transistor pin as output:
}
void loop() {
  Serial.println(potValue);
 potValue = analogRead(potPin) / 4; // read the potentiometer, convert it to 0 - 255:
 if(potValue > 100)
 {
 digitalWrite(11, HIGH); // use that to control the motor:
 pinMode(13,OUTPUT);
 digitalWrite(13,HIGH);
 }
else
digitalWrite(11,LOW);
}
