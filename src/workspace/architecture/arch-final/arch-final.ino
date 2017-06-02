/*
 * GROUP 3 - FRAMED AND WIRED CODE
 * KEVIN K
 * LAUREN H
 * SARAH C
 * CHARLIE B
 * KEEGAN P
 * 
 * TURNS ON AN OUTDOOR LIGHT IF IT IS DARK (sensed by a photocell)
 * OPENS THE DOOR AND PLAYS A DOORBELL NOISE IF BUTTON IS PRESSED
 * 
 */



//Includes the list of pitches for easier piazzo programming
#include "pitches.h";
//Includes the servo library
#include <Servo.h> 
//Servo object declaration
Servo servo1; 

//Pin constant declarations
const int PIN_PHOTO = A0;
const int PIN_BUTTON = 2;
const int PIN_NIGHTLIGHT = 8;
const int PIN_SERVO = 5;
const int PIN_DINGDONG = 12;

//Global variable declarations
//Last detected state of the button (0=up, 1=down)
int buttonState = -1;
//Time of last detected state change of button
long buttonStateChangeTime;
//Time that the door state was last changed
long doorChangeTime = - 10000;
//Current state of the door (0=up, 1=down)
int doorState = 0;

void setup()
{
    //Sets the pins to appropriate I/O settings
    pinMode(PIN_PHOTO, INPUT);
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_NIGHTLIGHT, OUTPUT);

    //Sets up servo on the appropriate pin
    servo1.attach(PIN_SERVO);
    //closes the door
    doorClosed();
    //tests the doorbell noise
    dingDong();
}
void loop()
{
    testInputs();
    delay(5);
}
void testInputs()
{
  testButton();
  testPhotoCell();
}
void testPhotoCell()
{
  //Reads the photopin and turn on the light if it is darker than the threshold
  if(analogRead(PIN_PHOTO) > 900)
    digitalWrite(8,HIGH);
   else
   digitalWrite(8,LOW);
}
void testButton()
{
    //Reads the current state from the input pin
    int state = 0;
    if (digitalRead(PIN_BUTTON) == HIGH)
        state = 1;

    //If......
    //The button had previously been down AND
    if(buttonState == 1 && 
    //The button is currently down AND
    state == 1 &&
    //The button has been down for 100ms AND
    millis() - buttonStateChangeTime > 100 && 
    //The door hasn't been moved for 400ms
    millis() - doorChangeTime > 400)
    {

      //If door currently closed then...
      if(doorState == 0)
      {
          //Ring doorbell
          dingDong();
          //Open the door
          doorOpen();
          //Remeber the current state of the door
          doorState = 1;
      }
      //If the door was open then...
      else
      {
          //Close the door
          doorClosed();
          //Remember that it is now closed
          doorState = 0;
      }

      //Store the time that door state was changed
      doorChangeTime = millis();
    }
    //If button state changed
    if (buttonState != state) {
        //Remember the new state
        buttonState = state;
        //Store the time that state changed
        buttonStateChangeTime = millis();
    }
}

void doorOpen()
{
  //Move the servo 90 degrees from closed
  servo1.write(150-90);
}

void doorClosed()
{
   //Move the servo to the closed position
   servo1.write(150);
}
void dingDong()
{
    //Play the first note on the piazzo
    tone(PIN_DINGDONG, NOTE_DS5, 750);
    delay(750);
    //Play the second note on the piazzo
    tone(PIN_DINGDONG, NOTE_B4, 750);
    delay(750);
}

