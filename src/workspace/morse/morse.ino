
const int ledPin =  13; 
int ledState = LOW;
unsigned long previousMillis = 0;       
int swaps = 0;

long interval = 0;
const long globalInterval = 150;
const int betweenWords = 7;
const int betweenLetters = 3;

void setup() 
{
  pinMode(ledPin, OUTPUT);
  setIntervalFromSwaps();
}

void loop() 
{
  if (millis() - previousMillis >= interval)
  {
    previousMillis = millis();

    
    if (ledState == LOW)
    {
      ledState = HIGH;
    }
    else
    {
      ledState = LOW;
    }
    swaps++;
    setIntervalFromSwaps();
    digitalWrite(ledPin, ledState);
  }
}

void setIntervalFromSwaps()
{
  if (swaps < 6 && swaps != 0)
  interval = globalInterval;
  else if (swaps == 0)
  interval = globalInterval * 4;
  else if (swaps == 6 || swaps == 12)
  interval = globalInterval * 3;
  else if (swaps > 6 && swaps % 2 == 1 && swaps < 12)
  interval = globalInterval * 3;
  else if (swaps > 12 && swaps < 18)
  interval = globalInterval;
  else if (swaps == 18)
  {
  interval = globalInterval * 10;
  swaps = 0;
  }
  else
  interval = globalInterval;
 
}

