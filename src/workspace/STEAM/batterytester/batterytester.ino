/* KEVIN KELLAR - FEB9 - BATTERYTESTER
 *  Green Led to pin2
 *  Yellow Led to pin3
 *  Red Led to pin4
 *  
 */
//Sets up the LCD
#include <LiquidCrystal.h>
LiquidCrystal lcd(7,8,9,10,11,12);
void setup() 
{
  //Sets up the output in input pins
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(A4,INPUT);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  //Begins the LCD
  lcd.begin(16,2);
}

void loop()
{
  //Reads voltage
  float reading = analogRead(A4);
  //Maps to millivolts
  float imTheMap = map(reading, 0,1023,0,5000);
  //Tests for which LED to light
  if (1600 <= imTheMap)
    digitalWrite(2,HIGH);
   else if(1400 < imTheMap)
    digitalWrite(3,HIGH);
  else
    digitalWrite(4,HIGH);
  //Prints the voltage read
  lcd.clear();
  lcd.setCursor(0,0);
  float real = imTheMap/1000;
  lcd.print(real);
  lcd.print("V");
  //Waits for two seconds
  delay(2000);
  //Turns off the leds
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
   
}
