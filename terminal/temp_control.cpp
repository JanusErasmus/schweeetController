#include <util/delay.h>

#include <terminal.h>
#include "temp_control.h"

#define SAMPLE_PERIOD 10  //set to be 1 second
#define OFF_TIME 60

cTempControl::cTempControl(cOutput *relay, cLED *led, cAnalog *analog) :
			mRelay(relay),
			mLED(led),
			mAnalog(analog)

{
	mCount = SAMPLE_PERIOD;
	mSetPoint = 80;
}

void cTempControl::enable()
{
	mRelay->set();
	mLED->green();
}

void cTempControl::disable()
{
	mRelay->reset();
	mLED->off();
}

void cTempControl::doIntegralControl(float temp)
{
	if(mIntegral.onFlag)
	{
		if(mIntegral.ontime-- > 0)
			return;
		mIntegral.onFlag = false;

		mIntegral.offtime = OFF_TIME;

		disable();

	}
	else
	{
		if(mIntegral.offtime-- > 0)
			return;
		mIntegral.onFlag = true;

		//Hysteresis of 0.4C
		if((((float)mSetPoint - 0.2) >= temp) || (temp >= ((float)mSetPoint + 0.2)))
		{
			if(temp > (float)mSetPoint)
				mIntegral.setOnTime--;
			else
				mIntegral.setOnTime++;

			if(mIntegral.setOnTime < 0)
				mIntegral.setOnTime = 0;
		}

		mIntegral.ontime = mIntegral.setOnTime;

		printp("%03.1f - set %ds\n", temp, mIntegral.ontime);

		if(mIntegral.ontime)
			enable();
	}
}

void cTempControl::run()
{
	if(mCount--)
		return;
	mCount = SAMPLE_PERIOD;

	float temp = getTemp();

	if(temp < (mSetPoint - 5))
	{
		enable();
	}
	else
		doIntegralControl(temp);

}

float cTempControl::getTemp()
{
	double sample = mAnalog->sample();
	double temp = 500 * (sample/1024.0) - 273.0;
	return temp;
}

cTempControl::~cTempControl()
{
}

cTempControl::sIntegralVariables::sIntegralVariables()
{
	offtime = 0;
	onFlag = true;
	ontime = 0;
	setOnTime = 0;
}

