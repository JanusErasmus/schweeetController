#include "analog_sampler.h"

#define SAMPLE_PERIOD 10  //set to be 1 second

cAnalogSampler::cAnalogSampler(cAnalog **analogInputs, uint8_t count) : mAnalogInputs(analogInputs), mAnalogCount(count)
{
	mTick = SAMPLE_PERIOD;
}

void cAnalogSampler::run()
{
	if(mTick--)
		return;
	mTick = SAMPLE_PERIOD;

	for(uint8_t k = 0; k < mAnalogCount; k++)
	{
		mAnalogInputs[k]->sample();
	}
}

cAnalogSampler::~cAnalogSampler()
{
}

