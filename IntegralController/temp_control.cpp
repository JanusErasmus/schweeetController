#include <util/delay.h>

#include <terminal.h>
#include "temp_control.h"
#include "nvm.h"

#define SAMPLE_PERIOD 10  //set to be 1 second
#define HEATER_OFF_TIME 60

#define FREEZER_OFF_TIME 300
#define FREEZER_MIN_TIME 600
#define FREEZER_INC_TIME 60

cTempControl::cTempControl(cHeater *heater, cLED *heaterled, cOutput *freezerRelay, cLED *freezerled, cTempProbe *probe) :
			mHeater(heater),
			mHeaterLED(heaterled),
			mFreezerRelay(freezerRelay),
			mFreezerLED(freezerled),
			mProbe(probe)

{
	mLEDflag = false;
	mStatus = STOPPED;
	mCount = 3;
	mSetPoint = eeprom_read_byte(ADDRES_SETPOINT);

	mFreezerIntegral.onFlag = false;

	bool started = eeprom_read_byte(ADDRES_CONTROLLING);
	if(started)
	{
		mStatus = IDLE;
	}
}

void cTempControl::setHeater(bool state)
{
	if(state)
	{
		mHeater->on();
		mStatus = HEATING;
	}
	else
	{
		mHeater->off();

		if(mStatus != COOLING)
			mStatus = IDLE;
	}

	if(!mHeater->OK())
	{
		mStatus = FAILURE;
	}
}

void cTempControl::setFreezer(bool state)
{
	if(state)
	{
		mFreezerRelay->set();
		mStatus = COOLING;
	}
	else
	{
		mFreezerRelay->reset();

		if(mStatus != HEATING)
			mStatus = IDLE;
	}
}

void cTempControl::start()
{
	eeprom_write_byte(ADDRES_CONTROLLING, true);
	mStatus = IDLE;
	setHeater(false);
	setFreezer(false);
}

void cTempControl::stop()
{
	eeprom_write_byte(ADDRES_CONTROLLING, false);
	mHeater->reset();
	mStatus = STOPPED;

	mHeaterIntegral.reset();
	mFreezerIntegral.reset();
}

void cTempControl::doIntegralHeating(float temp)
{
	if(mHeaterIntegral.onFlag)
	{
		if(mHeaterIntegral.ontime-- > 0)
			return;
		mHeaterIntegral.onFlag = false;

		mHeaterIntegral.offtime = HEATER_OFF_TIME;

		setHeater(false);
	}
	else
	{
		if(mHeaterIntegral.offtime-- > 0)
			return;
		mHeaterIntegral.onFlag = true;

		//Hysteresis of 0.4C
		if((((float)mSetPoint - 0.2) >= temp) || (temp >= ((float)mSetPoint + 0.2)))
		{
			if(temp > (float)mSetPoint)
				mHeaterIntegral.setOnTime--;
			else
				mHeaterIntegral.setOnTime++;

			if(mHeaterIntegral.setOnTime < 0)
				mHeaterIntegral.setOnTime = 0;
		}

		mHeaterIntegral.ontime = mHeaterIntegral.setOnTime;

		printp("Heater %03.1f - set %ds\n", temp, mHeaterIntegral.ontime);

		if(mHeaterIntegral.ontime)
		{
			setHeater(true);
		}
	}
}

void cTempControl::doIntegralCooling(float temp)
{
	if(mFreezerIntegral.onFlag)
	{
		if(mFreezerIntegral.ontime-- > 0)
			return;
		mFreezerIntegral.onFlag = false;

		mFreezerIntegral.offtime = FREEZER_OFF_TIME;

		setFreezer(false);
	}
	else
	{
		if(mFreezerIntegral.offtime-- > 0)
			return;
		mFreezerIntegral.onFlag = true;

		//Hysteresis of 2C
		if((((float)mSetPoint - 1) <= temp) || (temp <= ((float)mSetPoint + 1)))
		{
			if(temp < (float)mSetPoint)
				mFreezerIntegral.setOnTime -= 60;
			else
			{
				//start with minimim of 10m on
				if(mFreezerIntegral.setOnTime == 0)
					mFreezerIntegral.setOnTime = FREEZER_MIN_TIME;

				mFreezerIntegral.setOnTime += FREEZER_INC_TIME;
			}

			if(mFreezerIntegral.setOnTime < 0)
				mFreezerIntegral.setOnTime = 0;
		}

		mFreezerIntegral.ontime = mFreezerIntegral.setOnTime;

		printp("Freezer %03.1f - set %ds\n", temp, mFreezerIntegral.ontime);

		if(mFreezerIntegral.ontime)
		{
			setFreezer(true);
		}
	}
}

void cTempControl::run()
{
	switch(mStatus)
	{
	case STOPPED:
	{
		mHeaterLED->off();
	}
	return;
	case HEATING:
	{
		if(mLEDflag)
		{
			mLEDflag = false;
			mHeaterLED->off();
		}
		else
		{
			mLEDflag = true;
			mHeaterLED->green();
		}
	}
	break;
	case IDLE:
	{
		mHeaterLED->green();
		mFreezerLED->green();
	}
	break;
	case COOLING:
		if(mLEDflag)
		{
			mLEDflag = false;
			mFreezerLED->off();
		}
		else
		{
			mLEDflag = true;
			mFreezerLED->green();
		}
		break;
	case FAILURE:
	{
		if(mLEDflag)
		{
			mLEDflag = false;
			mHeaterLED->off();
		}
		else
		{
			mLEDflag = true;
			mHeaterLED->red();
		}
	}
	break;
	}

	if(mCount--)
		return;
	mCount = SAMPLE_PERIOD;

	uint8_t differentialControl = false;

	float temp = mProbe->getTemp();
	if(temp < ((float)mSetPoint - 5.0))
	{
		setHeater(true);
		differentialControl = true;
	}

	if(temp > ((float)mSetPoint + 3.0))
	{
		setFreezer(true);
		differentialControl = true;
	}

	if(differentialControl)
		return;


	//do NOT cool while we are still heating
	if(!mHeaterIntegral.setOnTime)
		doIntegralCooling(temp);

	//do NOT heat while we are still cooling
	if(!mFreezerIntegral.setOnTime)
		doIntegralHeating(temp);


}



cTempControl::~cTempControl()
{
}

cTempControl::sIntegralVariables::sIntegralVariables()
{
	reset();
}

void cTempControl::sIntegralVariables::reset()
{
	offtime = 0;
	onFlag = true;
	ontime = 0;
	setOnTime = 0;
}

