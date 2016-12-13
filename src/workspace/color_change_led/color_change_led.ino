

const short LED_PIN_RED = 12
const short LED_PIN_GREEN = 13;
const short LED_PIN_BLUE = 14;

const byte COLOR_NONE = 0;
const byte COLOR_RED = 1;
const byte COLOR_GREEN = 2;
const byte COLOR_BLUE = 3;
const byte COLOR_YELLOW = 4;
const byte COLOR_CYAN = 5;
const byte COLOR_MAGENTA = 6;
const byte COLOR_WHITE = 7;

const long DURATION_LIGHT = 500;
const long DURATION_DARK = 500;

long previousMillis;

byte[] colorSequence;

byte isLit;
int index;

void setup() 
{
  pinMode(LED_PIN_RED, OUTPUT);
  pinMode(LED_PIN_GREEN, OUTPUT);
  pinMode(LED_PIN_BLUE, OUTPUT);
  previousMillis = millis();
  colorSequence = new byte[] {COLOR_RED, COLOR_BLUE, COLOR_YELLOW, COLOR_GREEN, COLOR_WHITE};
  index = 0;
  isLit = 0;
}

void loop() 
{
  if (millis() - previousMillis > getDelay())
  {
    previousMillis = millis();
    isLit = (isLit + 1) % 2;
    if (isLit == 0)
    {
      index++;
      setColor(COLOR_NONE);
    }
    else
    {
      setColor(colorSequence[index]);
    }
  }
}

long getDelay()
{
  if (isLit == 0)
    return DURATION_DARK;
  else
    return DURATION_LIGHT;
}

void setColor(byte color)
{
  if(color == COLOR_NONE)
    tripleSet(0,0,0);
  else if (color == COLOR_RED)
    tripleSet(1,0,0);
  else if (color == COLOR_GREEN)
    tripleSet(0,1,0);
  else if (color == COLOR_BLUE)
    tripleSet(0,0,1);
  else if (color == COLOR_YELLOW)
    tripleSet(1,1,0);
  else if (color == COLOR_CYAN)
    tripleSet(0,1,1);
  else if (color == COLOR_MAGENTA)
    tripleSet(1,0,1);
  else if (color == COLOR_WHITE)
    tripleSet(1,1,1);
}

void tripleSet(byte red, byte green, byte blue)
{
  if(red > 0)
    digitalWrite(LED_PIN_RED, HIGH);
  else
    digitalWrite(LED_PIN_RED, LOW);

  if(green > 0)
    digitalWrite(LED_PIN_GREEN, HIGH);
  else
    digitalWrite(LED_PIN_GREEN, LOW);

  if(blue > 0)
    digitalWrite(LED_PIN_BLUE, HIGH);
  else
    digitalWrite(LED_PIN_BLUE, LOW);
}






