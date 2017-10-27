#ifndef FREEZER_H
#define FREEZER_H
#include <QObject>
#include "controller.h"
#include "output.h"

class Freezer : public QObject
{
    Q_OBJECT

    cOutput *mOutput;

    int mOnCounter;
    Controller *mController;
    float mTemperature;

private slots:

public:
    Freezer(Controller *controller, cOutput *output);

    void run();

signals:
    void temperatureChanged(float temp);

};

#endif // FREEZER_H
