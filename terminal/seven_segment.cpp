#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "terminal.h"
#include "seven_segment.h"

//#define DELAY_US 1

#ifdef DELAY_US
#define BIT_DELAY _delay_us(DELAY_US);
#else
#define BIT_DELAY
#endif

cSevenSegment SevenSegment;

const uint8_t segmentValues[] PROGMEM =
{
		0xDB,	//0
		0x12,   //1
		0x8F,   //2
		0x1F,   //3
		0x56,   //4
		0x5D,   //5
		0xDD,   //6
		0x5A,   //7
		0xDF,   //8
		0x5F,   //9
		0x04	//'-'
};

cSevenSegment::cSevenSegment()
{
	mPoint = 0xFF;
	memset(mDigits,8,4);

	DDRH = 0xFF;
	PORTH |= 0x00;

	TIMSK1 = _BV(TOIE1);
	TCCR1B = 0x01;
}

void cSevenSegment::run()
{
	static uint8_t k = 0;
	PORTH &= 0x0F;
	BIT_DELAY
	putDigit(mDigits[k], (mPoint == k));
	BIT_DELAY

	bool showDigit = false;
	switch(k)
	{
	case 3:
		if(mDigits[3])
			showDigit = true;
		break;
	case 2:
		if(mDigits[3] || mDigits[2])
			showDigit = true;
		break;
	case 1:
		if(mDigits[3] || mDigits[2] || mDigits[1])
			showDigit = true;

		if(mPoint == 1)
			showDigit = true;
		break;
	default:
		showDigit = true;
		break;
	}

	if(showDigit)
		PORTH |= (1 << (k + 4));

	if(k++ >= 3)
		k = 0;

}

void cSevenSegment::setNumber(float number)
{
	uint16_t digits = number;
	if(number < -999.9)
		return;

	if(number < -99.9)
	{
		digits = number * (-1);
		mPoint = 0;
	}
	else if(number < 0)
	{
		digits = number * (-10);
		mPoint = 1;
	}
	else if(number > 999.9)
	{
		mPoint = 0;
	}
	else //if(number > 99)
	{
		mPoint = 1;
		digits = number * 10;
	}
//	else if(number > 9)
//	{
//		mPoint = 2;
//		digits = number * 100;
//	}
//	else
//	{
//		mPoint = 3;
//		digits = number * 1000;
//	}

//	printp("number %0.2f, digits %d\n", number, digits);

	if(number >= 0)
	{
		mDigits[3] = digits / 1000;
	}
	else
	{
		mDigits[3] = 10;
	}

	digits %= 1000;
	mDigits[2] = digits / 100;
	digits %= 100;
	mDigits[1] = digits / 10;
	digits %= 10;
	mDigits[0] = digits;
}


void cSevenSegment::sendByte(uint8_t byte)
{
	for(uint8_t k = 0; k < 8; k++)
	{
		//set serial data bit to correct value
		if(byte & (1 << k))
			PORTH |= 0x01;
		else
			PORTH &= 0xFE;

		//clock set bit into serial register
		BIT_DELAY
		PORTH |= 0x08;
		BIT_DELAY
		PORTH &= 0xF7;
	}

	//latch register to output pins
	BIT_DELAY
	PORTH |= 0x04;
	BIT_DELAY
	PORTH &= 0xFB;
}

void cSevenSegment::putDigit(uint8_t index, bool point)
{
	if(index > 10)
		return;

	if(point)
		sendByte(pgm_read_byte(&segmentValues[index]) | 0x20);
	else
		sendByte(pgm_read_byte(&segmentValues[index]));
}

cSevenSegment::~cSevenSegment()
{
}

ISR(TIMER1_OVF_vect)
{
	SevenSegment.run();
}

