#include "pitches.h";
#include <Servo.h> // Loads the Arduino Servo Library.
Servo servo1; // Create a servo object named servo1.
const int PIN_PHOTO = A0;
const int PIN_BUTTON = 2;

int buttonState = -1;
long buttonStateChangeTime;
long doorChangeTime = - 10000;
int doorState = 0;

void setup()
{
    pinMode(PIN_PHOTO, INPUT);
    pinMode(PIN_BUTTON, INPUT);

    servo1.attach(5); //Servo1 on pin5
    servo1.write(150);
    dingDong();
}

void loop()
{

    testInputs();
}
void testInputs()
{
}
void testPhotoCell()
{
}
void testButton()
{
    int state = 0;
    if (digitalRead(PIN_BUTTON) == HIGH)
        state = 1;

    if(buttonState == 1 && state == 1 && millis() - buttonStateChangeTime > 200 && millis() - doorChangeTime > 1000)
    {
      if(doorState == 0)
      {
      dingDong();
      doorOpen();
      doorState = 1;
      }
      else
      {
      doorClosed();
      doorState = 0;
      }
      
      doorChangeTime = millis();
      
    }
    if (buttonState != state) {
        buttonState = state;
        buttonStateChangeTime = millis();
    }
}

void doorOpen()
{
  servo1.write(150-90);
}

void doorClosed()
{
  
}
void dingDong()
{
    tone(12, NOTE_DS5, 750);
    delay(750);
    tone(12, NOTE_B4, 750);
    delay(750);
}

