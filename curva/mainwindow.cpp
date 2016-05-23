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
    free_index=-1;
    ui->add->setEnabled(0);
    AbleUseBlockAdd();
    AbleUseBlockFree();
    litwin=NULL;
    DelWin=NULL;
    this->setWindowTitle("Graphics creator v. 1.0");
    // Создать поле со шкалами для отображения графика
    addPlot();

    // Включить масштабную сетку
    addPlotGrid();

    // Кривая
    //addfreeCurve();
    AddSimbols();
    //инициализировать вспомогатеьные кривые
    addHelpCurve();
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
    ui->Qwt_Widget->setTitle( "Your graphics" );
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

    QwtSymbol *CurveSim= new QwtSymbol( QwtSymbol::Ellipse,
    QBrush( Qt::red ), QPen( Qt::black, 0 ), QSize( 10, 10 ) );
    base[index].curva->setSymbol( CurveSim);
    base[index].curva->setTitle(buf.name);
    ui->UserCurve->addItem(buf.name,index);
    base[index].curva->attach( ui->Qwt_Widget ); // отобразить кривую на графике

}

void MainWindow::ChangeNewPoint()
{
    double x =ui->lineEditX->text().toDouble();
    double y =ui->lineEditY->text().toDouble();
    QPolygonF point;
    point<<QPointF(x,y);
    NewCurve->setSamples(point);
    ui->Qwt_Widget->replot();
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
    connect(d_picker,SIGNAL(moved(QPoint)),SLOT(MoveNewSim(const QPoint &)));
}

void MainWindow::enableMovingOnPlot()
{
    // #include <qwt_plot_panner.h>
    QwtPlotPanner *d_panner = new QwtPlotPanner( ui->Qwt_Widget->canvas() );
    // клавиша, активирующая перемещение
    d_panner->setMouseButton( Qt::RightButton );
}

void MainWindow::MoveNewSim(const QPoint &pos)
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
    int curve_index=ui->UserCurve->currentIndex();
    free_index=base[curve_index].FindNear(x,y);
    reshow();
    }
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
        else break;
}

void graph::MoveFromBackWithout()
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
    base[i].MoveFromBackWithout();
    base[i].curva->setSamples( base[i].tchk );
    reshow();
}

void MainWindow::on_free_clicked()
{   if(ui->UserCurve->count()>0)
    {
        int curve_index=ui->UserCurve->currentIndex();
        if(free_index>-1)
        {
        base[curve_index].tchk.erase(base[curve_index].tchk.begin()+free_index);
        if(free_index==base[curve_index].tchk.size())free_index--;
        }
        base[curve_index].curva->setSamples( base[curve_index].tchk );
        if(base[curve_index].tchk.size()==0) free_index=-1;
        reshow();
    }
}

void MainWindow::reshow()
{
    QPolygonF free;
    ActivCurve->setSamples(free);
    if(ui->UserCurve->count()>0)
    {
        int z=ui->UserCurve->currentIndex();
        ActivCurve->setSamples(base[z].tchk);
    }
    if(free_index>-1)
        free<<base[ui->UserCurve->currentIndex()].tchk[free_index];
    FreeCurve->setSamples(free ); // ассоциировать набор точек с кривой
    AbleUseBlockAdd();
    AbleUseBlockFree();
    ui->Qwt_Widget->replot();
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
    litwin->setWindowTitle("Add new curve");
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

void MainWindow::on_lineEditX_textChanged(const QString &arg1)
{
    ChangeNewPoint();
    if((ui->UserCurve->count()>0)&&
       (!ui->lineEditY->text().isEmpty())&&(!ui->lineEditY->text().isEmpty()))
            ui->add->setEnabled(1);
    else
        ui->add->setEnabled(0);

}

void MainWindow::on_lineEditY_textChanged(const QString &arg1)
{
    ChangeNewPoint();
    if((ui->UserCurve->count()>0)&&
        (!ui->lineEditY->text().isEmpty())&&(!ui->lineEditY->text().isEmpty()))
            ui->add->setEnabled(1);
    else
        ui->add->setEnabled(0);
}

void MainWindow::on_UserCurve_currentIndexChanged(int index)
{
    free_index=-1;
}

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
                int z=ui->UserCurve->currentIndex();
                delete base[z].curva;
                base.erase(base.begin()+z);
                ui->UserCurve->removeItem(z);
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
    double bufdlin,mindlin=-1;
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

void MainWindow::SaveToTxt()
{

}

void MainWindow::on_actionOpen_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr(".txt (*.txt);; .doc (*.doc)"));//Сюда дописывать форматы

        if (fileName != "")
        {
            QFile file(fileName);
            QTextStream in(&file);
            bool ok;
            if (!file.open(QIODevice::ReadOnly))
            {
                QMessageBox::critical(this, tr("Error"), tr("Could not open file")); //Типо если файл нельзя читать то ошибко.
                return;
            }
            qDebug()<<fileName[fileName.length()-1];
            if(fileName[fileName.length()-1]=='t')//для тхт формата.
            {
                qDebug()<<"Тут.";
                class graph nov;
                int i=-1;
                while(1)
                {
                    QString buf;
                    buf=in.readLine();
                    if(buf.isEmpty())
                    {
                        for(int j=0;j<base.size();j++)
                        {
                            base[j].curva->setSamples(base[j].tchk);
                            reshow();
                        }
                        NameOfFile=fileName;
                        QMessageBox::information(this,tr("Done"),tr("Успешно открыто"));
                        break;
                    }
                    buf.toDouble(&ok);
                    if(!ok)
                    {

                        nov.name=buf;
                        buf=in.readLine();
                        nov.red=buf.toInt();
                        buf=in.readLine();
                        nov.green=buf.toInt();
                        buf=in.readLine();
                        nov.blue=buf.toInt();
                        buf=in.readLine();
                        nov.pen=buf.toDouble();
                        addCurve(nov);
                        i++;
                    }
                    else
                    {
                        QString bufy;
                        bufy=in.readLine();
                        base[i].tchk.push_back(QPointF(buf.toDouble(),bufy.toDouble()));
                    }

                }
            }
            else if(fileName[fileName.length()-1]=='c')//для doc формата.
            {
                qDebug()<<"Тут.";
                class graph nov;
                int i=-1;
                while(1)
                {
                    QString buf;
                    buf=in.readLine();
                    QStringList lst = buf.split("\t");
                    buf.toDouble(&ok);
                    if(lst.size()==5)
                    {

                        nov.name=lst.at(0);
                        nov.red=lst.at(1).toInt();
                        nov.green=lst.at(2).toInt();
                        nov.blue=lst.at(3).toInt();
                        nov.pen=lst.at(4).toDouble();
                        addCurve(nov);
                        i++;
                    }
                    else if(lst.size()==2)
                    {   base[i].tchk.push_back(QPointF(lst.at(0).toDouble(),lst.at(1).toDouble()));

                    }
                    if(buf.isEmpty() && lst.size()<=1)
                    {
                        for(int j=0;j<base.size();j++)
                        {
                            base[j].curva->setSamples(base[j].tchk);
                            reshow();
                        }
                        NameOfFile=fileName;
                        QMessageBox::information(this,tr("Done"),tr("Успешно открыто"));
                        break;
                    }
                }
            }
            file.close();
        }
}

void MainWindow::on_actionSave_File_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), "C://",".txt(*.txt);;.doc(*.doc)");
    if (fileName != "")
    {
        bool flag=0;

        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly))
        {
            QTextStream out(&file);
            if(fileName[fileName.length()-1]=='t')
            {
                qDebug()<< "Это .txt" ;
                flag=true;
                for(int i=0; i<base.size(); i++)
                {
                    out << base[i].name << "\n" << base[i].red << "\n" << base[i].green << "\n" << base[i].blue << "\n" << base[i].pen << "\n";
                    for(int j=0; j<base[i].tchk.size();j++)
                        {
                            out<<base[i].tchk[j].x()<<"\n"<<base[i].tchk[j].y()<<"\n";
                            //return;
                        }
                }
            }
            if(fileName[fileName.length()-1]=='c')
            {
                qDebug()<<"Это .doc";
                flag=true;
                for(int i=0; i<base.size(); i++)
                {
                    out << base[i].name << "\t" << base[i].red << "\t" << base[i].green << "\t" << base[i].blue << "\t" << base[i].pen << "\n";
                    for(int j=0; j<base[i].tchk.size();j++)
                        {
                            out<<base[i].tchk[j].x()<<"\t"<<base[i].tchk[j].y()<<"\n";
                            //return;
                        }
                }

            }
            if(!flag)
            {
                qDebug()<<"С таким типо не работаем";

            }
            NameOfFile=fileName;
            QMessageBox::information(this, tr("Done"),tr("Сохранено в %1").arg(NameOfFile));
            file.close();
        }


    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("Задан пустой путь до файла.")); //Типо если файл нельзя читать то ошибко.
        return;
    }

}

void MainWindow::on_actionSave_File_triggered()
{
    if(!NameOfFile.isEmpty())
    {

        QFile file(NameOfFile);
        if (file.open(QIODevice::WriteOnly))
        {
            QTextStream out(&file);
            if(NameOfFile[NameOfFile.length()-1]=='t')
            {
                qDebug()<< "Это .txt" ;

                for(int i=0; i<base.size(); i++)
                {
                    out << base[i].name << "\n" << base[i].red << "\n" << base[i].green << "\n" << base[i].blue << "\n" << base[i].pen << "\n";
                    for(int j=0; j<base[i].tchk.size();j++)
                        {
                            out<<base[i].tchk[j].x()<<"\n"<<base[i].tchk[j].y()<<"\n";
                            //return;
                        }
                }
            }
            if(NameOfFile[NameOfFile.length()-1]=='c')
            {
                qDebug()<<"Это .doc";
                for(int i=0; i<base.size(); i++)
                {
                    out << base[i].name << "\t" << base[i].red << "\t" << base[i].green << "\t" << base[i].blue << "\t" << base[i].pen << "\n";
                    for(int j=0; j<base[i].tchk.size();j++)
                        {
                            out<<base[i].tchk[j].x()<<"\t"<<base[i].tchk[j].y()<<"\n";
                            //return;
                        }
                }

            }
            QMessageBox::information(this, tr("Done"),tr("Сохранено в %1").arg(NameOfFile));
            file.close();
        }
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("Нет имени файла")); //Типо если файл нельзя читать то ошибко.
        return;
    }
}
void MainWindow::AbleUseBlockFree()
{
    int i;
    int WorkingCurve=ui->UserCurve->currentIndex();
    if(ui->UserCurve->count()==0) WorkingCurve=-1;
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

void MainWindow::AddSimbols()
{
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
void MainWindow::AbleUseBlockAdd()
{
    int i;
    int WorkingCurve=ui->UserCurve->currentIndex();
    if(ui->UserCurve->count()==0) WorkingCurve=-1;
    if(WorkingCurve>-1) i=1;
    else i=0;
    if((ui->lineEditY->text().isEmpty())&&(ui->lineEditY->text().isEmpty()))
        ui->add->setEnabled(0);
        else(ui->add->setEnabled(i));
    ui->lineEditX->setEnabled(i);
    ui->lineEditY->setEnabled(i);
}
