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
    //и возвращаем новый индекс этой точки
    int MoveFromBackWithout();
    //Возращает индекс точки ближайшей к передаваемым координатам
    int FindNear(double coordX,double coordY);
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
    void on_lineEditX_textChanged();
    void on_lineEditY_textChanged();
    void on_UserCurve_currentIndexChanged(int index);
    void on_actionDelete_curve_triggered();
    void Move_canvas( const QPoint &pos );
private:
    QVector<graph> base;//База с прямыми пользователя
    Ui::MainWindow *ui;
    MyNewCurve *litwin;
    MyDeleteCurve *DelWin;
    //индекс base из поля coomandbox
    int WorkingCurve;
    int free_index;//точка для ->
    /*Прямая состоящая из одной точки,которая точно
     *есть у пользователя, используемая для отображаения
     * на графике выделенной для удаления точки под
     * free_index номером
     */
    //Oreol символы отображаются позади точек пямой
    //free для удаления activ для подсветки активной прямой
    QwtSymbol *CurveSim,*ActivSimOreol,*FreeSimOreol,*NewSim;
    QwtPlotCurve *FreeCurve;
    QwtPlotCurve *NewCurve;
    QwtPlotCurve *ActivCurve;
    void AddSimbols();
    //инициализирует вспомогательные кривые
    void addHelpCurve();
    void addPlot();//поле графика
    void addPlotGrid();//сетка
    void addfreeCurve();
    void addCurve(graph &buf);
    //Только та что в comandBox
    void reshow();
    void enableMagnifier();
    void enableMovingOnPlot();
    //переводит координаты клика в полле ввода
    void enablePicker();
    //контроль доступности работы с добавлением
    void AbleUseBlockAdd();
    //а это для удаления
    void AbleUseBlockFree();
    void ChangeNewPoint();
};
/*#ifndef MAINWINDOW_H
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
#include <QLineEdit>
#include <QLabel>
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
    //с замещением точки если координата x одна и та же
    void MoveFromBackWithout();
    //Поиск ближайшей точки. Возвращает индекс. если пусто то  -1
    int FindNear(double coordX,double coordY);
};


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    //пользователь совершил клик
    void ClickedPlot( const QPoint &pos );
    //Пользователь водит
    void MovedPlot( const QPoint & );
    void on_add_clicked();
    void on_free_clicked();
    void on_OneL_clicked();// pushbutton <
    void on_OneR_clicked();// pushbutton >
    void on_TWoR_clicked();// pushbutton >>
    void on_TwoL_clicked();// pushbutton <<
    //Открыть окно добавления графика
    void on_actionNew_curve_triggered();
    //Открыть окно удаления графика
    void on_actionDelete_curve_triggered();
    //При измениении содержимого ввода провереем на заполненовсть
    //и делаем возможным или невозможным нажатие кнопки add
    void on_lineEditX_textChanged();
    void on_lineEditY_textChanged();
    void on_UserCurve_currentIndexChanged(int index);
private:
    QVector<graph> base;//База с прямыми пользователя
    Ui::MainWindow *ui;
    MyNewCurve *litwin;
    MyDeleteCurve *DelWin;

    int free_index;
    Прямая состоящая из одной точки,которая точно
    есть у пользователя, используемая для отображения
    на графике выделенной для удаления точки под
    free_index номером
    void addCurve(graph &buf);
    //Перерисовывает график и точку для удаления
    void reshow();
    void enableMagnifier();
    void enableMovingOnPlot();
    //переводит координаты клика в полле ввода
    void enablePicker();

};*/

#endif // MAINWINDOW_H
