#include <stdio.h>

#include "temp_probe.h"

cTempProbe::cTempProbe(eType type, cAnalog *analog) : mType(type), mAnalog(analog)
{
}

float cTempProbe::getTemp()
{
	double temp = 0;

	switch(mType)
	{
	case LM335:
	{
		float sample = mAnalog->lastSample();
		temp = 500 * (sample/1024.0) - 273.0;
	}
	break;

	case PT100:
		break;
	}

	//printf("%f\n", temp);
	return temp;
}

cTempProbe::~cTempProbe()
{
}

