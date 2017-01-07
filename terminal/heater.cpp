#include "heater.h"


cHeater::cHeater(cOutput *heaterRelay) : mHeaterRelay(heaterRelay), mTemperature(DISABLED_TEMPERATURE)
{
}

bool cHeater::on(float temperature)
{
	mHeaterRelay->set();

	if(mTemperature == DISABLED_TEMPERATURE)
	{
		mTemperature = temperature;
		return true;
	}

	if(mTemperature > (temperature + 1.0))
		return false;

	return true;
}

void cHeater::off()
{
	mHeaterRelay->reset();

	mTemperature = DISABLED_TEMPERATURE;
}

cHeater::~cHeater()
{
}

