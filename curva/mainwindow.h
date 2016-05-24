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
#include <QFileDialog>
#include <QFile>

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
    //поэтому двигаем с конца элемент до своего мест
    //с замещением точки если координата x
    void MoveFromBackWithout();
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
    void on_lineEditX_textChanged(const QString &arg1);
    void on_lineEditY_textChanged(const QString &arg1);
    void on_UserCurve_currentIndexChanged(int index);

    void on_actionDelete_curve_triggered();

    void on_actionOpen_file_triggered();

    void on_actionSave_File_as_triggered();

    void on_actionSave_File_triggered();
    //при клик по checkbox
    void on_checkActiv_clicked();

private:
    void SaveToTxt(bool &flag, QFile &file);
    void SaveToDoc(bool &flag, QFile &file);
    void ReadFromTxt(bool &flag, QFile &file);
    void ReadFromDoc(bool &flag, QFile &file);
    void CheckVector(bool &okay);
    QVector<graph> base;//База с прямыми пользователя
    Ui::MainWindow *ui;
    MyNewCurve *litwin;
    MyDeleteCurve *DelWin;
    //Добавить имя файла для кнопки "сохранить"
    QString NameOfFile;
    int free_index;//индекс удаляемой точки в base[index].tchk
    //символы и кривые для подсветки,удаления и последнего клика
    QwtSymbol *ActivSimOreol,*FreeSimOreol,*NewSim;
    QwtPlotCurve *FreeCurve;
    QwtPlotCurve *NewCurve;
    QwtPlotCurve *ActivCurve;
    void AddSimbols();
    //инициализирует вспомогательные кривые
    void addHelpCurve();
    void addPlot();//поле графика
    void addPlotGrid();//сетка
    void addCurve(graph &buf);
    //Рисует все прямые
    void reshow();
    void enableMagnifier();
    void enableMovingOnPlot();
    //переводит координаты клика в полле ввода
    void enablePicker();
    void AbleUseBlockAdd();
    //а это для удаления
    void AbleUseBlockFree();
    void ChangeNewPoint();
};


#endif // MAINWINDOW_H
