#include "integral_parameters.h"

IntegralParameters::IntegralParameters()
{
    reset();
}

void IntegralParameters::reset()
{
    offtime = 0;
    onFlag = true;
    ontime = 0;
    setOnTime = 0;
}
