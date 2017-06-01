/* KEVIN KELLAR - DUAL SERVO CONTROL
*
* Uses two ungrowling servos to do the sequence as described in the assignment.
*
*/
#include <Servo.h> // Loads the Arduino Servo Library.
Servo servo1; // Create a servo object named servo1.
void setup()
{
    servo1.attach(A5); //Servo1 on pin5
}
void loop()
{
    //servo1.write(0);  //Servos to central position
    delay(3000);       //Delay 3sec
    
    servo1.write(150); //Lservo all right
   
    delay(1000);       //Delay 1sec
  
    delay(2000);       //Wait 2secs
}

