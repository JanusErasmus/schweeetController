#include <util/delay.h>

#include <terminal.h>
#include "temp_control.h"
#include "seven_segment.h"

#define SAMPLE_PERIOD 10  //set to be 1 second
#define OFF_TIME 60

cTempControl::cTempControl(cOutput *relay, cLED *led, cAnalog *analog) :
			mRelay(relay),
			mLED(led),
			mAnalog(analog)

{
	mEnabled = false;
	mCount = SAMPLE_PERIOD;
	mSetPoint = 80;
}

void cTempControl::setHeater(bool state)
{
	if(state)
	{
		mRelay->set();
		mLED->green();
	}
	else
	{
		mRelay->reset();
		mLED->off();
	}
}

void cTempControl::enable()
{
	mEnabled = true;
}

void cTempControl::disable()
{
	mEnabled = false;
}

void cTempControl::doIntegralControl(float temp)
{
	if(mIntegral.onFlag)
	{
		if(mIntegral.ontime-- > 0)
			return;
		mIntegral.onFlag = false;

		mIntegral.offtime = OFF_TIME;

		setHeater(false);

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
			setHeater(true);
	}
}

void cTempControl::run()
{

	if(mCount--)
		return;
	mCount = SAMPLE_PERIOD;

	float temp = getTemp();
	SevenSegment.setNumber(temp);

	if(!mEnabled)
	{
		mLED->red();
		return;
	}

	if(temp < (mSetPoint - 5))
	{
		setHeater(true);
	}
	else
		doIntegralControl(temp);

}

float cTempControl::getTemp()
{
	double sample = mAnalog->lastSample();
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

