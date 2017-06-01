#include "pitches.h";

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

int hue = 0;
#include <Servo.h> // Loads the Arduino Servo Library.
Servo servo1; // Create a servo object named servo1.

void setup()
{

  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GRN, OUTPUT);
  pinMode(PIN_BLU, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(13, OUTPUT);
  pinMode(12,OUTPUT);
 // pinMode(5,OUTPUT);
  servo1.attach(A5); //Servo1 on pin5
 // Serial.begin(9600);
 
 servo1.write(150);
 //digitalWrite(A5,LOW);
 dingDong();
}

void loop()
{
  boolean dont = false;

   

    doPhotocellThings();

   hue = (millis() / (20000/360)) % 360;
    int saturation = 255;
   int brightness =  ((millis()/125) %2)*255;
     int colors[3];
    getRGB(hue, saturation, brightness, colors);
    int red = dim_curve[(colors[0])];
    int green = dim_curve[(colors[1])];
    int blue = dim_curve[(colors[2])];
    analogWrite(PIN_RED, red);
    analogWrite(PIN_GRN, green);
    analogWrite(PIN_BLU, blue);

    delay(5);

 
}
void doPhotocellThings()
{
  
}
void dingDong()
{
   tone(12,NOTE_DS5,750);
  delay(750);
  tone(12,NOTE_B4,750);
  delay(750);
}


void getRGB(int hue, int sat, int bright, int colors[3])
{
 
  bright = dim_curve[bright];

  int r;
  int g;
  int b;
  int base;

  if (sat == 0) { // Acromatic color (gray). Hue doesn't mind.
    colors[0] = bright;
    colors[1] = bright;
    colors[2] = bright;
  }
  else {

    base = ((255 - sat) * bright) >> 8;

    switch (hue / 60) {
      case 0:
        r = bright;
        g = (((bright - base) * hue) / 60) + base;
        b = base;
        break;

      case 1:
        r = (((bright - base) * (60 - (hue % 60))) / 60) + base;
        g = bright;
        b = base;
        break;

      case 2:
        r = base;
        g = bright;
        b = (((bright - base) * (hue % 60)) / 60) + base;
        break;

      case 3:
        r = base;
        g = (((bright - base) * (60 - (hue % 60))) / 60) + base;
        b = bright;
        break;

      case 4:
        r = (((bright - base) * (hue % 60)) / 60) + base;
        g = base;
        b = bright;
        break;

      case 5:
        r = bright;
        g = base;
        b = (((bright - base) * (60 - (hue % 60))) / 60) + base;
        break;
    }

    colors[0] = r;
    colors[1] = g;
    colors[2] = b;
  }
}

