#-------------------------------------------------
#
# Project created by QtCreator 2017-06-14T20:10:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = shweeetSim
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    freezer.cpp \
    controller.cpp \
    onoffcontroller.cpp \
    temp_control.cpp \
    led.cpp \
    temp_probe.cpp \
    heater.cpp \
    nvm.cpp \
    output.cpp \
    integral_controller.cpp \
    integral_widget.cpp \
    integral_parameters.cpp

HEADERS  += mainwindow.h \
    Freezer.h \
    controller.h \
    onoffcontroller.h \
    temp_control.h \
    led.h \
    temp_probe.h \
    heater.h \
    nvm.h \
    output.h \
    integral_controller.h \
    integral_widget.h \
    integral_parameters.h

FORMS    += mainwindow.ui


INCLUDEPATH += "C:\Program Files (x86)\Windows Kits\10\Include\10.0.10240.0\ucrt"
LIBS += -L"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10240.0/ucrt/x64"
