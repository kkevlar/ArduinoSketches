/* TRAFFIC_LIGHT - KEVIN KELLAR - January 17, 2017
 *  
 */
const int SWITCH_PIN = 2;               //Sets the input pin
const int DOWN_THRESHOLD_MILLIS = 100;  //Sets how long the pushbutton needs to be down
                                        //	for the program to trigger a press

int pressCount = 0;                     //Counts total # of presses
long changeStartTime = 0;               //Time since last button state change
int currState = 0;                      //Current state of the pushbutton
int loopCount = -1;                     //The loop() function's way of knowing of a
                                        //	change in the count of button presses
boolean fLP = false;                    //Tells whether this is loop()'s first
                                        //	execution (FirstLoopPass)

void setup()
{
	pinMode(SWITCH_PIN, INPUT);         //The switch is the only input in the program
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
