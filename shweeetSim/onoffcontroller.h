#ifndef ONOFFCONTROLLER_H
#define ONOFFCONTROLLER_H
#include "controller.h"

class OnOffController : public Controller
{
public:
    OnOffController(float setPoint);

    bool run(float temperature);
};

#endif // ONOFFCONTROLLER_H
