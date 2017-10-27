#include <QDebug>
#include "heater.h"

cHeater::cHeater()
{
    mOK = true;
    mOnFlag = false;
}


void cHeater::on()
{
    mOnFlag = true;
    qDebug() << "Heater ON";
}

void cHeater::off()
{
    mOnFlag = false;
    qDebug() << "Heater OFF";
}

void cHeater::reset()
{
    mOnFlag = false;
}
