
const int DWN_TIME = 100;

const byte COLOR_RED = 0;
const byte COLOR_GREEN = 1;
const byte COLOR_YELLOW = 2;
const byte COLOR_BLUE = 3;
const byte[] COLOR_SEQUENCE = {COLOR_RED,COLOR_GREEN,COLOR_YELLOW,COLOR_BLUE};

const byte[] PIN_BUTTONS = {11,10,9,8};
const byte[] PIN_LEDS = {5,4,3,2};

long buttonChangeTimes[sizeof(PIN_BUTTONS)];
int buttonStates[sizeof(PIN_BUTTONS)];
int ledCounts[sizeof(PIN_BUTTONS)];
boolean shouldChangeLeds;

void setup()
{
	for(int i = 0; i < sizeof(PIN_BUTTONS); i++)
		pinMode(PIN_BUTTONS[i], INPUT_PULLUP);
	for(int i = 0; i < sizeof(PIN_LEDS); i++)
		pinMode(PIN_LEDS[i], OUTPUT);
	pinMode(13,OUTPUT);
	initialize();
} 

void initialize()
{
	digitalWrite(13,LOW);
}

void loop()
{
	switchPressTester();
	if(!shouldChangeLeds)
		return;
	for(int i = 0; i < sizeof(PIN_LEDS); i++)
	{
		int state = LOW;
		if(ledCounts[i]%2 == 1)
			state = HIGH;
		digitalWrite(PIN_LEDS[i],state);
	}
	shouldChangeLeds = false;
}

void buttonPressed(byte color)
{
	ledCounts[color]++;
	shouldChangeLeds = true;
}

void switchPressTester()
{

	long time = millis();
	for(int i = 0; i < sizeof(PIN_BUTTONS); i++)
	{
		int newState = digitalRead(PIN_BUTTONS[i]);
		/*
		if(redButtonState == LOW && time - redChangeTime > 2000)
		{
			initialize();
			redChangeTime = time;
			redButtonState = newState;
			return;
		}
		*/
		if (newState == buttonStates[i])
			return;

		if(buttonStates[i] == HIGH && time - buttonChageTimes[i] > DWN_TIME)
			buttonPressed(COLOR_SEQUENCE[i]);

		if(time - buttonChageTimes[i] < DWN_TIME)
			return;

		buttonChageTimes[i] = time;
		buttonStates[i] = newState;
	}
}

