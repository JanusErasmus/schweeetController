#ifndef LED_H
#define LED_H
#include <QWidget>

class cLED : public QWidget
{
    Q_OBJECT

    Qt::GlobalColor mColor;

public:
    cLED(QWidget *parent = 0);


    void paintEvent(QPaintEvent *);

    void off();
    void red();
    void green();
};

#endif // LED_H
