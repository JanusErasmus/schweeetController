#include <QDebug>
#include <QTimer>
#include <QLabel>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "onoffcontroller.h"
#include "integral_controller.h"
#include "integral_widget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qRegisterMetaType<IntegralParameters>("IntegralParameters");

    mTime = QDateTime::currentDateTime();

    cLED *heaterLed = new cLED();
    cLED *freezerLed = new cLED();

    QLabel *label = new QLabel("Heater:");
    label->setAlignment(Qt::AlignRight);
    ui->ledLayout->addWidget(label);
    ui->ledLayout->addWidget(heaterLed);
    label = new QLabel("Freezer:");
    label->setAlignment(Qt::AlignRight);
    ui->ledLayout->addWidget(label);
    ui->ledLayout->addWidget(freezerLed);

    IntegralWidget *heatVars = new IntegralWidget("Heater");
    ui->variablesLayout->addWidget(heatVars);
    IntegralWidget *freezeVars = new IntegralWidget("Freezer");
    ui->variablesLayout->addWidget(freezeVars);

    mFreezerOut = new cOutput();
    mController = new IntegralController(new cHeater,
                                         heaterLed,
                                         mFreezerOut,
                                         freezerLed,
                                         new cTempProbe());
    connect((IntegralController*)mController, SIGNAL(updateHeaterParameters(IntegralParameters)), heatVars, SLOT(updateVariables(IntegralParameters)));
    connect((IntegralController*)mController, SIGNAL(differentialCooling(bool)), heatVars, SLOT(disable(bool)));
    connect((IntegralController*)mController, SIGNAL(updateFreezerParameters(IntegralParameters)), freezeVars, SLOT(updateVariables(IntegralParameters)));
    connect((IntegralController*)mController, SIGNAL(differentialCooling(bool)), freezeVars, SLOT(disable(bool)));

    //mController = new OnOffController(25);

    mFreezer = new Freezer(mController, mFreezerOut);

    QTimer *timer = new QTimer();
    timer->setInterval(100);
    connect(timer, SIGNAL(timeout()), SLOT(run()));
    timer->start();

    connect(mFreezer, SIGNAL(temperatureChanged(float)), SLOT(temperatureChanged(float)));

    setWindowTitle("Shweeet Simulator");
}

void MainWindow::run()
{
    mTime = mTime.addMSecs(100);
    ui->timeLabel->setText(mTime.toString("hh:mm:ss"));

    mFreezer->run();
}

void MainWindow::temperatureChanged(float temperature)
{
    QString string;
    string.setNum(temperature, 'f', 1);    
    string.append("°C");

    ui->freezerTemp->setText(string);
}


MainWindow::~MainWindow()
{
    delete mFreezer;
    delete mFreezerOut;
    delete mController;
    delete ui;
}
