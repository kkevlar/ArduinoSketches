
#include "pitches.h"

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

int melody[] = {
  NOTE_A2,
  NOTE_A2,
  NOTE_C2,
  NOTE_E2,
  NOTE_F2,
  NOTE_C2,
  NOTE_E2,
  NOTE_F2,
  NOTE_C2,
  NOTE_E2,
  NOTE_F2,
  NOTE_C2,
  NOTE_E2,
  NOTE_A3,
  NOTE_A3,
  0,
  NOTE_A3,
  NOTE_A3,
  0,
  NOTE_A3,
  NOTE_A3,
  0,
  NOTE_A2,
  NOTE_E3,
  NOTE_D3,
  NOTE_E3,
  NOTE_G3,
  NOTE_E3,
  NOTE_E3,
  NOTE_E3
};

void setup() 
{
  pinMode(3,OUTPUT);
  pinMode(9,OUTPUT);
  /*
  for (int thisNote = 0; thisNote < sizeof(melody)/2; thisNote++) 
  {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 250;
    tone(3, melody[thisNote]);
    if(melody[thisNote]!=0)
      digitalWrite(9,HIGH);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    if(thisNote < 21)
      delay(250);
    else
      delay(600);
    // stop the tone playing:
    digitalWrite(9,LOW);
    if(sizeof(melody)/2 > thisNote+1 && melody[thisNote] != melody[thisNote+1])
      noTone(3);
    delay(20);
  }
  delay(500);
  noTone(3);
  */
}
int count = 0;
long changeTime = 0;
long setTime = 0;
int note;
void loop() 
{
  if(millis() > changeTime)
  {
    if(count >= sizeof(melody)/2)
      note = 0;
    else
      note = melody[count];
    do
    { 
      count++;
      if(count < 21)
      changeTime  += 250;
      else
      changeTime  += 600;
    }
    while(count < sizeof(melody)/2 && melody[count] == note);
  

    if(note != 0)
      tone(3,note);
    else
      noTone(3);
    setTime = millis();
  }

  int logic = map(millis(),setTime,changeTime,255,0);
  if(note == 0)
    logic = 0;
  analogWrite(9, dim_curve[logic]);
}
