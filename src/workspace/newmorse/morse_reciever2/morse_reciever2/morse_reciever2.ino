
unsigned char currMorse[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int currMorseIndex = 0;

int ambientLight = 0;
long startTime = 0;
byte state = 0;

const int LIGHT_CHANGE_THRESHOLD = 30;

const int TIME_UNIT = 30;
const int TIME_DASH 
const int TIME_SPACE
const int TIME_NEWLETTER

const int LIGHT_PIN = A1;


#include <LiquidCrystal.h>
LiquidCrystal lcd(7,8,9,10,11,12);

const unsigned char letters[] = {
    /*A*/ B01001000,
    /*B*/ B10010000,
    /*C*/ B10010100,
    /*D*/ B01110000,
    /*E*/ B00100000,
    /*F*/ B10000100,
    /*G*/ B01111000,
    /*H*/ B10000000,
    /*I*/ B01000000,
    /*J*/ B10001110,
    /*K*/ B01110100,
    /*L*/ B10001000,
    /*M*/ B01011000,
    /*N*/ B01010000,
    /*O*/ B01111100,
    /*P*/ B10001100,
    /*Q*/ B10011010,
    /*R*/ B01101000,
    /*S*/ B01100000,
    /*T*/ B00110000,
    /*U*/ B01100100,
    /*V*/ B10000010,
    /*W*/ B01101100,
    /*X*/ B10010010,
    /*Y*/ B10010110,
    /*Z*/ B10011000
};
void setup()
{
    Serial.begin(9600);
    pinMode(13, OUTPUT);
    pinMode(A1, INPUT);
    digitalWrite(13, LOW);
    initialize();
}

void initialize()
{
    delay(100);
    digitalWrite(13, LOW);
    lcd.begin(16, 2);
    lcd.clear();
}

int lengthOfMorse(unsigned char letter)
{
    int howLong = 0;
    for (int y = 0; y < 3; y++) {
        int bit = (letter >> (7 - y)) & 1;
        int exponent = 2 - y;
        howLong += (round(pow(2, exponent)) * bit);
    }
    return howLong;
}

void loop()
{
    
}

/*
void printTimes(int state, int timeMillis)
{

    float shortestUp = 50000;
    for (int i = 0; i < sizeof(upTimes) / sizeof(int); i++) 
    {
  
        if (upTimes[i] < shortestUp && upTimes[i] > 25)
            shortestUp = upTimes[i];
    }

    unitLength = shortestUp;
    if (dealtWith == false) {
        for (int i = 0; i < sizeof(upTimes) / sizeof(int); i++) {
            addToWhileOn(upTimes[i]);
            if (i + 1 < sizeof(upTimes) / sizeof(int)) {
                addToWhileOff(downTimes[i + 1]);
            }
        }

        dealtWith = true;
    }

    if (state == 1)
        addToWhileOn(timeMillis);
    else {
        addToWhileOff(timeMillis);
    }
  
   lcd.setCursor(0,0);
   int offset = currMorseIndex - 32;
   if(offset < 0)
   offset = 0;
    for (int i = 0; i < sizeof(currMorse); i++)
    {
        
        if (currMorse[i] == 0)
        {
            Serial.print(" ");
            if(i - offset >= 0)
               lcd.print(" ");
            
        }
        else
        {
            Serial.print(matchToMorse(currMorse[i]));
            if(i - offset >= 0)
              lcd.print(matchToMorse(currMorse[i]));
            //  if(i-offset == 15)
            //  lcd.setCursor(0,1);
        }
    }
 
    Serial.println();
}
*/

char morseCharToLetter(unsigned char morse)
{
    for (int i = 0; i < sizeof(letters); i++) {
        if (morse == letters[i])
            return 65 + i;
    }
}
void addToWhileOn(int intTime)
{
    float now = intTime;
    float unit = now / unitLength;
    if (unit < THRESH_DASH)
        dot();
    else
        dash();
}
void addToWhileOff(int intTime)
{
    float now = intTime;
    float unitt = now / unitLength;
    if (unitt > THRESH_SPACE) {
        currMorseIndex++;
        currMorseIndex++;
    }
    else if (unitt > THRESH_NEWLETTER) {
        currMorseIndex++;
    }
}
void addDashOrDot(byte value)
{
    int howLong = lengthOfMorse(currMorse[currMorseIndex]);
    howLong++;
    byte bitToChange = 7 - (howLong + 2);
    currMorse[currMorseIndex] ^= (-value ^ currMorse[currMorseIndex]) & (1 << bitToChange);
    for (int i = 0; i < 3; i++) {
        byte exponent = 2 - i;
        value = 0;
        byte binNum = round(pow(2, exponent));
        if (howLong >= binNum) {
            howLong -= binNum;
            value = 1;
        }
        bitToChange = (7 - i);
        currMorse[currMorseIndex] ^= (-value ^ currMorse[currMorseIndex]) & (1 << bitToChange);
    }
    for (int i = 0; i < 8; i++) {
        int bitt = (currMorse[currMorseIndex] >> (7 - i)) & 1;
    }
}
void dash()
{
    addDashOrDot(1);
}
void dot()
{
    addDashOrDot(0);
}

void doPhotocellThings()
{
    long lightDelta = analogRead(LIGHT_PIN) - ambientLight;
    long timeDelta = millis() - startTime;
    if (millis() > 500 && ambientLight == 0)
    {
      ambientLight = analogRead(LIGHT_PIN);
    }
    else
    {
      if(lightDelta > LIGHT_CHANGE_THRESHOLD && state != 2)
      {
        if(state == 1)
        {
          addToWhileOff(timeDelta);
        }
        state = 2;
        startTime = millis();
      }
      else if( !(delta > LIGHT_CHANGE_THRESHOLD) && state == light) 
      {
        state = 1;
        startTime = millis();
        addToWhileOn(timeDelta);
      }
    }
    
}


