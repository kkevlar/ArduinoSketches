#include "Arduino.h"
const int SWITCH_PIN = 2;
const int DOWN_THRESHOLD_MILLIS = 100;
int pressCount = 0;

void setup()
{
  pinMode(SWITCH_PIN, INPUT);
}


int readSwitchState()
{
	int init = digitalRead(SWITCH_PIN);
	delay(10);
	int second = digitalRead(SWITCH_PIN);
	if (init == second)
	{
      return init;
	}
	return 0;
}
