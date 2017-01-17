#include "Arduino.h"

const int SWITCH_PIN = 2;
const int FIRST_LED_PIN = 4;
const int NO_LEDS = 6;
const int DOWN_THRESHOLD_MILLIS = 100;

int pressCount = 0;
long changeStartTime = 0;
int currState = 0;
int loopCount = -1;
boolean firstLoopPass = false;
long stateFlashTime = 0;
boolean state2FlashState = false;
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
	if(firstLoopPass == true && mod == 0)
		for(int i = 0; i < NO_LEDS; i++)
			digitalWrite((FIRST_LED_PIN + i), LOW);
	if(firstLoopPass == true && mod == 1)
		for(int i = 0; i < NO_LEDS; i++)
			digitalWrite((FIRST_LED_PIN + i), HIGH);
	if(mod == 2 && millis() - stateFlashTime > 1000 && state2FlashState == false)
	{
		for(int i = 0; i < NO_LEDS; i++)
			digitalWrite((FIRST_LED_PIN + i), HIGH);
		stateFlashTime = millis();
		state2FlashState = true;
	}
	if(mod == 2 && millis() - stateFlashTime > 1000 && state2FlashState == true)
	{
		for(int i = 0; i < NO_LEDS; i++)
			digitalWrite((FIRST_LED_PIN + i), LOW);
		stateFlashTime = millis();
		state2FlashState = false;
	}
	if(mod == 3 && firstLoopPass == true)
		stateFlashTime = millis();
	if(mod == 3)
	{
		float count = (millis() - stateFlashTime) / 1000; 
		for (int i = 0; i < NO_LEDS; i++)
		{
			float inverse = NO_LEDS-(i+1);
			float power = pow(2,inverse);
			int realPower = round(power);
			int num = count / realPower;
			if(count >= realPower)
				count -= realPower;
			if(num == 1)
				digitalWrite(FIRST_LED_PIN+i,HIGH);
			else
				digitalWrite(FIRST_LED_PIN+i,LOW);
		}
	}
	if(firstLoopPass = true && mod == 4)
		for(int i = 0; i < NO_LEDS; i++)
			digitalWrite((FIRST_LED_PIN + i), LOW);
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
	return init;
}
