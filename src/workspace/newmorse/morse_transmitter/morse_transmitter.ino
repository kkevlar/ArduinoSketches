String transmission = "Vector";

const int MILLIS_UNIT = 200;

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
unsigned char morseAtIndex(int index)
{
  transmission = transmission.toUpperCase();
  
  char currChar = transmission.charAt(index);
  if(currChar == ' ')
    return B00000000;
  int letterNum = currChar - 65;
  return letters[letterNum];
}
void setup() 
{
  pinMode(13,OUTPUT);
}
int lengthOfMorse(unsigned char letter)
{
    int howLong = 0;
    for (int y = 0; y < 3; y++) 
    {
        int bitt = (letter >> (7 - y)) & 1;
        int exponent = 2 - y;
        howLong += (round(pow(2, exponent)) * bit);
    }
    return howLong;
}
void loop() 
{
  for(int currLetterIndex = 0; currLetterIndex < transmision.length(); currLetterIndex++)
  {
    unsigned char currMorse = morseAtIndex(currLetterIndex);
    if(currMorse == 0)
      {
        delay(7*MILLIS_UNIT);
        continue;
      }
    int loopCount = lengthOfMorse(currMorse);
    for(int i = 0; i < loopCount; i++)
    {
      int bitt = (letter >> (7 - (i+3))) & 1;
      lightsOn();
      if(bitt == 1)
      delay(MILLIS_UNIT * 3);
      else
      delay(MILLIS_UNIT);
      lightsOff();
      delay(MILLIS_UNIT);
    }
    delay(MILLIS_UNIT*3);
  }
}

void lightsOn()
{
  digitalWrite(13,HIGH);
}
void lightsOff()
{
  digitalWrite(13,LOW);
}

