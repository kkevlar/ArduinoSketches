

const int SENSOR_PIN = A2;   
int sensorValue;
int count;
float num = 0;
float num2 = 0;
long lastprint;
long lastTime;
#include <LiquidCrystal.h>
LiquidCrystal lcd(7,8,9,10,11,12);


 
void setup()
{
  Serial.begin(9600);
   lcd.begin(16, 2);
   lcd.print("dicks");
}

void loop()
{
  
  int newSensor = analogRead(SENSOR_PIN);
  if(sensorValue != 0 && millis()-lastTime > 100)
  {
    float newDelta = newSensor - sensorValue;
   if(newDelta > 0)
   num++;
   if(newDelta < 0)
   num--;
  }
  else
  {
    if(num2 != num)
    {
    lastTime = millis();
    num2 = num;
    }
  }
  
  sensorValue = newSensor;

  if(millis() - lastprint > 200)
  {
    int casted = int(round(num/50)) + 1000*26;
    int looper = casted % 26;
    looper += 65;
    char letter = looper;
    Serial.println(letter);  
    lcd.setCursor(0,0);
    lcd.print(letter);
     lastprint = millis();
  }
}
