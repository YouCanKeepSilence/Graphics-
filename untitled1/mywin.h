#ifndef MYWIN_H
#define MYWIN_H

#include <cstdlib>

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
#include <QVector>
#include <QSpacerItem>
#include <QChar>
#include <QColor>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_grid.h>
#include <qwt_legend.h>


class graph: public QDialog
{
    Q_OBJECT
public:
    graph(QWidget *parent,QVector <QPolygonF> vector);
    int SIZE;
    QwtPlot *gr;
    QwtPlotPanner *d_panner;
    QVector <QwtPlotCurve*> curves;
    QwtSymbol *symbol;
    //в идее загонять вектор и для каждого его элемента строить кривую

public slots:
    void makeme();//ненужен

};
//Переделать прямую в класс
/*class graphic
 * {
 * privete? Public?
 * QVector points;
 * QString name;
 * QColor color;
 * int tolshina;
 * }
 */
/*Идея: добавить кнопку "добавить прямую" , при ее нажатии выводить новое диалоговое окно (см. блокнот)
 * после ввода вызывать конструктор с параметрами??
 * Загонять ее в вектор. Изи
 *
 */
class Win1: public QDialog
{
    Q_OBJECT
public:
    //QVector <graphic(*?)> vec
    QVector  <QPolygonF> vec;//пытаюсь загнать точки в вектора. Я кажется ебанулся...
    QPolygonF points;
    int countGR;
    Win1(QWidget *parent);
    graph *mgr=NULL;
private:

    QLabel *sost;//Выводим текущие точки выводит ли?
    QLabel *name;//Еще не придумал зачем
    QPushButton *Postr;//Начинаем построение
    QPushButton *ext;//Выход
    QPushButton *Add;//Добавить точку к прямой
    QPushButton *NewGR;//Добавить новую прямую.
    QLineEdit *filename;//вводим имя файла
    QRadioButton *res1;//первое расширение
    QRadioButton *res2;//второе
    QLineEdit *x;//линия под х
    QLineEdit *y;//линия под у
    QSpacerItem *sx;//не работает можно выпилить я думаю
    //QSpinBox *x;//вводим точку по х
    //QSpinBox *y;//по у
private slots:
    //void AddP(QString str1,QString str2);
    //void PostrOn();
    void FileAdd(QString str);
    void AddClik();
    void PostrClick();
    void NewGr();
    //void GO();

};


#endif // MYWIN_H


