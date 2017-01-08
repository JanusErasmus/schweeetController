#include "heater.h"

#include <stdio.h>

#define RESPONSE_TIME 600  //set to be 60 seconds

cHeater::cHeater(cOutput *heaterRelay, cTempProbe *probe) :
		mProbe(probe),
		mHeaterRelay(heaterRelay),
		mTemperature(-999),
		mSampleCount(-1),
		mOK(true)
{
	mHeaterRelay->reset();
}

void cHeater::on()
{
	mHeaterRelay->set();

	//check that temperature of heater rises after the heater response time
	if(mSampleCount < 0)
		mSampleCount = 0;
}

void cHeater::off()
{
	mHeaterRelay->reset();
}

void cHeater::reset()
{
	mOK = true;
	mTemperature = -999;
	mSampleCount = -1;
}

void cHeater::run()
{
	if(mSampleCount >= 0)
	{
		if(mTemperature == -999)
			mTemperature = mProbe->getTemp();

		if(++mSampleCount > RESPONSE_TIME)
		{
			float temp = mProbe->getTemp();
			if(temp < (mTemperature - 0.1))
			{
				mOK = false;
				mHeaterRelay->reset();
			}

			//stop checking heater
			mTemperature = -999;
			mSampleCount = -1;
		}
	}
}

cHeater::~cHeater()
{
}

