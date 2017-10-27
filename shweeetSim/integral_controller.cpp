#include "integral_controller.h"

IntegralController::IntegralController(cHeater *heater,
                                       cLED *heaterled,
                                       cOutput *freezerRelay,
                                       cLED *freezerled,
                                       cTempProbe *probe) : Controller(25)
{
    mRelay = freezerRelay;
    mProbe = probe;
    mController = new cTempControl(heater, heaterled, freezerRelay, freezerled, probe);
}


bool IntegralController::run(float temperature)
{
    mProbe->setTemp(temperature);

    mController->run();

    emit differentialCooling(mController->isDifferential());
    emit updateFreezerParameters(mController->getFreezerParameters());
    emit updateHeaterParameters(mController->getHeaterParameters());


    return mRelay->getState();
}

IntegralController::~IntegralController()
{
    delete mController;
}
