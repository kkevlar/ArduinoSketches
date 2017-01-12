#include "Arduino.h"

const int SWITCH_PIN = 2;
const int FIRST_LED_PIN = 5;
const int NO_LEDS = 5;
const int DOWN_THRESHOLD_MILLIS = 25;

int pressCount = 0;
long changeStartTime = 0;
int currState = 0;

void setup()
{
  pinMode(SWITCH_PIN, INPUT);
  pinMode(FIRST_LED_PIN, OUTPUT);
}
void loop()
{
	/*
	digitalWrite(FIRST_LED_PIN,digitalRead(SWITCH_PIN));
	*/
	Serial.begin(9600);
	switchPressIncrementSpotlight();

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
