/* TRAFFIC_LIGHT - KEVIN KELLAR - January 19, 2017
 *   Has the arduino simulate a traffic light and pedestrian
 *   crossing. When the button is pressed, the light eventually
 *   changes from green to yellow to red, while the pedestiran
 *   crossing light changed from red, to green, to flashing, and
 *   then back to red.
 *   
 *   Five LEDs with resistors should be connected to different
 *   pins according to the fist set of constants below.
 *   
 *   The button should utilize a pull-up resistor because that is
 *   the input mode set for that pin in the setup() function.
 */

/* Pin constants: 
 *  Sets the hardware configuration of the Arduino
 *  and the number of ms needed to trigger a button press.
 */
const int DWN_TIME = 100;
const int SWITCH_PIN = 12;
const int RESET_PIN = 11;
const int TL_RED_PIN = 10;
const int TL_YLW_PIN = 9;
const int TL_GRN_PIN = 8;
const int PS_RED_PIN = 7;
const int PS_GRN_PIN = 6;

// Time constants: The number of ms that should be spent in each state
const int DUR_INIT_STATE = 5000;
const int DUR_YELLOW_STATE = 5000;
const int DUR_RED_STATE = 2000;
const int DUR_PED_STATE = 5000;
const int DUR_FLASH_STATE = 5000;
const int DUR_FINAL_STATE = 2000;

// State constants: Each state in the cycle had a unique ID
const byte STATE_GRN = 5;
const byte STATE_YLW = 1;
const byte STATE_RED = 2;
const byte STATE_PED = 3;
const byte STATE_FLASH = 4;

/* Array constants: 
 *   The durations and states arrays' indicies corrospond
 *   to each other. For index 0, it can be read as: "after waiting 
 *   the predetermined duration in the inital state, switch to the
 *   yellow-light state". 
 */
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

/* Button variables: 
 *   These variables are for the button methods to store the current
 *   state of the button and how long it has been in that state.
 */
long redChangeTime = 0; 
int redButtonState = 0;
long greenChangeTime = 0;
int greenButtonState = 0;

/* Loop() variables:
 *   These variables allow the loop() fuction to know if the button
 *   has been triggered, whether or not the light cycle sequece has
 *   started, and at what time the light cycle started.
 */
boolean button_pressed = false;
boolean startSequence = false;                   
long startTime = 0;
byte lightsState = 0;
long pin13LastFlashTime = 0;
boolean pin13FlashState = false;

/* Flash variables:
 *   These variables are for the setState() function to know
 *   when to flash the green pedestrian light on or off.
 */

byte flashState = 0;

/* setup():
 *   Sets all of the pins to the correct mode (LED pins in OUPUT)
 *   and the input pins in pullup mode.
 *   Also starts the system in the "green light" state.
 */
void setup()
{
	pinMode(SWITCH_PIN, INPUT_PULLUP);
	pinMode(RESET_PIN, INPUT_PULLUP);
	pinMode(TL_RED_PIN, OUTPUT);
	pinMode(TL_YLW_PIN, OUTPUT);
	pinMode(TL_GRN_PIN, OUTPUT);
	pinMode(PS_RED_PIN, OUTPUT);
	pinMode(PS_GRN_PIN, OUTPUT);
	pinMode(13,OUTPUT);
	reset();
} 

void loop()
{
	//The switch press function tests for button state changes
	switchPressTester();
  //secondarySwitchPressTester();
	/* First Control Block:
	 *   Tests to see if the button was pressed and the sequence
	 *   still hasn't started. If so, it starts the sequence.
	 *   After that if-block, the function tests to see if the sequence
	 *   has started. If not, it exits; there is nothing lef to do.
	 */
	if(button_pressed && !startSequence) 
	{
		startSequence = true;
		startTime = millis();
	}
	if(!startSequence)
		return;

	/* Pin13 Block:
	 *   Causes the onboard LED to blink while the sequence is in progress. 
	 */
	if(millis() - pin13LastFlashTime > 500)
	{
		pin13FlashState = !pin13FlashState;
		if(pin13FlashState)
			digitalWrite(13,HIGH);
		else
			digitalWrite(13,LOW);
		pin13LastFlashTime = millis();
	}

	/* State decision block:
	 *   Finds the furthest state down the array that enough time 
	 *   has elapsed to allow.  If not enough time has elapsed to 
	 *   trigger the next state, the for-loop exits and the furthest
	 *   state that was tested for is stored in the newState variable.
	 *   
	 *   If this "newState" isn't different, then the function exits,
	 *   because no changes to the LEDs need to be made, except if 
	 *   the LEDs are in the "flashing" state because then the LEDs 
	 *   might still need to be changed.
	 */
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

	/* State setting block:
	 *   However, if the state is changing, then the LEDs need to
	 *   be changed to account for this state change, so the 
	 *   setState() function is called.
	 *   
	 *   This also resets the flashing state variable if just now
	 *   entering a state.
	 */
	if(newState != lightsState)
		flashState = 0;
	lightsState = newState;
	setState(lightsState);

	/* Resetting Block:
	 *   If the state was just set to the "green light" state,
	 *   then that means that the cycle has finished.  To allow
	 *   the lights to be triggered again, the variables need to be
	 *   set back to their initial conditions.
	 */
	if(lightsState == STATE_GRN)
	{
		reset();
	}
}

void reset()
{
	lightsState = 0;
	startSequence = false;
	button_pressed = false;
	startTime = 0;
	setState(STATE_GRN);
}

/* setState():
 *   Sets the state based on the id provided as a parameter
 */
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
		/* Flash State Setter:
		 *   Sets the flash state so the green ped light blinks
		 *   every half-second. To achive this, newFlashState
		 *   alternates from 1 to 2 and the LEDs are only changed
		 *   if this value is different from the on previous.
		 */
		float div = 500;
		int count = (int) (millis()/div);
		int newFlashState = (count % 2)+1;
		if(newFlashState != flashState)
		{
			digitalWrite(TL_RED_PIN, HIGH);
			digitalWrite(TL_YLW_PIN, LOW);
			digitalWrite(TL_GRN_PIN, LOW);
			digitalWrite(PS_RED_PIN, LOW);

			flashState = newFlashState;

			if(flashState == 1)
				digitalWrite(PS_GRN_PIN, HIGH);
			else
				digitalWrite(PS_GRN_PIN, LOW);
		}
	}
}

/* switchPressTester()
 *   Tests for a change in the switch's state and then logs
 *   the time of the change if the switch's state did change.
 *   
 */
void switchPressTester()
{
	/* Inital Control Block:
	 *   Tests for a change in state and exits if there
	 *   isnt one.
	 */
	long time = millis();
	int newState = readSwitchState(); 
  if(redButtonState == LOW && time - redChangeTime > 2000)
  {
    reset();  
    redChangeTime = time;
    redButtonState = newState;
    return;
  }
	if (newState == redButtonState)
		return;

	/* Button press Block:
	 *   Only tells the loop() method that the button was pressed
	 *   if the button WAS down, and was held for a time that 
	 *   is longer than the required duration set at the 
	 *   top of the sketch.
	 */
	if(redButtonState == HIGH && time - redChangeTime > DWN_TIME)
		button_pressed = true;

	/* Bouce reduction block:
	 *   Causes the method to exit if there was a state change
	 *   that was too short.
	 */
	if(time - redChangeTime < DWN_TIME)
		return;

	/* Mutation block: 
	 *   If the previous change in state lasted long enough, then the
	 *   new state is logged and the time that the state
	 *   started is reset.
	 */
	redChangeTime = time;
	redButtonState = newState;
}

/* readSwitchState():
 *   Exists as a different function to allow for easy changes
 *   if further steps need to be taken to reduce false presses
 *   with the "bounce" problem.
 */
int readSwitchState()
{
	int init = digitalRead(SWITCH_PIN);
	return init;
}
