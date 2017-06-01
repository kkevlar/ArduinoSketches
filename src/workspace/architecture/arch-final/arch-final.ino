#include "pitches.h";
#include <Servo.h> // Loads the Arduino Servo Library.
Servo servo1; // Create a servo object named servo1.

void setup()
{


  servo1.attach(5); //Servo1 on pin5
 servo1.write(150);
 dingDong();
}

void loop()
{
  

   

    doPhotocellThings();

   

 
}
void doPhotocellThings()
{
  
}
void dingDong()
{
   tone(12,NOTE_DS5,750);
  delay(750);
  tone(12,NOTE_B4,750);
  delay(750);
}



