#include <math.h>
#include <QDebug>

#include "Freezer.h"

Freezer::Freezer(Controller *controller, cOutput *output) : QObject(0)
{
    mOutput = output;
    mOnCounter = 0;
    mTemperature = 5;
    mController = controller;
}

void Freezer::run()
{
    bool onFlag = mController->run(mTemperature);

    if(onFlag)
    {
        mOutput->set();

        mTemperature = (-10.0 * 0.002) + (0.998001998667333 * mTemperature);
    }
    else
    {
        mOutput->reset();

        mOnCounter = 0;
        mTemperature = (25.0 * 0.0000970873786407767) + (0.999902917334186 * mTemperature);
    }
    //qDebug() << mTemperature;

    emit temperatureChanged(mTemperature);
}
