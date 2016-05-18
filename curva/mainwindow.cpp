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
    free_index=WorkingCurve=-1;
    AbleUseBlockAdd();
    AbleUseBlockFree();
    litwin=NULL;
    DelWin=NULL;
    // Создать поле со шкалами для отображения графика
    addPlot();
    // Включить масштабную сетку
    addPlotGrid();
    // Кривая
    //addfreeCurve();
    // Включить возможность приближения/удаления графика
    //инициализировать символы
    AddSimbols();
    //инициализировать вспомогатеьные кривые
    addHelpCurve();
    // ///////////////////////////////
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
//     aaaaaaaaaaaaa
void MainWindow::ChangeNewPoint()
{
    double x =ui->lineEditX->text().toDouble();
    double y =ui->lineEditY->text().toDouble();
    QPolygonF point;
    point<<QPointF(x,y);
    NewCurve->setSamples(point);
    reshow();
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
/*void MainWindow::addCurve(class graph &buf)
{
    //index брать из combobox
    int index=base.size();//номер элемента в векторе base
    base.push_back(graph());
    base[index].curva=new QwtPlotCurve;
    base[index].name=buf.name;
    base[index].red=buf.red;
    base[index].green=buf.green;
    base[index].blue=buf.blue;
    base[index].pen=buf.pen;
    base[index].curva->setPen( QColor(buf.red,buf.green,buf.blue), buf.pen );
    base[index].curva->setRenderHint
            ( QwtPlotItem::RenderAntialiased, true ); // сглаживание
    base[index].curva->setSymbol( CurveSim );
    base[index].curva->setTitle(buf.name);
    ui->UserCurve->addItem(buf.name,index);
    base[index].curva->attach( ui->Qwt_Widget ); // отобразить кривую на графике
    ui->UserCurve->setCurrentIndex(index);
    reshow();
}
*/
void MainWindow::enableMovingOnPlot()
{
    // #include <qwt_plot_panner.h>
    QwtPlotPanner *d_panner = new QwtPlotPanner( ui->Qwt_Widget->canvas() );
    // клавиша, активирующая перемещение
    d_panner->setMouseButton( Qt::RightButton );

}
void MainWindow::addCurve(class graph &buf)
{
    int index=base.size();//номер элемента в векторе base
    base.push_back(graph());
    base[index].curva=new QwtPlotCurve;
    base[index].name=buf.name;
    base[index].red=buf.red;
    base[index].green=buf.green;
    base[index].blue=buf.blue;
    base[index].pen=buf.pen;
    base[index].curva->setPen( QColor(buf.red,buf.green,buf.blue), buf.pen );
    base[index].curva->setRenderHint
            ( QwtPlotItem::RenderAntialiased, true ); // сглаживание
    base[index].curva->setSymbol( CurveSim );
    base[index].curva->setTitle(buf.name);
    ui->UserCurve->addItem(buf.name,index);
    base[index].curva->attach( ui->Qwt_Widget ); // отобразить кривую на графике

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
    connect( d_picker, SIGNAL(moved( const QPoint & ) ),
          SLOT( Move_canvas( const QPoint & ) ) );
}

void MainWindow::Move_canvas( const QPoint &pos )
{
    // считываем значения координат клика
    double x = ui->Qwt_Widget->invTransform(QwtPlot::xBottom, pos.x());
    double y = ui->Qwt_Widget->invTransform(QwtPlot::yLeft, pos.y());
    ui->lineEditX->setText(QString::number(x));
    ui->lineEditY->setText(QString::number(y));
    ChangeNewPoint();
}
void MainWindow::click_on_canvas( const QPoint &pos )
{
    // считываем значения координат клика
    double x = ui->Qwt_Widget->invTransform(QwtPlot::xBottom, pos.x());
    double y = ui->Qwt_Widget->invTransform(QwtPlot::yLeft, pos.y());
    statusBar()->showMessage("x= " + QString::number(x) +
                             "; y = " + QString::number(y));
    //отправляем считанное в статус бар и
    //строкии ввода координат
    ui->lineEditX->setText(QString::number(x));
    ui->lineEditY->setText(QString::number(y));
    //выделить ближайшую точку
    ChangeNewPoint();
    if(ui->UserCurve->count()>0)
    {
    int WorkingCurve=ui->UserCurve->currentIndex();
    free_index=base[WorkingCurve].FindNear(x,y);
    reshow();
    }
}

graph::graph(){}

int graph::MoveFromBackWithout()
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
        else if(tchk[i].x()==tchk[i-1].x())
                {
                       tchk[i-1]=tchk[i];
                       tchk.erase(tchk.begin()+i);
                }

            else break;
    return i;
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
    free_index=base[i].MoveFromBackWithout();
    base[i].curva->setSamples( base[i].tchk );
    reshow();
}

void MainWindow::on_free_clicked()
{   if(ui->UserCurve->count()>0)
    {
        WorkingCurve=ui->UserCurve->currentIndex();
        if(free_index>-1)
        {
        base[WorkingCurve].tchk.erase(base[WorkingCurve].tchk.begin()+free_index);
        if(free_index==base[WorkingCurve].tchk.size())
        free_index--;
        }
        base[WorkingCurve].curva->setSamples( base[WorkingCurve].tchk );
        if(base[WorkingCurve].tchk.size()==0) free_index=-1;
        reshow();
    }
}
/*
void MainWindow::reshow()
{
    free_index=-1;

    else
    {
        ActivCurve->setSamples(base[WorkingCurve].tchk);
        if(free_index<0) free_index=0;
        if(free_index>base[WorkingCurve].tchk.size()-1)
            free_index=base[WorkingCurve].tchk.size()-1;
        free<<base[WorkingCurve].tchk[free_index];
    }
}*/
void MainWindow::reshow()
{
    if(ui->UserCurve->count()==0) WorkingCurve=-1;
      else WorkingCurve=ui->UserCurve->currentIndex();
    QPolygonF free;
    ActivCurve->setSamples(free);
    if(WorkingCurve==-1)
    {
        free_index=-1;
    }
    else ActivCurve->setSamples(base[WorkingCurve].tchk);
    if(free_index>-1)
        free<<base[WorkingCurve].tchk[free_index];
    FreeCurve->setSamples(free ); // ассоциировать набор точек с кривой
    AbleUseBlockAdd();
    AbleUseBlockFree();
    ui->Qwt_Widget->replot();
}

void MainWindow::AddSimbols()
{
    CurveSim= new QwtSymbol( QwtSymbol::Ellipse,
    QBrush( Qt::red ), QPen( Qt::black, 0 ), QSize( 10, 10 ) );
    ActivSimOreol= new QwtSymbol( QwtSymbol::Ellipse,
    QBrush(Qt::blue ), QPen( Qt::blue, 1 ), QSize( 15, 15 ) );
    FreeSimOreol = new QwtSymbol( QwtSymbol::Ellipse,
    QBrush( Qt::green ), QPen( Qt::green, 1 ), QSize( 20, 20 ) );
    NewSim=new QwtSymbol( QwtSymbol::Diamond,
    QBrush( QColor(145,0,211) ), QPen( QColor(145,0,211), 1 ), QSize( 17, 17 ) );
}

void MainWindow::addHelpCurve()
{
    FreeCurve= new QwtPlotCurve;
    FreeCurve->setSymbol( FreeSimOreol);
    FreeCurve->setTitle("fFree");
    FreeCurve->setPen(Qt::green,0);
    FreeCurve->setRenderHint
            ( QwtPlotItem::RenderAntialiased, true ); // сглаживание
    FreeCurve->attach( ui->Qwt_Widget );
    ActivCurve= new QwtPlotCurve;
    ActivCurve->setSymbol( ActivSimOreol);
    ActivCurve->setPen(Qt::blue,4);
    ActivCurve->setTitle("Activ");
    ActivCurve->setRenderHint
            ( QwtPlotItem::RenderAntialiased, true ); // сглаживание
    ActivCurve->attach( ui->Qwt_Widget );
    NewCurve= new QwtPlotCurve;
    NewCurve->setSymbol( NewSim);
    NewCurve->setTitle("New");
    NewCurve->setPen(QColor(145,0,211),0);
    NewCurve->setRenderHint
            ( QwtPlotItem::RenderAntialiased, true ); // сглаживание
    NewCurve->attach( ui->Qwt_Widget );
}

void MainWindow::on_OneR_clicked()
{
    if(ui->UserCurve->count()>0)
    {
        int curve_index=ui->UserCurve->currentIndex();
        if(free_index<base[curve_index].tchk.size()-1)
            free_index++;
        reshow();
    }
}

void MainWindow::on_OneL_clicked()
{
    if(ui->UserCurve->count()>0)
        if(free_index>0)
            free_index--;
    reshow();
}

void MainWindow::on_TWoR_clicked()
{
    if(ui->UserCurve->count()>0)
    {
    int curve_index=ui->UserCurve->currentIndex();
    if(free_index<base[curve_index].tchk.size()-10)free_index+=10;
    else free_index=base[curve_index].tchk.size()-1;
    reshow();
    }
}

void MainWindow::on_TwoL_clicked()
{   if(ui->UserCurve->count()>0)
    {
    if(free_index>10)
        free_index-=10;
    else
        free_index=0;
    }
    reshow();
}

void MainWindow::on_actionNew_curve_triggered()
{
    if(litwin!=NULL)
    {
        litwin->close();
        delete litwin;
    }
    class graph nov;
    litwin=new MyNewCurve(nov,this);
    litwin->show();
    int i=litwin->exec();
    if (i==0)
        statusBar()->showMessage("cancel");
    if (i==1)
    {
        statusBar()->showMessage(nov.name);
        addCurve(nov);
    }
}

void MainWindow::on_lineEditX_textChanged()
{
    ChangeNewPoint();
    if(ui->UserCurve->count()>0)
    {
        if((!ui->lineEditY->text().isEmpty())&&(!ui->lineEditX->text().isEmpty()))
        ui->add->setEnabled(1);
    else
        ui->add->setEnabled(0);
    }
}

void MainWindow::on_lineEditY_textChanged()
{
    ChangeNewPoint();
    if(ui->UserCurve->count()>0)
    {
        if((!ui->lineEditY->text().isEmpty())&&(!ui->lineEditX->text().isEmpty()))
        ui->add->setEnabled(1);

    else
        ui->add->setEnabled(0);
    }
}

void MainWindow::on_UserCurve_currentIndexChanged(int index)
{
    WorkingCurve=index;
    free_index=-1;
    reshow();
}
/*
void MainWindow::on_actionDelete_curve_triggered()
{
    if(WorkingCurve>-1)
        {
        DelWin=new MyDeleteCurve(this,base[WorkingCurve].name);
        DelWin->show();
            int i=DelWin->exec();
            if (i==0)
                statusBar()->showMessage("cancel");
            if (i==1)
            {
                delete base[WorkingCurve].curva;
                base.erase(base.begin()+WorkingCurve);
                ui->UserCurve->removeItem(WorkingCurve);
                statusBar()->showMessage("deleted");
            }
        }
    reshow();
}*/
void MainWindow::on_actionDelete_curve_triggered()
{
    if(DelWin!=NULL)
    {
        DelWin->close();
        delete DelWin;
    }
    if(ui->UserCurve->count()!=0)
        {
        DelWin=new MyDeleteCurve(this,base[ui->UserCurve->currentIndex()].name);
        DelWin->show();
            int i=DelWin->exec();
            if (i==0)
                statusBar()->showMessage("cancel");
            if (i==1)
            {
                WorkingCurve=ui->UserCurve->currentIndex();
                delete base[WorkingCurve].curva;
                base.erase(base.begin()+WorkingCurve);
                ui->UserCurve->removeItem(WorkingCurve);
                free_index=-1;
                reshow();
                statusBar()->showMessage("deleted");
                if(ui->UserCurve->count()==0)
                    ui->add->setEnabled(false);
            }
        }
}

int graph::FindNear(double coordX,double coordY)
{
    int i,index=-1;
    double mindlin=-1.0;
    double bufdlin;
    if(tchk.size()>0)
    {
        index=0;
        mindlin=(tchk[0].x()-coordX)*(tchk[0].x()-coordX)+(tchk[0].y()-coordY)*(tchk[0].y()-coordY);
    }
    for(i=1;i<tchk.size();i++)
    {
        bufdlin=(tchk[i].x()-coordX)*(tchk[i].x()-coordX)
                +(tchk[i].y()-coordY)*(tchk[i].y()-coordY);
        if(bufdlin<mindlin)
        {
            index=i;
            mindlin=bufdlin;
        }
    }
    return index;
}


void MainWindow::AbleUseBlockFree()
{
    int i;
    if((free_index>-1)&&((WorkingCurve>-1))) i=1;
    else i=0;
    ui->free->setEnabled(i);
    if((free_index>0)&&((WorkingCurve>-1))) i=1;
    else i=0;
    ui->OneL->setEnabled(i);
    ui->TwoL->setEnabled(i);
    i=0;
    if(WorkingCurve>-1)
    if(free_index<base[WorkingCurve].tchk.size()-1)
    i=1;
    ui->TWoR->setEnabled(i);
    ui->OneR->setEnabled(i);
}

void MainWindow::AbleUseBlockAdd()
{
    int i;
    if(WorkingCurve>-1) i=1;
    else i=0;
    if((ui->lineEditY->text().isEmpty())&&(ui->lineEditY->text().isEmpty()))
        ui->add->setEnabled(0);
        else(ui->add->setEnabled(i));
    ui->lineEditX->setEnabled(i);
    ui->lineEditY->setEnabled(i);
}
