/* TRAFFIC_LIGHT - KEVIN KELLAR - January 19, 2017
 *  
 */

const int DOWN_THRESHOLD_MILLIS = 100;  //Sets how long the pushbutton needs to be down
const int SWITCH_PIN = 12;               //Sets the input pin
const int TL_RED_PIN = 10;
const int TL_YLW_PIN = 9;
const int TL_GRN_PIN = 8;
const int PS_RED_PIN = 7;
const int PS_GRN_PIN = 6;

const int DUR_INIT_STATE = 5000;
const int DUR_YELLOW_STATE = 5000;
const int DUR_RED_STATE = 2000;
const int DUR_PED_STATE = 5000;
const int DUR_FLASH_STATE = 5000;
const int DUR_FINAL_STATE = 2000;

const byte STATE_GRN = 5;
const byte STATE_YLW = 1;
const byte STATE_RED = 2;
const byte STATE_PED = 3;
const byte STATE_FLASH = 4;

const int DURATIONS[] = {DUR_INIT_STATE,
		DUR_YELLOW_STATE,
		DUR_RED_STATE,
		DUR_PED_STATE,
		DUR_FLASH_STATE,
		DUR_FINAL_STATE};
const byte STATES[] = {STATE_YLW,
		STATE_RED,
		STATE_PED,
		STATE_FLASH,
		STATE_RED,
		STATE_GRN};


long changeStartTime = 0;               //Time since last button state change
int currState = 0;                      //Current state of the pushbutton
boolean button_pressed = false;
boolean startSequence = false;                   
long startTime = 0;
byte lightsState = 0;
boolean isFlashStateLit = false;

void setup()
{
	pinMode(SWITCH_PIN, INPUT_PULLUP);         //The switch is the only input in the program
	pinMode(TL_RED_PIN, OUTPUT);
	pinMode(TL_YLW_PIN, OUTPUT);
	pinMode(TL_GRN_PIN, OUTPUT);
	pinMode(PS_RED_PIN, OUTPUT);
	pinMode(PS_GRN_PIN, OUTPUT);
	setState(STATE_GRN);
} 

void loop()
{
	switchPressIncrementSpotlight();    //Runs the function to check for button changes
	if(button_pressed && !startSequence)         //If the number of counts has changed....
	{
		startSequence = true;
		startTime = millis();
	}
	if(!startSequence)
		return;
	long time = startTime;
	byte newState = 0;
	for(int i = 0; i < sizeof(STATES); i++)
	{
		time += DURATIONS[i];
		if(millis() > time)
			newState = STATES[i];
		else
			break;
	}
	if(newState == lightsState && lightsState != STATE_FLASH)
		return;
	lightsState = newState;
	setState(lightsState);	
	if(lightsState == STATE_GRN)
	{
		lightsState = 0;
		startSequence = false;
		button_pressed = false;
		startTime = 0;
	}
}

void setState(byte state)
{
	if(state == STATE_GRN)
	{
		digitalWrite(TL_RED_PIN, LOW);
		digitalWrite(TL_YLW_PIN, LOW);
		digitalWrite(TL_GRN_PIN, HIGH);
		digitalWrite(PS_RED_PIN, HIGH);
		digitalWrite(PS_GRN_PIN, LOW);
	}
	if(state == STATE_YLW)
	{
		digitalWrite(TL_RED_PIN, LOW);
		digitalWrite(TL_YLW_PIN, HIGH);
		digitalWrite(TL_GRN_PIN, LOW);
		digitalWrite(PS_RED_PIN, HIGH);
		digitalWrite(PS_GRN_PIN, LOW);
	}
	if(state == STATE_RED)
	{
		digitalWrite(TL_RED_PIN, HIGH);
		digitalWrite(TL_YLW_PIN, LOW);
		digitalWrite(TL_GRN_PIN, LOW);
		digitalWrite(PS_RED_PIN, HIGH);
		digitalWrite(PS_GRN_PIN, LOW);
	}
	if(state == STATE_PED)
	{
		digitalWrite(TL_RED_PIN, HIGH);
		digitalWrite(TL_YLW_PIN, LOW);
		digitalWrite(TL_GRN_PIN, LOW);
		digitalWrite(PS_RED_PIN, LOW);
		digitalWrite(PS_GRN_PIN, HIGH);
	}
	if(state == STATE_FLASH)
	{
		digitalWrite(TL_RED_PIN, HIGH);
		digitalWrite(TL_YLW_PIN, LOW);
		digitalWrite(TL_GRN_PIN, LOW);
		digitalWrite(PS_RED_PIN, LOW);
		float div = 500;
		int count = (int) (millis()/div);
		boolean isLit = false;
		if(count % 2 == 1)
			isLit = true;
		if(isLit != isFlashStateLit)
		{
			isFlashStateLit = isLit;
			if(isLit)
				digitalWrite(PS_GRN_PIN, HIGH);
			else
				digitalWrite(PS_GRN_PIN, LOW);
		}
	}
}

void switchPressIncrementSpotlight()
{
	long time = millis();
	int newState = readSwitchState();   //Runs the function to read the switches state
	if (newState == currState)          //If the state hasn't changed, leave the funtion
		return;
	if(currState == HIGH &&
			time - changeStartTime >
	DOWN_THRESHOLD_MILLIS)              //If the switch was down and was held long enough...
		button_pressed = true;          //Store that the button was pressed
	if(time - changeStartTime <
			DOWN_THRESHOLD_MILLIS)      //If the switch changed state to quick....
		return;                         //Leave the function
	changeStartTime = time;             //Store when the switch changed state
	currState = newState;               //Store that the switch did change state
}


int readSwitchState()
{
	int init = digitalRead(SWITCH_PIN);
	return init;
}
