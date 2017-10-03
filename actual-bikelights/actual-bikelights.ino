#define PIN_RED 5
#define PIN_GRN 6
#define PIN_BLU 9
#define PIN_BUTTON 3

const byte dim_curve[] = {
    0, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6,
    6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8,
    8, 8, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 11, 11, 11,
    11, 11, 12, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 15,
    15, 15, 16, 16, 16, 16, 17, 17, 17, 18, 18, 18, 19, 19, 19, 20,
    20, 20, 21, 21, 22, 22, 22, 23, 23, 24, 24, 25, 25, 25, 26, 26,
    27, 27, 28, 28, 29, 29, 30, 30, 31, 32, 32, 33, 33, 34, 35, 35,
    36, 36, 37, 38, 38, 39, 40, 40, 41, 42, 43, 43, 44, 45, 46, 47,
    48, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62,
    63, 64, 65, 66, 68, 69, 70, 71, 73, 74, 75, 76, 78, 79, 81, 82,
    83, 85, 86, 88, 90, 91, 93, 94, 96, 98, 99, 101, 103, 105, 107, 109,
    110, 112, 114, 116, 118, 121, 123, 125, 127, 129, 132, 134, 136, 139, 141, 144,
    146, 149, 151, 154, 157, 159, 162, 165, 168, 171, 174, 177, 180, 183, 186, 190,
    193, 196, 200, 203, 207, 211, 214, 218, 222, 226, 230, 234, 238, 242, 248, 255,
};

int state = 5;
long offset = 0;
int frozenHue = -1;
int colors[3];
int buttonState = LOW;
long bStateChangeMillis = 0;
bool allowStateIncrease = true;

void setup()
{
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GRN, OUTPUT);
    pinMode(PIN_BLU, OUTPUT);
    pinMode(PIN_BUTTON, INPUT_PULLUP);

    Serial.begin(9600);
}

int getHueFromMillis()
{
    return (millis()-offset/10)%360
}

void setLedsByHSV(int hue, int sat, int val)
{
   getRGB(hue, sat, val, colors);
   int red = dim_curve[(colors[0])];
   int green = dim_curve[(colors[1])];
   int blue = dim_curve[(colors[2])];
   analogWrite(PIN_RED, red);
   analogWrite(PIN_GRN, green);
   analogWrite(PIN_BLU, blue); 
}

void setLedsByHue(int hue)
{
    setLedsByHSV(hue, 255, 255);
}

void loop()
{
    /*
    for (int x = 0; x < 3600; x++) 
    {
        int colors[3];

        getRGB(int(x / 10), 255, 255, colors);
        int red = dim_curve[(colors[0])];
        int green = dim_curve[(colors[1])];
        int blue = dim_curve[(colors[2])];
        analogWrite(PIN_RED, red);
        analogWrite(PIN_GRN, green);
        analogWrite(PIN_BLU, blue);
        
        delay(5);
    }
    */

    if(state == 0)
        setLedsByHue(getHueFromMillis());
    if (state != 1)
        frozenHue = -1;
    else
        if (frozenHue == -1)
            frozenHue == getHueFromMillis();
        else        
            setLedsByHue(frozenHue);
    if (state == 2)
        if ((millis() / 200) % 2 == 0)
            setLedsByHSV(frozenHue, 255, 255);
        else
            setLedsByHSV(frozenHue, 255, 0);
    if (state == 3)
        setLedsByHSV(0,0,255);
    if (state == 4)
        if ((millis() / 200) % 2 == 0)
            setLedsByHSV(frozenHue, 0, 255);
        else
            setLedsByHSV(frozenHue, 0, 0);
    if (state == 5)
        setLedsByHSV(0,0,0);

    int nState = digitalRead(PIN_BUTTON);
    if (nState != buttonState)
    {
        buttonState = nState;
        bStateChangeMillis = millis();
    }
    if(millis() - bStateChangeMillis > 100 &&
        buttonState == LOW &&
        && allowStateIncrease)
    {
        state = (state+1)%6;
        allowStateIncrease = false;
    }
    if(millis() - bStateChangeMillis > 100 &&
        buttonState == HIGH)
    {
         allowStateIncrease = true;
    }

}

void getRGB(int hue, int sat, int val, int colors[3])
{
    /* convert hue, saturation and brightness ( HSB/HSV ) to RGB
     The dim_curve is used only on brightness/value and on saturation (inverted).
     This looks the most natural.      
  */

    val = dim_curve[val];
    sat = 255 - dim_curve[255 - sat];

    int r;
    int g;
    int b;
    int base;

    if (sat == 0) { // Acromatic color (gray). Hue doesn't mind.
        colors[0] = val;
        colors[1] = val;
        colors[2] = val;
    }
    else {

        base = ((255 - sat) * val) >> 8;

        switch (hue / 60) {
        case 0:
            r = val;
            g = (((val - base) * hue) / 60) + base;
            b = base;
            break;

        case 1:
            r = (((val - base) * (60 - (hue % 60))) / 60) + base;
            g = val;
            b = base;
            break;

        case 2:
            r = base;
            g = val;
            b = (((val - base) * (hue % 60)) / 60) + base;
            break;

        case 3:
            r = base;
            g = (((val - base) * (60 - (hue % 60))) / 60) + base;
            b = val;
            break;

        case 4:
            r = (((val - base) * (hue % 60)) / 60) + base;
            g = base;
            b = val;
            break;

        case 5:
            r = val;
            g = base;
            b = (((val - base) * (60 - (hue % 60))) / 60) + base;
            break;
        }

        colors[0] = r;
        colors[1] = g;
        colors[2] = b;
    }
}

