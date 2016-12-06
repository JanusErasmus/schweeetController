#include <avr/io.h>
#include <avr/interrupt.h>

#include "terminal.h"
#include "button.h"

cButtons::cButtons()
{
	mPressed = 0;
	PCICR = 1 << PCIE1;
	PCMSK1 = _BV(PCINT11) | _BV(PCINT12) | _BV(PCINT13) | _BV(PCINT14) | _BV(PCINT15);
}

void cButtons::handleButton(uint8_t buttons)
{
	if(buttons & 0x04)
		mPressed = 11;
	else if(buttons & 0x08)
		mPressed = 12;
	else if(buttons & 0x10)
		mPressed = 13;
	else if(buttons & 0x20)
		mPressed = 14;
	else if(buttons & 0x40)
		mPressed = 15;
}

void cButtons::run()
{

	switch(mPressed)
	{
	case 11:
		printp("UP\n");
		break;
	case 12:
		printp("DOWN\n");
		break;
	case 13:
		printp("LEFT\n");
		break;
	case 14:
		printp("RIGHT\n");
		break;
	case 15:
		printp("ENTER\n");
		break;
	default:
		break;
	}

	mPressed = 0;
}

cButtons::~cButtons()
{
}


ISR(PCINT1_vect)
{
	uint8_t pins = ~PINJ;

	Buttons.handleButton(pins);
}

cButtons Buttons;
