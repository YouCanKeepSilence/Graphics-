#ifndef MYDIALOGCURVE_H
#define MYDIALOGCURVE_H
/*!
  \file
  \brief Загловочный файл окон добавления и удаления графиков

  Содержит в себе описания двух окон добавления и удаления
  */

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
/*!
 * \brief The MyNewCurve class
 *
 * Класс окна добавления нового графика.Вызывается при нажатии Edit->New Curve
 * внутрь окна заносится вся информация о прямой, после создания прямой в главном окне можно добавлять различные точки
 * \warning Имя прямой не должно содержать только цифры.
 */


class MyNewCurve:public QDialog
{
    Q_OBJECT
public:
    ///При создании окно получает ссылку на класс прямой и заполняет его.
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
    ///Доступность кнопки ок
    void TextChanged(QString str);
    ///выход через accept , тоесть вернёт 1.
    void OkClicked();
};
/*!
 * \brief The MyDeleteCurve class
 *
 * Класс окна удаления текущего активного графика. Весь смысл в том чтобы подтвердить удаление
 */

class MyDeleteCurve:public QDialog
{
    Q_OBJECT
    QLabel *text;

    QPushButton *ok;
    QPushButton *cancel;
    QHBoxLayout *Lone;
    QHBoxLayout *Ltwo;
    QVBoxLayout *Final;
public:
    ///Получает имя строки для вывода
    MyDeleteCurve(QWidget *parent, QString name);

};
#endif // MYDIALOGCURVE_H
