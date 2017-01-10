/* DISTANCE CALCULATOR - KEVIN KELLAR - January 10, 2017
 *  Calculates the distance from newport to corvallis in
 *    miles, yards, football fields, inches, and feet
 */
const float MILES = 55.6;                              //No of miles
const int YARDS_IN_MILE = 1760;                        //Conversion factors
const int YARDS_IN_FOOTBALL_FIELD  = 120;
const int FEET_IN_YARD = 3;
const int INCHES_IN_FOOT = 12;

float inMiles;                                         //Variables to hold the conversions
float inYards;
float inFootballFields;
float inFeet;
float inInches;
void setup()
{
 Serial.begin(9600);                                   //Sets up the Serial Monitor
 
 inMiles = MILES;
 inYards = inMiles * YARDS_IN_MILE;                    //Doing the conversions
 inFootballFields = inYards / YARDS_IN_FOOTBALL_FIELD;
 inFeet = inYards * FEET_IN_YARD;
 inInches = inFeet * INCHES_IN_FOOT;

 Serial.println("Distance from Newport to Corvallis");//Prints the variables and labels
 Serial.print(inMiles );
 Serial.println("       miles");
 Serial.print(inFootballFields);
 Serial.println("      football fields");
 Serial.print(inYards);
 Serial.println("    yards");
 Serial.print(inFeet);
 Serial.println("   feet");
 Serial.print(inInches);
 Serial.println("  inches");
}
void loop(){}                                          //Who cares

