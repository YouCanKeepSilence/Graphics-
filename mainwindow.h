#ifndef MAINWINDOW_H
#define MAINWINDOW_H
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
namespace Ui {
class MainWindow;
}

class graph{
public:
    graph();
    QwtPlotCurve *curva;
    QVector<QPointF> tchk;
    void MoveFromBack();
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
    void on_OneL_clicked();
    void on_OneR_clicked();
    void on_actionNew_curve_triggered();

private:
    QVector<graph> base;
    Ui::MainWindow *ui;
    int free_index;
    QwtPlotCurve *free_tchk;
    void addPlot();
    void addPlotGrid();
    void addCurve();
    void enableMagnifier();
    void enableMovingOnPlot();
    void enablePicker();
};


#endif // MAINWINDOW_H
