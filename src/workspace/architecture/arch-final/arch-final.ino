#include "pitches.h";
#include <Servo.h> // Loads the Arduino Servo Library.
Servo servo1; // Create a servo object named servo1.
const int PIN_PHOTO = A0;
const int PIN_BUTTON = 2;
const int PIN_NIGHTLIGHT = 8;

int buttonState = -1;
long buttonStateChangeTime;
long doorChangeTime = - 10000;
int doorState = 0;

void setup()
{
    pinMode(PIN_PHOTO, INPUT);
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_NIGHTLIGHT, OUTPUT);
    Serial.begin(9600);
    servo1.attach(5); //Servo1 on pin5
    doorClosed();
    dingDong();
}

void loop()
{

    testInputs();
    Serial.println(analogRead(A0));
    delay(25);
}
void testInputs()
{
  testButton();
  testPhotoCell();
}
void testPhotoCell()
{
  if(analogRead(PIN_PHOTO) > 900)
    digitalWrite(8,HIGH);
   else
   digitalWrite(8,LOW);
}
void testButton()
{
    int state = 0;
    if (digitalRead(PIN_BUTTON) == HIGH)
        state = 1;

    if(buttonState == 1 && state == 1 && millis() - buttonStateChangeTime > 100 && millis() - doorChangeTime > 400)
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
   servo1.write(150);
}
void dingDong()
{
    tone(12, NOTE_DS5, 750);
    delay(750);
    tone(12, NOTE_B4, 750);
    delay(750);
}

