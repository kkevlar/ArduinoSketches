/* PIEZO SOUNDER ALARM
*
* This sketch utilizes the tone() procedure and a piezo element to make an alarm similar to a car
* alarm or a police car siren. The delay is placed as a separate line instead of incorporated within
* the tone() procedure because the loop will be executed faster than the 2 ms. Therefore, if it were
* within the tone() procedure, it wouldn't really sound that tone.
*
*/
float sinVal; // Set up a floating variable for what the sine function returnes.
int toneVal; // Set up an integer variable to be used in the tone() procedure.
void setup() {
 pinMode(6, OUTPUT); // Set the piezo pin to an OUTPUT.
}
void loop() {
 for (int x=0; x<180; x++) { // Go from 0 to 179 to avoid negative values from the sine function.
 sinVal = (sin(x*(3.1412/180))); // Convert degrees to radians then obtain sin value.
 toneVal = +(int(sinVal*3000)); // Generate an appropriate frequency range from the sin value.
 tone(6, toneVal); // Send the determined value to the piezo to generate the sound.
 delay(6); // Delay to insure the sine wave rises and falls as we want.
 }
}
