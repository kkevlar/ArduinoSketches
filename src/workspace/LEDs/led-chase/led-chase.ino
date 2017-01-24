/* LED CHASE EFFECT
* This sketch takes 10 LED's and lights them such that the lit LED appears to
* move along the line, then bounce back to the start. This program utilizes arrays.
*/
byte ledPin[] = {2,3,4, 5, 6, 7, 8, 9, 10, 11}; // Create array for LED pins
int ledDelay = 30; // The variable that sets the rate of the chasing effect.
int direction = 1; // The variable controlling the direction of the sequence of LEDs, initially = 1.
int currentLED = 0; // The variable that governs which LED is on at any given moment, initially = 0.
unsigned long changeTime; // The variable used to check if enough time has passed to change LED's.
void setup() {
  
  for (int x=0; x<10; x++) { // sets all pins to OUTPUT
 pinMode(ledPin[x], OUTPUT);
 }
 changeTime = millis(); // Initializes the variable to the time that has passed
}
void loop() {
  ledDelay = analogRead(2);
 if ((millis() - changeTime) > ledDelay) { // if it has been ledDelay ms since last change
 changeLED(); // called the procedure we define below called "changeLED"
 changeTime = millis(); // alters the value of changeTime to the current elapsed time -- a reset
 }
}
void changeLED() { // This is a separate procedure that is called above in the main section.
 for (int x=0; x<10; x++) { // turn off all LED's
 if(x != currentLED)
 digitalWrite(ledPin[x], LOW);
 }
 digitalWrite(ledPin[currentLED], HIGH); // turn on the current LED
 currentLED += direction; // increment by the direction value
 if (currentLED == 9) {direction = -1;} // this changes the direction if we reach the last LED
 if (currentLED == 0) {direction = 1;} // this changes the direction if we reach the last LED
}


