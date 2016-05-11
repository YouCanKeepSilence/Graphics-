#ifndef MYWIN_H
#define MYWIN_H
#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QRadioButton>
#include <QRect>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <qwt_plot.h>
#include <QSpacerItem>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_curve.h>
#include <QVector>
#include <qwt_plot_panner.h>
#include <qwt_plot_grid.h>
#include <qwt_legend.h>

class graph: public QDialog
{
    Q_OBJECT
public:

    QwtPlot *gr;
    QwtPlotPanner *d_panner;
    QwtPlotCurve *curve;
    QwtSymbol *symbol;
    graph(QWidget *parent,QPolygonF point);//в идее загонять вектор и для каждого его элемента строить кривую

public slots:
    void makeme();//ненужен

};

class Win1: public QDialog
{
    Q_OBJECT
public:
    QVector  <QPolygonF> vec;//пытаюсь загнать точки в вектора. Я кажется ебанулся...
    QPolygonF points;
     //QPolygonF points;
    //yjxm
    //QString str2=(str.toInt());
    Win1(QWidget *parent);
    graph *mgr=NULL;
private:

    QLabel *sost;//Выводим текущие точки
    QLabel *name;//Еще не придумал зачем
    QPushButton *Postr;//Начинаем построение
    QPushButton *ext;//Выход
    QPushButton *Add;
    QLineEdit *filename;//вводим имя файла
    QRadioButton *res1;
    QRadioButton *res2;
    QLineEdit *x;
    QLineEdit *y;
    QSpacerItem *sx;
    //QSpinBox *x;//вводим точку по х
    //QSpinBox *y;//по у
private slots:
    //void AddP(QString str1,QString str2);
    //void PostrOn();
    void FileAdd(QString str);
    void AddClik();
    void PostrClick();
    //void GO();

};


#endif // MYWIN_H


