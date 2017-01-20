
const int DWN_TIME = 50;

const byte COLOR_RED = 0;
const byte COLOR_GREEN = 1;
const byte COLOR_YELLOW = 2;
const byte COLOR_BLUE = 3;
const byte COLOR_SEQUENCE[] = {COLOR_RED,COLOR_GREEN,COLOR_YELLOW,COLOR_BLUE};

const byte PIN_BUTTONS[] = {11,10,9,8};
const byte PIN_LEDS[] = {5,4,3,2};

long buttonChangeTimes[sizeof(PIN_BUTTONS)];
int buttonStates[sizeof(PIN_BUTTONS)];
//int ledCounts[sizeof(PIN_BUTTONS)];
boolean shouldChangeLeds;
byte morse[5];
boolean shouldFlash;
int progress = 0;
long timeStarted;
void setup()
{
	for(int i = 0; i < sizeof(PIN_BUTTONS); i++)
		pinMode(PIN_BUTTONS[i], INPUT);
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
	if(!shouldChangeLeds && !shouldFlash)
		return;
	if(shouldFlash)
	{
		progress = -1;
		shouldChangeLeds = true;
		timeStarted = millis();
		shouldFlash = false;
	}
	if(sizeof(morse) <= 0)
		digitalWrite(PIN_LEDS[COLOR_BLUE], HIGH);
	else
		digitalWrite(PIN_LEDS[COLOR_BLUE], LOW);
	if(millis() - timeStarted > 1000)
		progress++;
	else
		return;
	if(progress >= 0)
	{
		if(progress > sizeof(morse[0]))
		{
			shouldFlash = false;
			shouldChangeLeds = false;
			digitalWrite(PIN_LEDS[COLOR_YELLOW], HIGH);
		}
	byte letter = morse[progress];
    if (letter == 1 || letter == 2)
		digitalWrite(PIN_LEDS[COLOR_RED], HIGH);
    else
    digitalWrite(PIN_LEDS[COLOR_RED],LOW);
		if(letter == 1)
			digitalWrite(PIN_LEDS[COLOR_GREEN], HIGH);
		else
			digitalWrite(PIN_LEDS[COLOR_GREEN], LOW);
	}

}


void addToWord(byte letter)
{
	byte newWord[] = {letter};
	if (sizeof(morse)!=0)
	{
		newWord[sizeof(morse)+1];
		for(int i =0; i < sizeof(newWord); i++)
		{
			newWord[i] = morse[i];
		}
   newWord[sizeof(morse)] = letter;
	}
	morse = newWord;
}

void buttonPressed(byte color)
{
	if(color == COLOR_RED)
		addToWord(2);
	if(color == COLOR_GREEN)
		addToWord(1);
	if(color == COLOR_YELLOW)
		shouldFlash == true;
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

		if(newState == buttonStates[i])
			continue;

		if(buttonStates[i] == HIGH && time - buttonChangeTimes[i] > DWN_TIME)
			buttonPressed(COLOR_SEQUENCE[i]);

		if(time - buttonChangeTimes[i] < DWN_TIME)
			continue;

		buttonChangeTimes[i] = time;
		buttonStates[i] = newState;
	}
}

