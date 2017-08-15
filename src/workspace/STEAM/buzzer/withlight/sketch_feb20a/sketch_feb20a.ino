/* KEVIN KELLAR - PHOTORESISTOR --> LED - Feb 21, 2017
 *  Changes brigtness of an LED based on light measured by a photoresistor.
 *  If dark, LED will light
 *  If bright, LED will be dark
 */
int ledPin = 3;
int lightPin = A4;

//Min and max light: variables that measure the min and max measured values
//  during the calibration phase.
int minLight = 5000;
int maxLight;

//Dim_curve changes analog LED voltages from a linear to more logarithmic
//  curve so that from dim_curve[128] to dim_curve[255] it looks like
//  a 2x increase in brightness to the human eye.
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

void setup()
{
    pinMode(ledPin, OUTPUT);
}

void loop()
{
    //Calibration phase: blinks the led while the photocell is gathering
    //  information about the darkest and lightest it can be in the
    //  environment.
    if (millis() < 5000) {
        //This block is responsible for blinking the LED every half second
        float tim = millis();
        int num = int(tim / 500.00);
        num = num % 2;
        analogWrite(ledPin, map(num, 0, 1, 0, 255));

        //Measures the light on the photocell and changes the extremes if applicable
        int currLight;
        currLight = analogRead(lightPin);
        if (currLight < minLight)
            minLight = currLight;
        if (currLight > maxLight)
            maxLight = currLight;
        return;
    }

    //Maps the measured photocell value from the extremes measured to 0-255, which
    //  is then again mapped to the human eye brightness index with the dim_curve array
    analogWrite(ledPin, dim_curve[map(analogRead(lightPin), minLight, maxLight, 0, 255)]);
}
