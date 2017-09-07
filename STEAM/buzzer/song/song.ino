/* PIEZO SOUNDER MELODY PLAYER
*
* This project utilizes a piezo element to play a melody by controlling the notes that the
* piezo element plays. Notes are defined using the #define directive. Not all of the notes
* defined are used in this sketch. They are included for future use as desired.
*
*/
#define NOTE_C3 131 // These series of lines define certain notes.
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define WHOLE 1 // Defined multiplier to produce whole notes.
#define HALF 0.5 // Defined multiplier to produce half notes.
#define QUARTER 0.25 // Defined multiplier to produce quarter notes.
#define EIGHTH 0.125 // Defined multiplier to produce eighth notes.
#define SIXTEENTH 0.0625 // Defined multiplier to produce sixteenth notes.
// Defining an integer array having a list of the notes we previous defined. These will play
// 'Oh My Darling Clementine'. The subsequent float array will define the duration of each note.
int tune[] = {
    NOTE_F3, NOTE_F3, NOTE_F3, NOTE_C3,
    NOTE_A3, NOTE_A3, NOTE_A3, NOTE_F3,
    NOTE_F3, NOTE_A3, NOTE_C4, NOTE_C4, NOTE_AS3, NOTE_A3, NOTE_G3,
    NOTE_G3, NOTE_A3, NOTE_AS3, NOTE_AS3,
    NOTE_A3, NOTE_G3, NOTE_A3, NOTE_F3,
    NOTE_F3, NOTE_A3, NOTE_G3, NOTE_C3, NOTE_E3, NOTE_G3, NOTE_F3
};
float duration[] = {
    EIGHTH + SIXTEENTH, SIXTEENTH, QUARTER, QUARTER,
    EIGHTH + SIXTEENTH, SIXTEENTH, QUARTER, QUARTER,
    EIGHTH + SIXTEENTH, SIXTEENTH, QUARTER + EIGHTH, EIGHTH, EIGHTH, EIGHTH, HALF,
    EIGHTH, SIXTEENTH, QUARTER, QUARTER,
    EIGHTH + SIXTEENTH, SIXTEENTH, QUARTER, QUARTER,
    EIGHTH + SIXTEENTH, SIXTEENTH, QUARTER + EIGHTH, EIGHTH, EIGHTH, SIXTEENTH, HALF
};
int len; // Defining an integer variable called length to calculate and store the array length.
void setup()
{
    pinMode(6, OUTPUT); // Set digital Pin 8 to an OUTPUT
    len = sizeof(tune) / sizeof(tune[0]); // Set the integer length to the size of the array. It does
    // this by dividing the # of bytes in the array (they are
    // integers having two bytes each, so 13x2), and then
    // deviding by the number of bytes in the first element
    // of the tune[] array (which is two, an integer).
}
void loop()
{
    for (int x = 0; x < len; x++) { // A loop that iterates the # of times there are notes in melody.
        tone(6, tune[x]); // The piezo is sounded on Pin 8 with the specified note.
        delay(900 * duration[x]); // The delay is adjusted for the length the note needs to play.
        noTone(6); // The piezo is turned off, ready to play the next note.
    }
    delay(500); // The delay before the melody is repeated.
}
