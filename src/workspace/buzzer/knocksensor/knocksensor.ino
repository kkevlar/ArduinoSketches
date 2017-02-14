/* PIEZO KNOCK SENSOR
*
* This sketch utilizes a piezo element to sense a force or strain due to an impact or a vibration.
* In this case, the strain on the piezo gets converted to an electrical potential difference that
* the Arduino can sense as an input. The LED will flash twice quickly as a visual indication that
* the program has started.
*
* Here, we have the Arduino do two things when an impact is sensed. First, the program will
* light an LED and have it then fade off. At the same time, the program prints the sensed input
* voltage read by the pin to the Serial Monitor. The LED will dim until it either goes off completely
* or returns to full brightness when another knock is sensed.
*
* The Serial Monitor portion of this sketch is helpful for troubleshooting in a variety of ways.
* It helps know what to set the threshold level to. If the threshold is too low, the LED will come on
* too often. Conversely if it is too high, the LED won't come on at all.
*
*/
int ledPin = 9; // LED on Digital Pin 9.
int piezoPin = A0; // Piezo on Analog Pin 5.
int threshold = 9; // The sensor value to reach before activation.
int sensorValue = 0; // A variable to store the value read from the sensor, initialized at 0.
float ledValue = 0; // The brightness of the LED.
void setup()
{
    Serial.begin(9600); // Start serial communication so the Serial Monitor can be used.
    pinMode(ledPin, OUTPUT); // Set the ledPin to an OUTPUT
    // Flash the LED twice to show the program has started
    digitalWrite(ledPin, HIGH);
    delay(150);
    digitalWrite(ledPin, LOW);
    delay(150);
    digitalWrite(ledPin, HIGH);
    delay(150);
    digitalWrite(ledPin, LOW);
    delay(150);
}
void loop()
{
    sensorValue = analogRead(piezoPin); // Read the value from the sensor
    Serial.println(sensorValue); // Print the actual voltage being measured at Pin A0 in the Serial Monitor.
    Serial.println(" "); // Print a blank line to separate readings in the Serial Monitor.
    if (sensorValue >= threshold) { // If knock detected set brightness to max brightness for PWM on pin
        ledValue = 255;
    }
    analogWrite(ledPin, int(ledValue)); // Write brightness value to LED
    ledValue -= 2; // Dim the LED slowly; a float variable is used here for a decimal increment
    if (ledValue <= 0) { // Make sure value does not go below zero
        ledValue = 0;
    }
}
