#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>

#include "Freezer.h"
#include "controller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QDateTime mTime;

    Controller *mController;
    Freezer *mFreezer;
    cOutput *mFreezerOut;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void temperatureChanged(float temperature);
    void run();

};

#endif // MAINWINDOW_H
