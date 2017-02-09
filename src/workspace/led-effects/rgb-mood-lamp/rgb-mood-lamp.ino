const int PIN_RED = 9;
const int PIN_GRN = 10;
const int PIN_BLU = 11;

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

int brightness = 255;
long stateChangeTime = 0;
int photoOn = 0;
float calibrateCount = 0;
float calibration = 0;
int triggercount = 0;
byte RED_PRESETS = {255};
byte GREEN_PRESETS = {0};
byte BLUE_PRESETS = {0};
void setup()
{

    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GRN, OUTPUT);
    pinMode(PIN_BLU, OUTPUT);
    pinMode(A1, INPUT);
    pinMode(13, OUTPUT);
}
typedef unsigned char  morseBitmask_t; // see also MAX_TIMINGS
const morseBitmask_t MORSE_LETTERS[26] = {
  /* a */ B101,
  /* b */ B11000,
  /* c */ B11010,
  /* d */ B1100,
  /* e */ B10,
  /* f */ B10010,
  /* g */ B1110,
  /* h */ B10000,
  /* i */ B100,
  /* j */ B10111,
  /* k */ B1101,
  /* l */ B10100,
  /* m */ B111,
  /* n */ B110,
  /* o */ B1111,
  /* p */ B10110,
  /* q */ B11101,
  /* r */ B1010,
  /* s */ B1000,
  /* t */ B11,
  /* u */ B1001,
  /* v */ B10001,
  /* w */ B1011,
  /* x */ B11001,
  /* y */ B11011,
  /* z */ B11100,
};
void loop()
{
    boolean dont = false;

    for (int x = 0; x < 3600; x++) {
        int colors[3];

        doPhotocellThings();

        getRGB(int(x / 10), 255, brightness, colors);
        int red = dim_curve[(colors[0])];
        int green = dim_curve[(colors[1])];
        int blue = dim_curve[(colors[2])];
        analogWrite(PIN_RED, red);
        analogWrite(PIN_GRN, green);
        analogWrite(PIN_BLU, blue);
        
        delay(15);
    }
}
void doPhotocellThings()
{
    if (millis() < 2000) {
        if (calibrateCount == 0)
            calibration = analogRead(A1);
        else
            calibration *= (calibrateCount / (calibrateCount + 1));
        calibration += analogRead(A1) / (calibrateCount + 1);
        calibrateCount++;
        return;
    }
    int newPhoto;
    int photoVal = analogRead(A1);
    if (photoVal > calibration + 75)
        newPhoto = 1;
    else
        newPhoto = 0;

    if (newPhoto == photoOn)
        return;

    if (photoOn == 0 && millis() - stateChangeTime > 100) {
        photoOn = 1;
        stateChangeTime = millis();
        triggercount++;
    }
    else if (photoOn == 1 && millis() - stateChangeTime > 100) {
        photoOn = 0;
        stateChangeTime = millis();
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

