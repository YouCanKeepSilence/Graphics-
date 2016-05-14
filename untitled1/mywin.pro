#-------------------------------------------------
#
# Project created by QtCreator 2016-05-07T13:19:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled1
TEMPLATE = app


SOURCES += main.cpp \
    WinMain.cpp \
    NewGraphWindow.cpp \
    VisualGraph.cpp

HEADERS  += \
    WinMain.h \
    NewGraphWindow.h \
    libs.h \
    graphic.h \
    VisualGraph.h

FORMS    +=
INCLUDEPATH += /usr/include/qwt/
DEPENDPATH += /usr/include/qwt/
LIBS += -L/usr/lib/ -lqwt-qt5
