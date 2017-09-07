/*
  Analog input, analog output, serial output

 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.

 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground

 created 29 Dec. 2008
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A3;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
int cumquat = 0;
int count = 0;
int hightest = 0;
void setup() {
  pinMode(A3,INPUT);
  pinMode(A2,OUTPUT);
  pinMode(A1,OUTPUT);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,LOW);
  pinMode(9,OUTPUT);
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  delay(200);
  cumquat = analogRead(analogInPin);
}

void loop() 
{
  /*
  // read the analog in value:
  for(int i = 0 ; i < 100; i++)
  {
  sensorValue = max(analogRead(analogInPin),sensorValue);
 // delay();
  }
  */
  sensorValue = analogRead(analogInPin);
  Serial.println(sensorValue - cumquat);
  int mapp = map(sensorValue - cumquat,0,400,0,255);
  analogWrite(9,mapp);
}
