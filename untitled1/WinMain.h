#ifndef MYWIN_H
#define MYWIN_H
#include "libs.h"



class WinMain: public QDialog
{
    Q_OBJECT
public:
    QVector <graphic*> vec;
    //QVector  <QPolygonF> vec;//пытаюсь загнать точки в вектора. Я кажется ебанулся...
    //QPolygonF points;
    int countGR;
    WinMain(QWidget *parent);
    class VisualGraph *mgr=NULL;
    class NewGraphicWindow *AddGr=NULL;
private:

    QLabel *sost;//Выводим текущие точки выводит ли?
    QLabel *name;//Еще не придумал зачем
    QPushButton *Postr;//Начинаем построение
    QPushButton *ext;//Выход
    QPushButton *NewGR;//Добавить новую прямую.
    QLineEdit *filename;//вводим имя файла
    QRadioButton *res1;//первое расширение
    QRadioButton *res2;//второе
    QLineEdit *x;//линия под х
    QLineEdit *y;//линия под у
    QSpacerItem *sx;//не работает можно выпилить я думаю

private slots:

    //void FileAdd(QString str);
    void PostrClick();
    void NewGr();


};


#endif // MYWIN_H


