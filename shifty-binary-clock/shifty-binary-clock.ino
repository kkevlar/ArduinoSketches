
#define OE_IS_CONTROLLED 0

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) ||defined(__AVR_ATmega328P__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	#define ARDUINOZ 1
	#warning "ARDUINOZ defined"
#endif

#if defined(__linux) || defined(_WIN32) || defined(__CYGWIN__)
	#define ARDUINOZ 0
	#warning "PC defined"
	#include <stdio.h>
	#include <stdint.h>
#endif

#define PIN_DATA 2
#define PIN_CLOCK 3
#define PIN_LATCH 4

#if (OE_IS_CONTROLLED)
	#define PIN_OE 5
#endif

long offset = 0;
uint8_t secs = 0;
uint8_t minutes = 0;
uint8_t hours = 0;

void rsPins()
{
	#if (ARDUINOZ)
		digitalWrite(PIN_CLOCK,LOW);
		digitalWrite(PIN_DATA,LOW);
		digitalWrite(PIN_LATCH, LOW);
	#endif
	#if !(ARDUINOZ)
		printf("\n");
	#endif
}

#if (ARDUINOZ)
	void setup()
	{
		pinMode(PIN_DATA, OUTPUT);
		pinMode(PIN_CLOCK, OUTPUT);
		pinMode(PIN_LATCH, OUTPUT);
		#if (OE_IS_CONTROLLED)
			pinMode(PIN_OE, OUTPUT);
			digitalWrite(PIN_OE, LOW); //low -> enabled
		#endif
		rsPins();
	}
#endif

#if !(ARDUINOZ)
	#include "cpTime.h"
	long millis()
	{
		return cpMillis();
	}
#endif


int getCurrSecs()
{
  
	return (((millis()+offset))/1000 % 60);
}

void writeReg(bool writeVal)
{
	#if (ARDUINOZ)
		digitalWrite(PIN_CLOCK, LOW);
		digitalWrite(PIN_DATA, writeVal);
		delayMicroseconds(5);
		digitalWrite(PIN_CLOCK, HIGH);
		delayMicroseconds(5);
		digitalWrite(PIN_DATA, LOW);
		digitalWrite(PIN_CLOCK,LOW);
	#endif
	#if !(ARDUINOZ)
		printf("%d", writeVal);
	#endif
}

void loop()
{
	long currSecs = getCurrSecs();

	if(currSecs < secs)
	{
		if(minutes == 59)
		{
			minutes = 0;
			hours++;
		}
		else
			minutes++;
	}

	if(currSecs != secs)
	{
		rsPins();

		secs = (uint8_t) currSecs;

		for(int i = 0; i < 6; i++)
			writeReg((secs >> i) & 0x01);
		for(int i = 0; i < 6; i++)
			writeReg((minutes >> i) & 0x01);
		for(int i = 0; i < 5; i++)
			writeReg((hours >> i) & 0x01);

		#if (ARDUINOZ)
			digitalWrite(PIN_LATCH, HIGH);
			delay(10);
			digitalWrite(PIN_LATCH, LOW);
		#endif
	}
}

#if !(ARDUINOZ)
	int main()
	{
		while(true)
		{
			loop();
		}
	}
#endif
