#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>

class Controller : public QObject
{
    Q_OBJECT

protected:
    bool mOnFlag;
    float mSetPoint;

public:
    Controller(float setPoint);

    virtual bool run(float temperature) = 0;
};

#endif // CONTROLLER_H
