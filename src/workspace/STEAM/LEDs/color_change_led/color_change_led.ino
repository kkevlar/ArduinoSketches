
/* COLOR CHANGE LEDS - KEVIN KELLAR - January 5, 2017
 *  This program utilizes red, green and blue LEDs to produce light
 *  in different colors.  A sequence of colors will flash, each flash
 *  being followed by the lights turning dark for half a second.
 *  
 *  The arduino should be set up with the following hardware:
 *    - A red LED with a 1kOhm resistor should be connected to pin 7
 *    - A green LED with a 1kOhm resistor should be connected to pin 8
 *    - A blue LED with a 1kOhm resistor shoule be connected to pin 9
 *    * The setup can different than described above if the first 
 *      three constants are adjusted accordingly
 */

const short LED_PIN_RED = 7;   // Tells what LEDs are connected to what pin
const short LED_PIN_GREEN = 8;
const short LED_PIN_BLUE = 9;

const byte COLOR_NONE = 0;     // Defines constant numbers to represent the different colors
const byte COLOR_RED = 1;
const byte COLOR_GREEN = 2;
const byte COLOR_BLUE = 3;
const byte COLOR_YELLOW = 4;
const byte COLOR_CYAN = 5;
const byte COLOR_MAGENTA = 6;
const byte COLOR_WHITE = 7;

const long DURATION_LIGHT = 1000; // Defines the duration in ms the light will be on or off for the whole program
const long DURATION_DARK = 500;

long previousMillis;           // The variable that holds the last time the light's state was changed

byte colorSequence[] =         // An array that holds the sequence of codes representing the colors the light will be
                               // The website wants "red, yellow, green, turquioise, blue violet and back to red"
{COLOR_RED, COLOR_YELLOW, COLOR_GREEN, 
COLOR_CYAN, COLOR_BLUE, COLOR_MAGENTA, 
COLOR_RED, COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE};

byte isLit;                    // A variable that tells whether the light is currently lit (0=no, 1=yes)
int index;                     // A variable that holds how many colors from the sequence have been shown so far

void setup() 
{
  pinMode(LED_PIN_RED, OUTPUT);// Set all of the pins with LEDs to output mode
  pinMode(LED_PIN_GREEN, OUTPUT);
  pinMode(LED_PIN_BLUE, OUTPUT);
  pinMode(13, OUTPUT);
  previousMillis = millis();   // Makes it so the light will be off for DURATION_DARK until it starts the sequence  
  index = 0;                   // Start the the flashes at the first color in the sequence
  isLit = 0;                   // The lights are starting unlit (unlit = 0)
}

void loop() 
{                               // If time elapsed since last change in the light's state is long 
  if (millis() - previousMillis >= getDelay())  enough
  {
    previousMillis = millis();  // Sets the last time the light was changed to "now"
    isLit = (isLit + 1) % 2;    // Flips isLit from 0 --> 1 or 1 --> 0
    if (isLit == 0)             // If turning the light off, then
    {
      index++;                  // So the next time the light turns on its the next color in the sequence
      setColor(COLOR_NONE);     // Turn off the light
    }
    else
    {
                                // Turn the light on and to the current color in the sequence by knowing how many colors have been shown so far
      setColor(colorSequence[index % sizeof(colorSequence)]);
    }
  }
}

long getDelay()                 // A method to return how long the light should stay at the current state
{
  if (isLit == 0)               // If it's not lit, return the preset duration of how long it should be unlit
    return DURATION_DARK;
  else
    return DURATION_LIGHT;
}

void setColor(byte color)       // A method to set the color of the light to the specified color code
{
  if(color == COLOR_NONE)       // No color is red off, green off, and blue off (AKA unlit)
    tripleSet(0,0,0);
  else if (color == COLOR_RED)  // To make red, only the red LED should be on, and everything else off
    tripleSet(1,0,0);
  else if (color == COLOR_GREEN)
    tripleSet(0,1,0);
  else if (color == COLOR_BLUE)
    tripleSet(0,0,1);
  else if (color == COLOR_YELLOW)
    tripleSet(1,1,0);
  else if (color == COLOR_CYAN)
    tripleSet(0,1,1);
  else if (color == COLOR_MAGENTA)
    tripleSet(1,0,1);
  else if (color == COLOR_WHITE)
    tripleSet(1,1,1);
}
                                // This method sets the state of each of the LEDs all at once
void tripleSet(byte red, byte green, byte blue) 
{
  if(red > 0)                   // Turn on the red LED if the "red" argument is 1
    digitalWrite(LED_PIN_RED, HIGH);
  else
    digitalWrite(LED_PIN_RED, LOW);

  if(green > 0)
    digitalWrite(LED_PIN_GREEN, HIGH);
  else
    digitalWrite(LED_PIN_GREEN, LOW);

  if(blue > 0)
    digitalWrite(LED_PIN_BLUE, HIGH);
  else
    digitalWrite(LED_PIN_BLUE, LOW);
}






