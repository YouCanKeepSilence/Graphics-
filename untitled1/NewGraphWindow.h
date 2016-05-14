#ifndef NEWGRAPHWINDOW_H
#define NEWGRAPHWINDOW_H
#include "libs.h"



class NewGraphicWindow:public QDialog
{
    Q_OBJECT
public:
    //QVector <QPolygonF> localpoint;
    QPolygonF localpoint;
    QString localname;
    QColor localcolor;
    int localtolshina;
    graphic *inwork;
    NewGraphicWindow(QWidget *parent,class graphic *work);
private:
    QLabel *nameline;
    QLineEdit *nameenter;
    QLabel *xname;
    QLabel *yname;
    QLineEdit *xenter;
    QLineEdit *yenter;
    QPushButton *AddPoint;
    //Как-то выбирать цвет?
    QLabel *nametolshina;
    QSpinBox *toshinaenter;
    QLabel *WhatPoints;
    QPushButton *AddGraph;
    QPushButton *Cancel;
private slots:
    void AddPointClicked();
    void EnableAddGraph();
    void AddGraphClicked();
    //class graphic grap;
};

#endif // NEWGRAPHWINDOW_H
