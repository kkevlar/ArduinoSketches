/* TRAFFIC_LIGHT - KEVIN KELLAR - January 19, 2017
 *
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

long redChangeTime = 0; 
int redButtonState = 0;
long greenChangeTime = 0;
int greenButtonState = 0;

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
	initialize();
} 

void loop()
{
	//The switch press function tests for button state changes
	switchPressTester();

}

void initialize()
{
	digitalWrite(13,LOW);
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
		initialize();
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
