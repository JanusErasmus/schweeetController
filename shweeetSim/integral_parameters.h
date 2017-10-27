#ifndef INTEGRAL_H
#define INTEGRAL_H
#include <stdint.h>

class IntegralParameters
{
public:
    bool onFlag;
    int16_t offtime;
    int16_t ontime;
    int16_t setOnTime;

    IntegralParameters();
    void reset();
};

#endif // INTEGRAL_H
