#ifndef FILE_H
#define FILE_H
#include <QVector>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <iostream>
#include "mywin.h"
const QString allFileToString(QFile &aFile);
void setDataToVector(const QStringList &aStringList,
                     QVector< QVector <float> > &aVector);
void fun(const QVector< QVector <float> > &aVector,QVector <QPolygonF> &FinalV);
int SetFromFile(QString name,QVector <QPolygonF> &vector);
#endif // FILE_H
