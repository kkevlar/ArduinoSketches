/* KEVIN KELLAR - DUAL SERVO CONTROL
*
* Uses two ungrowling servos to do the sequence as described in the assignment.
*
*/
#include <Servo.h> // Loads the Arduino Servo Library.
Servo servo1; // Create a servo object named servo1.
Servo servo2; // Create a second servo object named servo2.
void setup()
{
    servo1.attach(5, 620, 2000); //Servo1 on pin5
    servo2.attach(6, 650, 2000); //Servo2 on pin6
}
void loop()
{
    servo1.write(90);  //Servos to central position
    servo2.write(90);
    delay(3000);       //Delay 3sec
    servo1.write(0);   //Left servo all way left
    delay(1000);       //Delay a sec
    servo1.write(180); //Lservo all right
    delay(2000);       //Del 2sec
    servo2.write(0);   //RServo all left
    delay(400);        //Delay to let the Rservo get to left
    servo2.write(180); //Rservo all right
    delay(1000);       //Delay 1sec
    servo1.write(0);   //Both to right pos
    servo2.write(0);
    delay(500);        //Delay while they get there
    servo1.write(180); //Both all right
    servo2.write(180);
    delay(2000);       //Wait 2secs
}

