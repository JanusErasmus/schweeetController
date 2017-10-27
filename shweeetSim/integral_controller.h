#ifndef INTEGRALCONTROLLER_H
#define INTEGRALCONTROLLER_H
#include "controller.h"
#include "temp_control.h"

class IntegralController : public Controller
{
    Q_OBJECT

    cTempControl *mController;

    cOutput *mRelay;
    cTempProbe *mProbe;

public:
    IntegralController(cHeater*, cLED*, cOutput*, cLED*, cTempProbe*);
    virtual ~IntegralController();

    bool run(float temperature);


signals:
    void differentialCooling(bool state);
    void updateFreezerParameters(IntegralParameters ivar);
    void updateHeaterParameters(IntegralParameters ivar);
};

#endif // INTEGRALCONTROLLER_H
