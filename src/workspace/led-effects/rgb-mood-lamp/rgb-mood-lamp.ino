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
}
void loop()
{
    randomSeed(analogRead(0));
    for (int i = 0; i < 3; i++)
    {
        increment[i] = (goalRGB[i] - currentRGB[i]) / 1000;
    }
    for (int x = 0; x < 1000; x++)
    {
        int red = int(currentRGB[0]);
        int green = int(currentRGB[1]);
        int blue = int(currentRGB[2]);
        analogWrite(PIN_RED, red);
        analogWrite(PIN_GRN, green);
        analogWrite(PIN_BLU, blue);
        delay(1);
        currentRGB[0] += increment[0];
        currentRGB[1] += increment[1];
        currentRGB[2] += increment[2];
    }
    
      
    delay(400);
    int dark = random(3);
    for (int x = 0; x < 3; x++) 
    {
        int num = random(256);
       // float diff = abs(goalRGB[x] - num);
        //if(diff < ((100/2)-10) || (random(100) > 90  && num > 100))
        //{
         // x--;
         // continue;
       // }
       if(x == dark && x!=0)
        goalRGB[x] = 0;
        else
        goalRGB[x] = num;
        ///total += num;
    
    }
   
}
