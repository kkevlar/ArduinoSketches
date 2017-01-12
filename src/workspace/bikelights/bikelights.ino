#include "Arduino.h"

const int SWITCH_PIN = 2;
const int FIRST_LED_PIN = 5;
const int NO_LEDS = 5;
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
		if(pressCount % 5 == 1)
			for(int i = 0; i < NO_LEDS; i++)
					digitalWrite((FIRST_LED_PIN + i), LOW);
		if (pressCount % 5 == 0)
			for(int i = 0; i < NO_LEDS; i++)
								digitalWrite((FIRST_LED_PIN + i), HIGH);
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
