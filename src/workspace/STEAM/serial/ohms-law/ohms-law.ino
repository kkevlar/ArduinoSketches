/* OHMS LAW - KEVIN KELLAR - January 10, 2017
 *  Calculates ohms law based on inital values
 *   of resistance and current
 */
const int CURRENT = 1;             //Sets the Current
const int RESISTANCE = 1000;       //Sets the Resistance
void setup()
{
 Serial.begin(9600);               //Sets up the Serial Monitor
 Serial.print("Current:    ");     //The label for current
 Serial.print(CURRENT);            //The value for current
 Serial.println("A");              //The unit for current
 Serial.print("Resistance: ");     //The label for resist
 Serial.print(RESISTANCE);         //The value for resist
 Serial.println("ohms");           //The unit for resist
 Serial.print("Voltage:    ");     //The label for voltage
 Serial.print(CURRENT*RESISTANCE); //The value for voltage
 Serial.println("V");              //The unit for voltage
}
void loop(){}                      //Who cares

