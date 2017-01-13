#include "Arduino.h"

const int SWITCH_PIN = 2;
const int FIRST_LED_PIN = 4;
const int NO_LEDS = 6;
const int DOWN_THRESHOLD_MILLIS = 100;

int pressCount = 1;
long changeStartTime = 0;
int currState = 0;
int loopCount = -1;
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
		int count = pressCount;
   //Serial.print(count);
  // Serial.println(":");
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
       // Serial.print(realPower);
        //Serial.print("  ");
       // Serial.println(num);
		}
   //Serial.println();
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
   if(time - changeStartTime <
      DOWN_THRESHOLD_MILLIS)
      return;
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
