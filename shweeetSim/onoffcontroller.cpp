#include "onoffcontroller.h"

OnOffController::OnOffController(float setPoint) : Controller(setPoint)
{

}


bool OnOffController::run(float temperature)
{
    if(temperature > (mSetPoint + 5))
        mOnFlag = true;

    if(temperature < (mSetPoint - 5))
       mOnFlag =  false;

    return mOnFlag;
}
