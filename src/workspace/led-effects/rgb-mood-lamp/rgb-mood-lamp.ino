const int PIN_RED = 9;
const int PIN_GRN = 8;
const int PIN_BLU = 10;

float RGB1[3];
float RGB2[3];
float INC[3];
void setup()
{
    Serial.begin(9600);
    randomSeed(analogRead(0));

    RGB1[0] = 0;
    RGB1[1] = 0;
    RGB1[2] = 0;
    RGB2[0] = random(256);
    RGB2[1] = random(256);
    RGB2[2] = random(256);
}
void loop()
{
    randomSeed(analogRead(0));
    for (int x = 0; x < 3; x++) 
    {
        INC[x] = (RGB1[x] - RGB2[x]);
    }
    for (int x = 0; x < 256; x++)
    {
        int red = int(RGB1[0]);
        int green = int(RGB1[1]);
        int blue = int(RGB1[2]);
        analogWrite(PIN_RED, red);
        analogWrite(PIN_GRN, green);
        analogWrite(PIN_BLU, blue);
        delay(100);
        RGB1[0] -= INC[0];
        RGB1[1] -= INC[1];
        RGB1[2] -= INC[2];
    }
    for (int x = 0; x < 3; x++) 
    {
        RGB2[x] = random(556) - 300;
        RGB2[x] = constrain(RGB2[x], 0, 255);
        delay(1000);
    }
}
