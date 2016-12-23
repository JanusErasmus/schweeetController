#include "temp_probe.h"

cTempProbe::cTempProbe(eType type, cAnalog *analog) : mType(type), mAnalog(analog)
{
}

double cTempProbe::getTemp()
{
	double temp = 0;

	switch(mType)
	{
	case LM335:
	{
		double sample = mAnalog->lastSample();
		temp = 500 * (sample/1024.0) - 273.0;
	}
	break;

	case PT100:
		break;
	}

	return temp;
}

cTempProbe::~cTempProbe()
{
}

