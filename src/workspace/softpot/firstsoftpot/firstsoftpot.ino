

const int SENSOR_PIN = A2;   
int sensorValue;
int count;
void setup()
{
  Serial.begin(9600);
  
}

void loop()
{
  
  int newSensor = analogRead(SENSOR_PIN);
  if(sensorValue != 0)
  {
    float newDelta = newSensor - sensorValue;
    if(newDelta > 0)
    count++;
    else
    count--;
  }
  else
  {
    if(count < -10)
    Serial.println("down");
    else if(count > 10)
    Serial.println("up");
    count = 0;
  }
  sensorValue = newSensor;
  
  delay(5);
  
}
