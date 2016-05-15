#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "mydialogcurve.h"
#include <QMainWindow>
#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_legend.h>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>
#include <QMainWindow>
#include <QVector>
#include <QMessageBox>
namespace Ui {
class MainWindow;
}
class MyNewCurve;
class MyDeleteCurve;

class graph{
public:
    graph();
    //по моим наблюдениям каждому QwtPlotCurve *
    //может соответствовать только одна кривая
    QwtPlotCurve *curva;
    QString name;
    //сортировку для QPolygonF я не нашел
    //поэтому решил использовать свой вектор из QPointF
    QVector<QPointF> tchk;
    int red,green,blue;
    double pen;//толщина
    //предполагается что новый элемент tchk добавлен в конец
    //поэтому двигаем с конца элемент до своего места
    void MoveFromBack();
    //тоже самое но с замещением точки если координата x
    //одна и таже
    void MoveFromBackWithout();
};


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void click_on_canvas( const QPoint &pos );
    void on_add_clicked();
    void on_free_clicked();
    void on_OneL_clicked();// pushbutton <
    void on_OneR_clicked();// pushbutton >
    void on_TWoR_clicked();// pushbutton >>
    void on_TwoL_clicked();// pushbutton <<
    //Открыть окно добавления графика
    void on_actionNew_curve_triggered();

    //При измениении содержимого ввода провереем на заполненовсть
    //и делаем возможным или невозможным нажатее кнопки add
    void on_lineEditX_textChanged(const QString &arg1);
    void on_lineEditY_textChanged(const QString &arg1);
    void on_UserCurve_currentIndexChanged(int index);

    void on_actionDelete_curve_triggered();

private:
    QVector<graph> base;//База с прямыми пользователя
    Ui::MainWindow *ui;
    MyNewCurve *litwin;
    MyDeleteCurve *DelWin;
    int free_index;//точка для ->
    /*Прямая состоящая из одной точки,которая точно
     *есть у пользователя, используемая для отображаения
     * на графике выделенной для удаления точки под
     * free_index номером
     */
    QwtPlotCurve *free_tchk;
    void addPlot();//поле графика
    void addPlotGrid();//сетка
    void addfreeCurve();
    void addCurve(graph &buf);
    //Рисует все прямые
    void FullReshow();
    //Только та что в comandBox
    void reshow();
    void enableMagnifier();
    void enableMovingOnPlot();
    //переводит координаты клика в полле ввода
    void enablePicker();
};


#endif // MAINWINDOW_H
