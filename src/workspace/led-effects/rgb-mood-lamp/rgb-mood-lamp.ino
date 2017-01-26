const int PIN_RED = 9;
const int PIN_GRN = 10;
const int PIN_BLU = 11;

float currentRGB[3];
float goalRGB[3];
float increment[3];
void setup()
{
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(PIN_RED,OUTPUT);
    pinMode(PIN_GRN,OUTPUT);
    pinMode(PIN_BLU,OUTPUT);
    pinMode(13,OUTPUT);
    Serial.begin(9600);
    randomSeed(analogRead(0));

    currentRGB[0] = 0;
    currentRGB[1] = 0;
    currentRGB[2] = 255;
    goalRGB[0] = 255;
    goalRGB[1] = 0;
    goalRGB[2] = 0;
    for(int i = 0; i <= 255; i+=5)
    {
       Serial.print(i);
       Serial.print(" --> ");
       Serial.println(logmatize(i));
    }  
}
void loop()
{
    randomSeed(analogRead(0));
    for (int i = 0; i < 3; i++)
    {
        increment[i] = (goalRGB[i] - currentRGB[i]) / 3000 ;
        if(random(8) == 2)
          increment[i] = 0;
    }
    for (int x = 0; x < 3000; x++)
    {
  
        int red = logmatize(currentRGB[0]);
        int green = logmatize(currentRGB[1]);
        int blue = logmatize(currentRGB[2]);
        analogWrite(PIN_RED, red);
        analogWrite(PIN_GRN, green);
        analogWrite(PIN_BLU, blue);
        delay(1);
        currentRGB[0] += increment[0];
        currentRGB[1] += increment[1];
        currentRGB[2] += increment[2];
    }
    //for(int i = 0; i < 3; i++)
    // goalRGB[i] = 0;
     
    delay(800);
    int total = 0;
    while(total < 240 || total > 550)
    {
    total = 0;
    for (int x = 0; x < 3; x++) 
    {
        int num = random(556)-100;
        if(random(7)==1)
          num = 0;
        num = constrain(num,0,255);
        goalRGB[x] = num;
        total +=  num;  
    }
    }
   
}
int logmatize(float num)
{
  return constrain(255-int( ( (log(255-num) - 1) / (log(255)-1) ) * 255),0,255);
  //return constrain(int(pow(num,.5)*(255/pow(255,.5))),0,255);
}

