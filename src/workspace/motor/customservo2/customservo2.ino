/* DUAL SERVO CONTROL
*
* This sketch allows a person to control two servo motors from commands entered in the serial monitor
* and sent to the Arduino. Initially, the Arduino will reset and the servos will move to their
* central positions. To control the left motor, enter an L and then a number between 0 and 180 for
* the angle. To control the right motor, enter an R and then the angle. You can send individual
* commands at the same time by separating the commands with a space or comma.
*
*/
#include <Servo.h> // Loads the Arduino Servo Library.
char buffer[11]; // Create a character array to accept input from the Serial Monitor.
Servo servo1; // Create a servo object named servo1.
Servo servo2; // Create a second servo object named servo2.
void setup() {
 servo1.attach(5, 620, 2000);
servo2.attach(6, 650, 2000);
Serial.begin(9600); // Enable serial communication at 9600 baud.
 while(Serial.available()) // Reads data in only once it is available.
 Serial.read(); // Read the data from the serial monitor
 servo1.write(90); // Put servo1 at home position to start.
  servo2.write(90); // Put servo2 at home position to start.
 Serial.println("STARTING..."); // Display "STARTING..." in serial monitor to notify user they can now enter commands.
}
void loop() {
 if (Serial.available() > 0) { // Checks if data has been entered on the serial line.
 int index=0;
 delay(100); // Let the buffer fill with inputted info before proceeding. This is ...
 // ...necessary because the serial communication is much slower than...
 // ...the speed at which the Arduino processes information.
 int numChar = Serial.available(); // Assigns numChar an int value = to the number of characters in the string.
 if (numChar>10) { // Check to see if the inputted data exceeds the maximum of 10.
 numChar=10; // If greater than 10, set it to a length of 10.
 }
 while (numChar--) { // While loop checks the value of numChar and then subtracts 1 for next check.
 buffer[index++] = Serial.read(); // Fills the buffer array with characters from serial monitor, one element at a time.
 }
 buffer[index]='\0';
 splitString(buffer); // Run splitString function
 }
}
void splitString(char* data) { // The splitString function receives the buffer array, splits...
 // ... it into separate commands if more than one is entered, ...
 // ... and calls the setServo routine with the parameter stripped...
 // ... from the command string received over the serial line.
 // Here "char*" declares data as a variable that points to character data
 Serial.print("Data entered: "); // Prints "data entered: " on the serial monitor.
 Serial.println(data); // Prints the data on the serial monitor and then goes to a new line.
 char* parameter; // Establishes a new character pointer variable called parameter.
 parameter = strtok (data, " ,"); // String to token
 while (parameter != NULL) { // If we haven't reached the end of the string...
 setServo(parameter); // ...run the setServo function
 parameter = strtok (NULL, " ,"); // Sets parameter to the next part of the string up to the next space or comma...
 // ... we do this by passing it the NULL parameter.
 }
 while(Serial.available()) // If data is available,
 Serial.read(); // It is read so that it is cleared from the serial buffer and...
 // ...therefore ready for a new entry from the user.
}
void setServo(char* data) { // The setServo routine receives the smaller string sent from ...
 // ...the splitString function and checks if an L or R is entered...
 // ...and if so, moves either the left or right servo by the...
 // ...amount specified in the string.
 if ((data[0] == 'L') || (data[0] == 'l')) { // Checks to see if the first character indicates the left servo.
 int firstVal = strtol(data+1, NULL, 10); // Removes the angle in the string to a base-10 long integer.
 firstVal = constrain(firstVal,0,180); // Constrain values to within 0 and 180 degrees.
 servo1.write(firstVal); // Has the left servo turn to the specified angle.
 Serial.print("Servo1 is set to: "); // Confirmation message to the serial monitor that the move has been executed.
 Serial.println(firstVal); // Value is printed in the serial monitor, and the cursor moves to the next line.
 }
 if ((data[0] == 'R') || (data[0] == 'r')) { // Checks to see if the first character indicates the right servo
  int secondVal = strtol(data+1, NULL, 10); // Removes the angle in the string to a base-10 long integer.
 secondVal = constrain(secondVal,0,180); // Constrain values to within 0 and 180 degrees.
 servo2.write(secondVal); // Has the right servo turn to the specified angle.
 Serial.print("Servo2 is set to: "); // Confirmation message to the serial monitor that the move has been executed.
 Serial.println(secondVal); // Value is printed in the serial monitor, and the cursor moves to the next line.
 }
}
 

