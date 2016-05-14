#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QLabel>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDoubleValidator* doubler = new QDoubleValidator(this);
    ui->lineEditX->setValidator(doubler);
    ui->lineEditY->setValidator(doubler);
    free_index=0;
    // Создать поле со шкалами для отображения графика
    addPlot();

    // Включить масштабную сетку
    addPlotGrid();

    // Кривая
    addCurve();

    // Включить возможность приближения/удаления графика
    enableMagnifier();

    // Включить возможность перемещения по графику
    enableMovingOnPlot();

    // Включить отображение координат курсора и двух перпендикулярных
    // линий в месте его отображения
    enablePicker();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addPlot()
{
    // #include <qwt_plot.h>
    ui->Qwt_Widget->setTitle( "Qwt demonstration" );
    ui->Qwt_Widget->setCanvasBackground( Qt::white );

    // Параметры осей координат
    ui->Qwt_Widget->setAxisTitle(QwtPlot::yLeft, "Y");
    ui->Qwt_Widget->setAxisTitle(QwtPlot::xBottom, "X");
    ui->Qwt_Widget->insertLegend( new QwtLegend() );

}

void MainWindow::addPlotGrid()
{
    // #include <qwt_plot_grid.h>
    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setMajorPen(QPen( Qt::black, 1 )); // цвет линий и толщина
    grid->attach( ui->Qwt_Widget );
}

void MainWindow::addCurve()
{

    base.push_back(graph());
    for(int i=0;i<base.size();i++)
    {
        base[i].curva=new QwtPlotCurve;
        base[i].curva->setPen( Qt::blue, 6 );
        QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
        QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
        base[i].curva->setSymbol( symbol );
        base[i].curva->setTitle( "Demo Curve" );
        ui->UserCurve->addItem("Test",0);
        base[i].curva->setSamples( base[i].tchk ); // ассоциировать набор точек с кривой
        base[i].curva->attach( ui->Qwt_Widget ); // отобразить кривую на графике
    }
    QwtSymbol *symbolf = new QwtSymbol( QwtSymbol::Ellipse,
    QBrush( Qt::green ), QPen( Qt::green, 2 ), QSize( 10, 10 ) );
       free_tchk= new QwtPlotCurve;
    free_tchk->setSymbol( symbolf);
    QPolygonF free;
    if(base[ui->UserCurve->currentIndex()].tchk.size()>0)
    free<<base[ui->UserCurve->currentIndex()].tchk[free_index];
    free_tchk->setSamples(free ); // ассоциировать набор точек с кривой
    free_tchk->attach( ui->Qwt_Widget );
}

void MainWindow::enableMagnifier()
{
    // #include <qwt_plot_magnifier.h>
    QwtPlotMagnifier *magnifier =
            new QwtPlotMagnifier(ui->Qwt_Widget->canvas());
    // клавиша, активирующая приближение/удаление
    magnifier->setMouseButton(Qt::MidButton);
}

void MainWindow::enablePicker()
{
    // #include <qwt_plot_picker.h>
    // настройка функций
    QwtPlotPicker *d_picker =
            new QwtPlotPicker(
                QwtPlot::xBottom, QwtPlot::yLeft, // ассоциация с осями
    QwtPlotPicker::CrossRubberBand, // стиль перпендикулярных линий
    QwtPicker::AlwaysOn, // всегда включен
    ui->Qwt_Widget->canvas() ); // ассоциация с полем

    // Цвет перпендикулярных линий
    d_picker->setRubberBandPen( QColor( Qt::red ) );

    // цвет координат положения указателя
    d_picker->setTrackerPen( QColor( Qt::black ) );

    // непосредственное включение вышеописанных функций
    d_picker->setStateMachine( new QwtPickerDragPointMachine() );
    connect( d_picker, SIGNAL( appended( const QPoint & ) ),
            SLOT( click_on_canvas( const QPoint & ) ) );
}

void MainWindow::enableMovingOnPlot()
{
    // #include <qwt_plot_panner.h>
    QwtPlotPanner *d_panner = new QwtPlotPanner( ui->Qwt_Widget->canvas() );
    // клавиша, активирующая перемещение
    d_panner->setMouseButton( Qt::RightButton );
}



void MainWindow::click_on_canvas( const QPoint &pos )
{
    // считываем значения координат клика
    double x = ui->Qwt_Widget->invTransform(QwtPlot::xBottom, pos.x());
    double y = ui->Qwt_Widget->invTransform(QwtPlot::yLeft, pos.y());
    statusBar()->showMessage("x= " + QString::number(x) +
                             "; y = " + QString::number(y)+"Free="+QString::number(free_index));
   // ui->lineEditX->//(QString::number(x));
}

graph::graph()
{
    curva =new QwtPlotCurve;
}

void graph::MoveFromBack()
{
    int i;
    QPointF buf;
    for(i=tchk.size()-1;i>0;i--)
        if(tchk[i].x()<tchk[i-1].x())
        {
            buf=tchk[i];
            tchk[i]=tchk[i-1];
            tchk[i-1]=buf;
        }
}

void MainWindow::on_add_clicked()
{
    double x =ui->lineEditX->text().toDouble();
    double y =ui->lineEditY->text().toDouble();
    int i;
    i=ui->UserCurve->currentIndex();
    statusBar()->showMessage("x= " + QString::number(x) +
                             "; y = " + QString::number(y)+"Free="+QString::number(free_index));
    base[i].tchk.push_back(QPointF(x,y));
    base[i].MoveFromBack();
    base[i].curva->setSamples( base[i].tchk );
    QPolygonF free;
    if(base[ui->UserCurve->currentIndex()].tchk.size()>0)
    free<<base[ui->UserCurve->currentIndex()].tchk[free_index];
    free_tchk->setSamples(free ); // ассоциировать набор точек с кривой
    ui->Qwt_Widget->replot();
}

void MainWindow::on_free_clicked()
{
    int curve_index=ui->UserCurve->currentIndex();
    if(free_index<base[curve_index].tchk.size()-2)
    base[curve_index].tchk.erase(base[curve_index].tchk.begin()+free_index);
    else base[curve_index].tchk.pop_back();
    base[curve_index].curva->setSamples( base[curve_index].tchk );
    QPolygonF free;
    free<<base[ui->UserCurve->currentIndex()].tchk[free_index];
    free_tchk->setSamples(free ); // ассоциировать набор точек с кривой
    ui->Qwt_Widget->replot();
}

void MainWindow::on_OneL_clicked()
{
    if(free_index>0) free_index--;
    QPolygonF free;
    free<<base[ui->UserCurve->currentIndex()].tchk[free_index];
    free_tchk->setSamples(free ); // ассоциировать набор точек с кривой
    ui->Qwt_Widget->replot();
}

void MainWindow::on_OneR_clicked()
{
    int curve_index=ui->UserCurve->currentIndex();
    if(free_index<base[curve_index].tchk.size()-1) free_index++;
    QPolygonF free;
    free<<base[ui->UserCurve->currentIndex()].tchk[free_index];
    free_tchk->setSamples(free ); // ассоциировать набор точек с кривой
    ui->Qwt_Widget->replot();
}
/*
void MainWindow::on_actionNew_curve_triggered()
{
    QLabel
    QLineEdit *ll=new QLineEdit;
    ll->show();
}
*/
