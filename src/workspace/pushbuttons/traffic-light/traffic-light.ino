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
const int SWITCH_PIN = 2;               //Sets the input pin
const int FIRST_LED_PIN = 4;            //Sets the first LED's pin
const int NO_LEDS = 5;                  //Sets the total number of LEDs
const int DOWN_THRESHOLD_MILLIS = 100;  //Sets how long the pushbutton needs to be down
                                        //	for the program to trigger a press

int pressCount = 0;                     //Counts total # of presses
long changeStartTime = 0;               //Time since last button state change
int currState = 0;                      //Current state of the pushbutton
int loopCount = -1;                     //The loop() function's way of knowing of a
                                        //	change in the count of button presses
boolean fLP = false;                    //Tells whether this is loop()'s first
                                        //	execution (FirstLoopPass)
long stateStartTime = 0;                //The time that the lights first entered
                                        //	the current state.  Only used for
                                        //	states 2,3, and 4 because they
                                        //	have changing features.
boolean state2FlashState = false;       //Wheather or not the lights are lit when
                                        //	the lights are in state2 to know
                                        //	if they need to be turned on or off
                                        //	when one second has elapsed.
void setup()
{
	pinMode(SWITCH_PIN, INPUT);         //The switch is the only input in the program
	for(int i = 0; i < NO_LEDS; i++)    //Turns all the LED pins to output
		pinMode((FIRST_LED_PIN + i), OUTPUT);

}
void loop()
{
	switchPressIncrementSpotlight();    //Runs the function to check for button changes
	if(loopCount != pressCount)         //If the number of counts has changed....
	{
		fLP = true;                     //Tell rest of loop that its first time in state
		loopCount = pressCount;         //Account for the change so this if block is
		                                //	only run once per state change
	}
	int mod = pressCount % 5;           //Use the % operator so the states cycle through
	if(fLP == true && mod == 0)         //If its the first time the lights enter state0...
		for(int i = 0; i < NO_LEDS; i++)//Then turn off all the LEDs
			digitalWrite((FIRST_LED_PIN + i), LOW);
	if(fLP == true && mod == 1)         //If its the first time entering state 1...
		for(int i = 0; i < NO_LEDS; i++)//Then turn on all the LEDs
			digitalWrite((FIRST_LED_PIN + i), HIGH);
	if((mod == 2 || mod == 3 || mod == 4) && 
			fLP == true)                //If just now entering states 2-4...
	{
		stateStartTime = millis();      //Then make note of the time entering this state
		state2FlashState = true;        //And start the state2 LEDs lit so that they
		                                //  start off and then turn on after 1sec
	}
	if(mod == 2 && millis() - stateStartTime > 1000 && 
			state2FlashState == false)  //If in state2, 1sec has elapsed, lights off...
	{
		for(int i = 0; i < NO_LEDS; i++)//Then turn them all on,
			digitalWrite((FIRST_LED_PIN + i), HIGH);
		stateStartTime = millis();      //Store when this change was made
		state2FlashState = true;        //Save the state of the lights
	}
	if(mod == 2 && millis() - stateStartTime > 1000 && 
			state2FlashState == true)   //If in state2, 1sec has elapsed, lights on...
	{
		for(int i = 0; i < NO_LEDS; i++)//Turn them all off,
			digitalWrite((FIRST_LED_PIN + i), LOW);
		stateStartTime = millis();      //Store when this change was made
		state2FlashState = false;       //Save the state of the lights 
	}
	if(mod == 3)                        //If in state 3 (binary counting state)
	{
		float count =                   //Finds how many half-seconds have elapsed
				(millis() - stateStartTime) / 500; 
		for (int i = 0; i < NO_LEDS; i++)//For each LED...
		{
			float inverse = NO_LEDS-(i+1);//Finds the highest power of 2 that can
			                              //  be represented with the number of LEDS
			float power = pow(2,inverse);//Evaluates the power of two
			int realPower = round(power);//Rounds the power to an int
			int num = count / realPower; //Finds if the number is greater than the
			                             //  current bit trying to be represented
			if(count >= realPower)       //If the bit was able to be represened...
				count -= realPower;      //Then subtract the power of 2 from the original
			if(num == 1)                 //If the bit should be on.... then turn light on
				digitalWrite(FIRST_LED_PIN+i,HIGH);
			else                         //Otherwise turn off the light 
				digitalWrite(FIRST_LED_PIN+i,LOW);
		}
	}
	if(mod == 4)                         //If the lights are in state4, flash "SOS"
	{
		float timePassed = (millis() - stateStartTime);
		float count = timePassed / 300;  //Counts how many instances of 300ms have elapsed 
		int intCount = (int) count;      //Casts the count to an integer
		int sosMod = (intCount % 37)+1;  //Has the count cycle through 37 values, start at 1
		if(sosMod <= 5 ||                //Some super ugly logic that makes it flash properly
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
	fLP = false;                         //Stores that the loop has completed at least once
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
		pressCount++;                   //Then increment the number of presses
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
