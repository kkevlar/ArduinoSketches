/* BIKELIGHTS - KEVIN KELLAR - January 17, 2017
 *  This program utilizes four, five, or six LEDs to act as
 *  bikelights with five different modes, which can be cycled
 *  through be pressing a pushbutton on the breadboard.
 *  
 *  The five states (0,1,2,3,4) are:
 *    -State 0: All the lights are off
 *    -State 1: All the lights are on
 *    -State 2: The lights alternate on and off each second
 *    -State 3: The lights count in binary, incrementing by one each half-second
 *    -State 4: The lights signal "SOS" in morse code
 *    
 *  The arduino should be set up with the following hardware:
 *    - Five LEDs should be hooked to digital pins 4-8
 *    - A pushbutton should toggle input to digital pin 2
 *    	> Using a pull-up or pull-down resistor circuit
 */
const int SWITCH_PIN = 12;
const int FIRST_LED_PIN = 6;
const int NO_LEDS = 5;
const int DOWN_THRESHOLD_MILLIS = 100;
int pressCount = 0;
long changeStartTime = 0;
int currState = 0; 
int loopCount = -1;
boolean fLP = false;
long stateStartTime = 0;
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
		fLP = true;  
		loopCount = pressCount;
	}
	int mod = pressCount % 5;
	if(fLP == true && mod == 0)
		for(int i = 0; i < NO_LEDS; i++)
			digitalWrite((FIRST_LED_PIN + i), HIGH);
	if(fLP == true && mod == 1)
		for(int i = 0; i < NO_LEDS; i++)
			digitalWrite((FIRST_LED_PIN + i), LOW);
	if((mod == 2 || mod == 3 || mod == 4) && 
			fLP == true)
	{
		stateStartTime = millis();
		state2FlashState = true; 
	}
	if(mod == 2 && millis() - stateStartTime > 1000 && 
			state2FlashState == false)
	{
		for(int i = 0; i < NO_LEDS; i++)
			digitalWrite((FIRST_LED_PIN + i), HIGH);
		stateStartTime = millis();
		state2FlashState = true;
	}
	if(mod == 2 && millis() - stateStartTime > 1000 && 
			state2FlashState == true)
	{
		for(int i = 0; i < NO_LEDS; i++)
			digitalWrite((FIRST_LED_PIN + i), LOW);
		stateStartTime = millis();
		state2FlashState = false;
	}
	if(mod == 3)
	{
		float count =
				(millis() - stateStartTime) / 500; 
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
	if(mod == 4)
	{
		float timePassed = (millis() - stateStartTime);
		float count = timePassed / 300;
		int intCount = (int) count;
		int sosMod = (intCount % 37)+1;
		if(sosMod <= 5 ||
				sosMod >= 33 ||
				(sosMod <= 13 && (sosMod % 2 == 1 || sosMod == 12)) ||
				sosMod == 17 ||
				sosMod == 21 ||
				(sosMod >= 25 && sosMod <= 27) ||
				((sosMod >= 27 && sosMod <= 33) && sosMod % 2 == 1) )
			for(int i = 0; i < NO_LEDS; i++)
				digitalWrite((FIRST_LED_PIN + i), LOW);
		else
			for(int i = 0; i < NO_LEDS; i++)
				digitalWrite((FIRST_LED_PIN + i), HIGH);

	}
	fLP = false; 
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
