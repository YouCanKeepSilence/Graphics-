#-------------------------------------------------
#
# Project created by QtCreator 2016-05-14T11:21:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = new_curves
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mydialogcurve.cpp

HEADERS  += mainwindow.h \
    mydialogcurve.h \
    libs.h

FORMS    += mainwindow.ui
INCLUDEPATH += /usr/include/qwt/
DEPENDPATH += /usr/include/qwt/
LIBS += -L/usr/lib/ -lqwt-qt5
