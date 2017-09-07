

unsigned char currMorse[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int currMorseIndex = 0;
int loopCurr = 0;

int transBeepCount = 0;
int transLetterIndex = 0;
long transWait = 0;
int transBeepIndex = 0;
int transState = 0;

int ambientLight = 0;
long startTime = 0;
byte state = 0;

const int LIGHT_CHANGE_THRESHOLD = 100;

const int TIME_UNIT = 60;
const int TIME_DASH = TIME_UNIT * 2.75;
const int TIME_SPACE = TIME_UNIT * 6.5;
const int TIME_NEWLETTER = TIME_UNIT * 3;

const int LIGHT_PIN = A1;

String transmission = "FREEDMAN IS A GOON    ";

#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

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
    Serial.println("__________________________");
    pinMode(13, OUTPUT);
    pinMode(A1, INPUT);
    digitalWrite(13, LOW);
    initialize();
}

unsigned char morseAtIndex(int index)
{
    transmission.toUpperCase();

    char currChar = transmission.charAt(index);
    if (currChar == ' ')
        return B00000000;
    int letterNum = currChar - 65;
    return letters[letterNum];
}

void initialize()
{
    delay(100);
    pinMode(13, OUTPUT);
    pinMode(A1,INPUT);
    pinMode(12, OUTPUT);
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    lcd.begin(16, 2);
    lcd.clear();
    Serial.begin(9600);
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
    doPhotocellThings();
    
    if (loopCurr != currMorseIndex) {

        for (int i = 0; i < currMorseIndex + 1; i++) {
            Serial.print(morseCharToLetter(currMorse[i]));
        }
        Serial.println();
        loopCurr = currMorseIndex;

        
    }
    /*
    if (millis()/1000 > loopCurr && true)
    {
      loopCurr= millis() / 1000;
      for(int x = 0; x < 3; x++)
      {
        for (int y = 0; y < 8; y++)
        {
          if(y == 3)
          Serial.print(" ");
          int bitt = (currMorse[x] >> (7 - (y))) & 1;
          Serial.print(bitt); 
        }
        Serial.print(", ");
      }
      Serial.println();
    }
    */

    if (millis() > transWait) {
        if (transState == 1 && transBeepIndex == transBeepCount) //letter over
        {
         
            transBeepIndex = 0;
            transLetterIndex++;
            unsigned char currMorse = morseAtIndex(transLetterIndex);
            transBeepCount = lengthOfMorse(currMorse);
            if (transBeepCount == 0) {
                transWait = millis() + TIME_UNIT * 7;
                transLetterIndex++;
            }
            else
                transWait = millis() + TIME_UNIT * 3.5;

            transState = 0;
            lightsOff();
        }
        else if (transState == 1) {
           
            transWait = millis() + TIME_UNIT;
            transState = 0;
            lightsOff();
        }
        else if (transState == 0) {
           
            unsigned char currMorse = morseAtIndex(transLetterIndex);
            transBeepCount = lengthOfMorse(currMorse);
            int bitt = (currMorse >> (7 - (transBeepIndex + 3))) & 1;
            if (bitt == 1)
                transWait = millis() + TIME_UNIT * 3;
            else
                transWait = millis() + TIME_UNIT;
            transBeepIndex++;
            transState = 1;
            lightsOn();
        }
    }

    
}
void lightsOn()
    {
        digitalWrite(12, HIGH);
    }
    void lightsOff()
    {
        digitalWrite(12, LOW);
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
    if (now < TIME_DASH)
        dot();
    else
        dash();
}
void addToWhileOff(int intTime)
{
    float now = intTime;
    if (now > TIME_SPACE) {
        currMorseIndex++;
        currMorseIndex++;
    }
    else if (now > TIME_NEWLETTER) {
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
  //Serial.println(analogRead(LIGHT_PIN));
    long lightDelta = analogRead(LIGHT_PIN) - ambientLight;
    long timeDelta = millis() - startTime;
    if (millis() > 500 && ambientLight == 0) {
        ambientLight = analogRead(LIGHT_PIN);
    }
    else {
        if (lightDelta > LIGHT_CHANGE_THRESHOLD && state != 2) {
            if (state == 1) {
                addToWhileOff(timeDelta);
            }
            state = 2;
            startTime = millis();
        }
        else if (!(lightDelta > LIGHT_CHANGE_THRESHOLD) && state == 2) {
            state = 1;
            startTime = millis();
            addToWhileOn(timeDelta);
        }
    }
}


