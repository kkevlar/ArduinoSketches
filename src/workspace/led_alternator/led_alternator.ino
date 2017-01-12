#include "Arduino.h"

const int SWITCH_PIN = 2;
const int FIRST_LED_PIN = 5;
const int NO_LEDS = 2;
const int DOWN_THRESHOLD_MILLIS = 25;

int pressCount = 0;
long changeStartTime = 0;
int currState = 0;
int loopCount = 2;
void setup()
{
	//Serial.begin(9600);
	pinMode(SWITCH_PIN, INPUT);
	for(int i = 0; i < NO_LEDS; i++)
		pinMode((FIRST_LED_PIN + i), OUTPUT);

}
void loop()
{
	/*
	digitalWrite(FIRST_LED_PIN,digitalRead(SWITCH_PIN));
	*/
	switchPressIncrementSpotlight();
	if(loopCount != pressCount)
	{
		int state1 = LOW;
		int state2 = LOW;
		if(pressCount % 2 == 0)
			state1 = HIGH;
		else
			state2 = HIGH;

		digitalWrite(FIRST_LED_PIN, state1);
		digitalWrite((FIRST_LED_PIN+1), state2);
		loopCount = pressCount;
	}
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
	changeStartTime = time;
	currState = newState;
}

int readSwitchState()
{
	int init = digitalRead(SWITCH_PIN);
	//delay(10);
	//int second = digitalRead(SWITCH_PIN);
	//if (init == second)
	//if(init == HIGH)
		//Serial.println("gotem");
      return init;
	//return 0;
}
