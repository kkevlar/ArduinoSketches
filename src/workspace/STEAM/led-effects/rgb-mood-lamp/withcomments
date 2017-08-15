/* RGB MOOD LAMP
*
* This sketch controls three different LEDs (one red, one green, one blue) to produce a variety of
* different colors. These colors transition from one color to another. This sketch utilizes a
* couple of different types of variable arrays as well as both the random() and randomseed() procedures.
*/
float RGB1[3]; // A 3-element floating variable array to store RGB values
float RGB2[3]; // A 3-element floating variable array to store RGB values
float INC[3]; // A 3-element floating array to store increment values
int red, green, blue; // Three integer variables to store brightness levels to the LED's
int RedPin = 11; // Integer value for pin # for red LED
int GreenPin = 10; // Integer value for pin # for green LED
int BluePin = 9; // Integer value for pin # for blue LED
void setup() {
 Serial.begin(9600); // Begin serial communication with the Arduino
 randomSeed(analogRead(0)); // Reading a value from Pin #0; the random noise since nothing is
 // attached to this pin will provide a truly random starting
 // point for the random() procedure when it generates numbers.
 RGB1[0] = 0; // Have RGB1[0] start with a value of 0.
 RGB1[1] = 0; // Have RGB1[1] start with a value of 0.
 RGB1[2] = 0; // Have RGB1[2] start with a value of 0.
 RGB2[0] = random(256); // Have RGB2[0] end with a randomly generated value between 0 and 255.
 RGB2[1] = random(256); // Have RGB2[1] end with a randomly generated value between 0 and 255.
 RGB2[2] = random(256); // Have RGB2[2] end with a randomly generated value between 0 and 255.
}
void loop() {
 randomSeed(analogRead(0)); // Generating a new random number to start the random() procedure with
 for (int x=0; x<3; x++) { // For statement to increment values for all three LED's
 INC[x] = (RGB1[x] - RGB2[x]) / 256; // Determines the increment with which to step between the starting and ending
 } // values for each LED, spread over 256 equal increments.
 for (int x=0; x<256; x++) { // Start of FOR statement to increment each LED brightness.
 red = int(RGB1[0]); // Sets current value to red LED.
 green = int(RGB1[1]); // Sets current value to green LED.
 blue = int(RGB1[2]); // Sets current value to blue LED.
 analogWrite (RedPin, red); // Using PWM to send a brightness level to the red LED.
 analogWrite (GreenPin, green); // Using PWM to send a brightness level to the green LED.
 analogWrite (BluePin, blue); // Using PWM to send a brightness level to the blue LED.
  delay(100); // A pause before the change to brightness levels is made.
 RGB1[0] -= INC[0]; // Red LED brightness level is incremented by one step.
 RGB1[1] -= INC[1]; // Green LED brightness level is incremented by one step.
 RGB1[2] -= INC[2]; // Blue LED brightness level is incremented by one step.
 }
 for (int x=0; x<3; x++) { // For statement to reset the final brightness values for each LED.
 RGB2[x] = random(556)-300; // Resets the values, done by subtracting 300 to increase chance for primary color.
 RGB2[x] = constrain(RGB2[x], 0, 255); // Insures the values are not negative. Zeros will be generated more frequently.
 delay(1000); // A delay before starting the next mood phase.
 }
}
