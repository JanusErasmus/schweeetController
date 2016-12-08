#include "input.h"

cInput::cInput(uint8_t pin_definition) : cPort(pin_definition)
{
	clearDDRn();
}

bool cInput::get()
{
	 volatile uint8_t *port = PINn_reg();

	 if( *port & (1 << (mPinDefinition & 0x0F)))
		 return true;

	 return false;
}

cInput::~cInput()
{
}

