#ifndef VISUALGRAPH_H
#define VISUALGRAPH_H
#include "libs.h"
class VisualGraph: public QDialog
{
    Q_OBJECT
public:
    VisualGraph(QWidget *parent,QVector <graphic*> vector);
    QwtPlot *gr;
    QwtPlotPanner *d_panner;
    QVector <QwtPlotCurve*> curves;
    QwtSymbol *symbol;
    //в идее загонять вектор и для каждого его элемента строить кривую

};
#endif // VISUALGRAPH_H
