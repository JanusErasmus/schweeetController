#include <QPainter>
#include "led.h"

cLED::cLED(QWidget *parent) : QWidget(parent)
{
    mColor = Qt::gray;
}

void cLED::off()
{
    mColor = Qt::gray;
    repaint();
}

void cLED::red()
{
    mColor = Qt::red;
    repaint();
}

void cLED::green()
{
    mColor = Qt::green;
    repaint();
}

void cLED::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);

    QBrush brush(mColor);
    painter.setBrush(brush);

    painter.drawEllipse(0, 0, 20, 20);
}
