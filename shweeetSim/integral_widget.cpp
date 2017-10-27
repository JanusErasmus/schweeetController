#include <QVBoxLayout>
#include <QHBoxLayout>

#include "integral_widget.h"

IntegralWidget::IntegralWidget(QString name, QWidget *parent) : QWidget(parent)
{

    mOnTime = new QLabel();
    offtime = new QLabel();
    setOnTime = new QLabel();

    QVBoxLayout *layout = new QVBoxLayout();

    QLabel *label = new QLabel(name + QString(" Integral Parameters"));
    label->setAlignment(Qt::AlignHCenter);
    layout->addWidget(label);

    QHBoxLayout *itemLayout = new QHBoxLayout();
    label = new QLabel("Set On time:");
    itemLayout->addWidget(label);
    itemLayout->addWidget(setOnTime);
    layout->addLayout(itemLayout);

    itemLayout = new QHBoxLayout();
    label = new QLabel("On Time:");
    itemLayout->addWidget(label);
    itemLayout->addWidget(mOnTime);
    layout->addLayout(itemLayout);

    itemLayout = new QHBoxLayout();
    label = new QLabel("Off time:");
    itemLayout->addWidget(label);
    itemLayout->addWidget(offtime);
    layout->addLayout(itemLayout);



    setLayout(layout);
}

void IntegralWidget::disable(bool state)
{
    setEnabled(!state);
}

void IntegralWidget::updateVariables(IntegralParameters ivar)
{
    QString string;

    string.setNum(ivar.setOnTime);
    setOnTime->setText(string);

    string.setNum(ivar.ontime);
    mOnTime->setText(string);

    string.setNum(ivar.offtime);
    offtime->setText(string);
}
