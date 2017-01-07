#include "heater.h"

#include <stdio.h>

cHeater::cHeater(cOutput *heaterRelay) : mHeaterRelay(heaterRelay), mTemperature(DISABLED_TEMPERATURE)
{
}

bool cHeater::on(float temperature)
{
	mHeaterRelay->set();

	if(temperature == DISABLED_TEMPERATURE)
		return true;

	return checkHeating(temperature);
}

bool cHeater::off(float temperature)
{
	mHeaterRelay->reset();

	if(temperature == DISABLED_TEMPERATURE)
	{
		mTemperature = DISABLED_TEMPERATURE;
		return true;
	}

	return checkHeating(temperature);
}

bool cHeater::checkHeating(float temp)
{
	if(mTemperature == DISABLED_TEMPERATURE)
	{
		mTemperature = temp;
		return true;
	}

	if(temp > mTemperature)
	{
		mTemperature = temp;
		return true;
	}

	if(mTemperature > (temp + 1.0))
		return false;

	return true;
}

cHeater::~cHeater()
{
}

