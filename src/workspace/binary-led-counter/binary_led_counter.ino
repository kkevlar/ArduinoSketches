#include "Arduino.h"
const int SWITCH_PIN = 2;
const int FIRST_LED_PIN = 3;
const int NO_LEDS = 5;
const int DOWN_THRESHOLD_MILLIS = 100;
int pressCount = 0;
long changeStartTime = 0;
int currState = 0;
void setup()
{
  pinMode(SWITCH_PIN, INPUT);
}
void loop()
{
	Serial.begin(9600);
	long lastprint = millis();
	while(true)
	{
		switchPressIncrementSpotlight();
		if(millis() - lastprint > 1000)
		{
			Serial.println(pressCount);
			lastprint = millis();
		}
		delay(10);
	}
}
void switchPressIncrementSpotlight()
{
	long time = millis();
	int newState = readSwitchState();
	if (newState == currState)
		return;
	if(currState == 1 &&
			changeStartTime - time >
			DOWN_THRESHOLD_MILLIS)
		pressCount++;

	changeStartTime = time;
	currState = newState;
}

int readSwitchState()
{
	int init = digitalRead(SWITCH_PIN);
	//delay(10);
	//int second = digitalRead(SWITCH_PIN);
	//if (init == second)
      return init;
	//return 0;
}
