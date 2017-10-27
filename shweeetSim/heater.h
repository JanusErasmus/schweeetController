#ifndef CHEATER_H
#define CHEATER_H
#include "output.h"

class cHeater
{
    bool mOK;
    bool mOnFlag;

public:
    cHeater();

    void run(){}
    void on();
    void off();
    void reset();

    bool OK(){ return mOK; }

    bool isOn(){ return mOnFlag; }
};

#endif // CHEATER_H
