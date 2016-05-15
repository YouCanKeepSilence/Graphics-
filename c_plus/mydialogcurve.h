#ifndef MYDIALOGCURVE_H
#define MYDIALOGCURVE_H
#include "mainwindow.h"
#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QApplication>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QSpinBox>

class MyNewCurve:public QDialog
{
    Q_OBJECT
public:
    MyNewCurve(class graph &nov,QWidget *parent);
private:
    QLabel *text;
    QLineEdit *name;
    QHBoxLayout *Lname;
    QLabel      *TextRed,*TextGreen,*TextBlue;
    QSpinBox    *BoxRed ,*BoxGreen ,*BoxBlue;
    QHBoxLayout *LRed   ,*LGreen   ,*LBlue;
    //для ширины:
    QLabel *TextThickness;
    QDoubleSpinBox *BoxThickness;
    QHBoxLayout *LThickness;
    QPushButton *ok;
    QPushButton *cancel;
    QHBoxLayout *LPushButton;
    QVBoxLayout *Final;
    class graph *curva;
 private slots:
    void TextChanged(QString str);//доступность кнопки ок
    void OkClicked();//выход через accept , тоесть вернёт 1.
};

class MyDeleteCurve:public QDialog
{
    Q_OBJECT
    QLabel *text;
    QComboBox *choose;
    QPushButton *ok;
    QPushButton *cancel;
    QHBoxLayout *Lone;
    QHBoxLayout *Ltwo;
public:
    MyDeleteCurve(QWidget *parent=0);
};
#endif // MYDIALOGCURVE_H
