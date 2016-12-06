#include <stdio.h>
#include <avr/io.h>

#include "analog.h"

cAnalog::cAnalog(uint8_t channel) : mChannel(channel)
{
}

uint16_t cAnalog::sample()
{
	if(mChannel > 7)
		return 0;

	uint32_t sum = 0;

	//enable ADC
	ADCSRA = _BV(ADEN) | 7;

	//setup ADC
	ADMUX = 0x40 | mChannel;

	for(uint8_t k = 0; k < 16; k++)
	{
		//Start conversion
		ADCSRA |= _BV(ADSC);

		//wait for conversion
		while(ADCSRA & _BV(ADSC));

		sum += ADC;
	}

	//disable ADC
	ADCSRA = 0;

	return (sum >> 4);
}

cAnalog::~cAnalog()
{
}

