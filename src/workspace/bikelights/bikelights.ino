#include "Arduino.h"

const int SWITCH_PIN = 2;
const int FIRST_LED_PIN = 4;
const int NO_LEDS = 6;
const int DOWN_THRESHOLD_MILLIS = 100;

int pressCount = 1;
long changeStartTime = 0;
int currState = 0;
int loopCount = -1;
boolean firstLoopPass = true;
void setup()
{
	pinMode(SWITCH_PIN, INPUT);
	for(int i = 0; i < NO_LEDS; i++)
		pinMode((FIRST_LED_PIN + i), OUTPUT);

}
void loop()
{
	switchPressIncrementSpotlight();
	if(loopCount != pressCount)
	{
		firstLoopPass = true;
    loopCount = pressCount;
	}
 int mod = pressCount % 5;
 if(firstLoopPass = true && mod == 0)
  for(int i = 0; i < NO_LEDS; i++)
    digitalWrite((FIRST_LED_PIN + i), LOW);
 if(firstLoopPass = true && mod == 1)
  for(int i = 0; i < NO_LEDS; i++)
    digitalWrite((FIRST_LED_PIN + i), HIGH);
   
  firstLoopPass = false;
}

void switchPressIncrementSpotlight()
{
  long time = millis();
  int newState = readSwitchState();
  if (newState == currState)
    return;
  if(currState == HIGH &&
      time - changeStartTime >
      DOWN_THRESHOLD_MILLIS)
    pressCount++;
   if(time - changeStartTime <
      DOWN_THRESHOLD_MILLIS)
      return;
  changeStartTime = time;
  currState = newState;
}


int readSwitchState()
{
	int init = digitalRead(SWITCH_PIN);
}
