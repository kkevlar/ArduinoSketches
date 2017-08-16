/*
  Melody

 Plays a melody

 circuit:
 * 8-ohm speaker on digital pin 8

 created 21 Jan 2010
 modified 30 Aug 2011
 by Tom Igoe

This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Tone

 */
#include "pitches.h"

// notes in the melody:
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
};

void setup() {
  pinMode(9,OUTPUT);
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < sizeof(melody)/2; thisNote++) {

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
}

void loop() {
  // no need to repeat the melody.
}
