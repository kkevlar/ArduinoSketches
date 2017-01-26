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

    currentRGB[0] = 255;
    currentRGB[1] = 200;
    currentRGB[2] = 0;
    goalRGB[0] = 255;
    goalRGB[1] = 100;
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
    }
    int bank = 0;
    for (int x = 0; x < 3000; x++)
    {
        int red = logmatize(currentRGB[0]);
        int green = logmatize(currentRGB[1]);
        int blue = logmatize(currentRGB[2]);
        analogWrite(PIN_RED, red);
        analogWrite(PIN_GRN, green);
        analogWrite(PIN_BLU, blue);
        delay(1);
        if(x > 1000 && x < 2000 && random(100) < 30)
        {
            bank++;
            currentRGB[0] += increment[0];
           currentRGB[1] += increment[1];
            currentRGB[2] += increment[2];
        }
        if(bank > 0 && x > 2000 && random(100)>((3000-x)/10))
        {
          bank--;
          continue;
        }
        currentRGB[0] += increment[0];
        currentRGB[1] += increment[1];
        currentRGB[2] += increment[2];
    }
    //for(int i = 0; i < 3; i++)
    // goalRGB[i] = 0;
     
    delay(300);
    int total = 0;
    int want = random(4) + 1;
    if(want == 3 && random(100) > 20)
      want = random(2)+1;
    if(want == 4 && random(100) > 50)
      want = random(2)+1;
    if(want == 4)
    {
       for (int x = 0; x < 3; x++) 
      {
        int num = random(255+50)-25;
        num = constrain(num,0,255);
        goalRGB[x] = num;
       }
       return;
    }
    while(total != want)
    {
    total = 0;
    for (int x = 0; x < 3; x++) 
    {
        int num = random(2)*255;
        num = constrain(num,0,255);
        goalRGB[x] = num;
        if(num > 0)
        total++;
    }
    }
   
}
int logmatize(float num)
{
  return constrain(255-int( ( (log(255-num) - 1) / (log(255)-1) ) * 255),0,255);
  //return constrain(int(pow(num,.5)*(255/pow(255,.5))),0,255);
}
void HSV_to_RGB(float h, float s, float v, byte *r, byte *g, byte *b)
{
  int i,f,p,q,t;
  
  h = max(0.0, min(360.0, h));
  s = max(0.0, min(100.0, s));
  v = max(0.0, min(100.0, v));
  
  s /= 100;
  v /= 100;
  
  if(s == 0) {
    // Achromatic (grey)
    *r = *g = *b = round(v*255);
    return;
  }

  h /= 60; // sector 0 to 5
  i = floor(h);
  f = h - i; // factorial part of h
  p = v * (1 - s);
  q = v * (1 - s * f);
  t = v * (1 - s * (1 - f));
  switch(i) {
    case 0:
      *r = round(255*v);
      *g = round(255*t);
      *b = round(255*p);
      break;
    case 1:
      *r = round(255*q);
      *g = round(255*v);
      *b = round(255*p);
      break;
    case 2:
      *r = round(255*p);
      *g = round(255*v);
      *b = round(255*t);
      break;
    case 3:
      *r = round(255*p);
      *g = round(255*q);
      *b = round(255*v);
      break;
    case 4:
      *r = round(255*t);
      *g = round(255*p);
      *b = round(255*v);
      break;
    default: // case 5:
      *r = round(255*v);
      *g = round(255*p);
      *b = round(255*q);
    }
}

