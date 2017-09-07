
int diffThresh = 100;
int keepThresh = 50;
long timeThresh = 100*1000;
int baseline = 0;
int newBaseline = 0;
long startDiff = 0;
bool hasDiff = false;
int switchCount = 0;

void setup() 
{
  pinMode(A1,INPUT);
}

void loop() 
{
  int val = analogRead(A1);
  if(abs(val - baseline) > diffThresh)
  {
    if(hasDiff == false) //initiate newBaseLine
    {
      startDiff = micros();
      hasDiff = true;
      newBaseline = val;
    }
    else if (abs(val - newBaseline) > keepThresh) //see if maintains newbase line
    {
      hasDiff = false; //failure
    }
    else
    {
      if (micros() - startDiff > timeThresh)  //maintain, and enough time
      {
        baseline = newBaseline;
        hasDiff = false;
        switchCount++; //success
      }
    }
  }
  else
  {
    hasDiff = false; //status quo, close enough to baseline
  }
}
