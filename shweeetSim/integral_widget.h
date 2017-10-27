#ifndef INTEGRALVARIABLES_H
#define INTEGRALVARIABLES_H
#include <QLabel>
#include <QWidget>

#include "integral_parameters.h"

class IntegralWidget : public QWidget
{
    Q_OBJECT
    QLabel *mOnTime;
    QLabel *offtime;
    QLabel *setOnTime;

public:
    explicit IntegralWidget(QString name, QWidget *parent = 0);

signals:

public slots:
    void updateVariables(IntegralParameters ivar);
    void disable(bool state);
};

#endif // INTEGRALVARIABLES_H
