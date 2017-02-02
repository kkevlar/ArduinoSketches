
const int DWN_TIME = 50;

const byte COLOR_RED = 0;
const byte COLOR_GREEN = 2;
const byte COLOR_YELLOW = 3;
const byte COLOR_BLUE = 1;
const byte COLOR_SEQUENCE[] = { COLOR_RED, COLOR_BLUE, COLOR_GREEN, COLOR_YELLOW, COLOR_BLUE };

const byte PIN_BUTTONS[] = { 5, 4, 3, 2 };
const byte PIN_LEDS[] = { 11, 10, 9, 8 };

int calibrateCount = 0;
float calibration = 0;

byte photoCellHitCount = 0;
int upTimes[] = { 0, 0, 0, 0, 0 };
int downTimes[] = { 0, 0, 0, 0, 0 };
long photoStateChangeTime = 0;
byte photoOn = 0;
boolean dealtWith = false;
float unitLength = 0;

long buttonChangeTimes[sizeof(PIN_BUTTONS)];
int buttonStates[sizeof(PIN_BUTTONS)];
unsigned char currMorse[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int currMorseIndex = 0;

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
    for (int i = 0; i < sizeof(PIN_BUTTONS); i++)
        pinMode(PIN_BUTTONS[i], INPUT);
    for (int i = 0; i < sizeof(PIN_LEDS); i++)
        pinMode(PIN_LEDS[i], OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(A0, INPUT);
    initialize();
}

void initialize()
{
    delay(100);
    digitalWrite(13, LOW);
    /*
  for(int x = 0; x < sizeof(letters); x++)
  {
    delay(50);
    char character = 65+x;
    int howLong = 0;

    howLong = lengthOfMorse(letters[x]);
    //length = (letters[x] >> (7)) & 1;
    Serial.print(character);
    Serial.print(" is length ");
    Serial.println(howLong);
  }
 */
    randomSeed(analogRead(A0));
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
    switchPressTester();

    delay(25);
}

void printTimes(int state, int timeMillis)
{

    float shortestUp = upTimes[0];
    for (int i = 0; i < sizeof(upTimes) / sizeof(int); i++) {

        if (upTimes[i] < shortestUp)
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
    else
    {
       addToWhileOff(timeMillis);
    }
    for(int i = 0; i < sizeof(currMorse); i++)
    {
      if(currMorse[i] == 0)
        Serial.print(" ");
        else
        Serial.print(matchToMorse(currMorse[i]));
    }
    Serial.println();
}
char matchToMorse(unsigned char morse)
{
  for (int i = 0; i < sizeof(letters); i++) 
  {
        if (morse == letters[i])
            return  65 + i; 
    }
}
void addToWhileOn(int intTime)
{
    float now = intTime;
    float unit = now / unitLength;
    if (unit < 1.25)
        buttonPressed(COLOR_RED);
    else
        buttonPressed(COLOR_BLUE);
}
void addToWhileOff(int intTime)
{
  float now = intTime;
  float unitt = now / unitLength;
              if (unitt > 7)
              {
                   currMorseIndex++;
                   currMorseIndex++;
                }
               else if (unitt > 2) {
                   currMorseIndex++;
                }
}
void buttonPressed(byte color)
{

    int howLong = lengthOfMorse(currMorse[currMorseIndex]);
    howLong++;
    byte bitToChange = 7 - (howLong + 2);
    byte value = 0;
    if (color == COLOR_BLUE)
        value = 1;
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
       // Serial.print(bitt);
    }
   // Serial.println();
}
void doPhotocellThings()
{
    if (millis() < 1000) {
        if (calibrateCount == 0 || true)
            calibration = analogRead(A0);
        else
            calibration *= (calibrateCount / (calibrateCount + 1));
        calibration += analogRead(A0) / (calibrateCount + 1);
        calibrateCount++;
        return;
    }
    int newPhoto = 0;
    int photoVal = analogRead(A0);
    photoVal -= 75;
    photoVal -= int(calibration);
    //Serial.println(photoVal);
    if (photoVal > 0) {
        newPhoto = 1;
    }
    else {
        newPhoto = 0;
    }
    if (newPhoto == photoOn)
        return;
    digitalWrite(13, HIGH);
    if (newPhoto == 1 && millis() - photoStateChangeTime > 10) {
        photoOn = 1;
        int index = -1;

        for (int i = 0; i < sizeof(downTimes) / sizeof(int); i++) {

            if (!(downTimes[i] > 0)) {

                index = i;
                break;
            }
        }

        if (index >= 0)
            downTimes[index] = millis() - photoStateChangeTime;
        else
            printTimes(0, millis() - photoStateChangeTime);

        photoStateChangeTime = millis();
    }
    else if (newPhoto == 0 && millis() - photoStateChangeTime > 10) {

        photoOn = 0;
        int index = -1;
        for (int i = 0; i < sizeof(upTimes) / sizeof(int); i++) {
            if (upTimes[i] == 0) {
                index = i;
                break;
            }
        }
        if (index >= 0)
            upTimes[index] = millis() - photoStateChangeTime;
        else
            printTimes(1, millis() - photoStateChangeTime);
        photoStateChangeTime = millis();
    }
}
void switchPressTester()
{
    doPhotocellThings();
    long time = millis();
    for (int i = 0; i < sizeof(PIN_BUTTONS); i++) {
        int newState = digitalRead(PIN_BUTTONS[i]);

        /*
    if(redButtonState == LOW && time - redChangeTime > 2000)
    {
      initialize();
      redChangeTime = time;
      redButtonState = newState;
      return;
    }
     */

        if (newState == buttonStates[i])
            continue;

        if (buttonStates[i] == HIGH && time - buttonChangeTimes[i] > DWN_TIME)
            buttonPressed(COLOR_SEQUENCE[i]);

        if (time - buttonChangeTimes[i] < DWN_TIME)
            continue;

        buttonChangeTimes[i] = time;
        buttonStates[i] = newState;
    }
}

