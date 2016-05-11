#include "mywin.h"

Win1::Win1(QWidget *parent) : QDialog(parent)
{
    sost=new QLabel("Тут будут точки");

    name=new QLabel("Введите имя файла и выберете одно из расширений");
    Postr=new QPushButton("Построить");
    Postr->setEnabled(false);
    ext=new QPushButton("Выход");
    Add=new QPushButton("Add");
    connect(ext,SIGNAL(clicked()),this,SLOT(close()));

    filename=new QLineEdit;
    //filename->setFixedWidth(1000);
    connect(filename,SIGNAL(textChanged(QString)),this,SLOT(FileAdd(QString)));
    //res1=new QCheckBox(".txt");
    //res2=new QCheckBox(".doc");
    res1=new QRadioButton(".txt");
    res2=new QRadioButton(".doc");
    //x=new QSpinBox;
    //y=new QSpinBox;
    x=new QLineEdit;
    y=new QLineEdit;
    //x->setMaximumWidth(100);
    QHBoxLayout *a=new QHBoxLayout;
    a->addWidget(name);
    a->addWidget(filename);
    //sx=new QSpacerItem;
    QHBoxLayout *b=new QHBoxLayout;
    QHBoxLayout *c=new QHBoxLayout;
    QHBoxLayout *d=new QHBoxLayout;
    //QHBoxLayout *e=new QHBoxLayout;
    QVBoxLayout *main=new QVBoxLayout;
    QVBoxLayout *V1=new QVBoxLayout;
    V1->addWidget(res1);
    V1->addWidget(res2);
    QVBoxLayout *V2=new QVBoxLayout;
    V2->addWidget(x);
    V2->addWidget(y);
    b->addLayout(V1);
    //b->addSpacerItem(sx);
    b->addLayout(V2);
    c->addWidget(sost);
    d->addWidget(Postr);
    d->addWidget(Add);
    d->addWidget(ext);

    main->addLayout(a);
    main->addLayout(b);
    main->addLayout(c);
    main->addLayout(d);
    //main->addLayout(e);
    setLayout(main);
    setWindowTitle("Beta 0.0.1");
    //yxjm

    connect(Add,SIGNAL(clicked()),this,SLOT(AddClik()));
    connect(Postr,SIGNAL(clicked()),this,SLOT(PostrClick()));



}

void Win1::FileAdd(QString str)
{
    if(res1->isChecked()||res2->isChecked())//Сначала выбрать формат, потом имя.
        Postr->setEnabled(!str.isEmpty());
}


void Win1::AddClik()
{
    static int i=0;

      qDebug()<<i;

    points<<QPointF(x->text().toInt(),y->text().toInt());
    if(i==0)
    {
        vec.push_back(points);
    }
    i++;
    vec[0]=points;
    qDebug()<<i;
    //vec[0]=points;
    qDebug() << vec;
    qDebug() << points;

}
void Win1::PostrClick()
{
    if(mgr!=NULL)
    {
        mgr->close();
        delete mgr;
    }
    mgr=new graph(this,points);
    mgr->show();
    mgr->exec();
}

graph::graph(QWidget *parent,QPolygonF point)
{
    QwtPlot *gr = new QwtPlot;
    QHBoxLayout *a =new QHBoxLayout;
    a->addWidget(gr);
    setLayout(a);
    gr->setTitle( "Qwt demonstration" ); // заголовок
    gr->setCanvasBackground( Qt::white ); // цвет фона
    // Параметры осей координат
    gr->setAxisTitle(QwtPlot::yLeft, "Y");
    gr->setAxisTitle(QwtPlot::xBottom, "X");
    gr->insertLegend( new QwtLegend() );
    // #include <qwt_plot_grid.h>
        QwtPlotGrid *grid = new QwtPlotGrid(); //
        grid->setMajorPen(QPen( Qt::gray, 2 )); // цвет линий и толщина
        grid->attach( gr );
    curve= new QwtPlotCurve();
    curve->setTitle( "Demo Curve" );
    curve->setPen( Qt::blue, 6 ); // цвет и толщина кривой
    curve->setRenderHint
             ( QwtPlotItem::RenderAntialiased, true );
    symbol = new QwtSymbol( QwtSymbol::Ellipse,QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
    curve->setSymbol( symbol );
    curve->setSamples(point);
    curve->attach(gr);
    QwtPlotMagnifier *magnifier = new QwtPlotMagnifier(gr->canvas());
        // клавиша, активирующая приближение/удаление
    magnifier->setMouseButton(Qt::MidButton);
    QwtPlotPanner *d_panner = new QwtPlotPanner( gr->canvas() );
    // клавиша, активирующая перемещение
    d_panner->setMouseButton( Qt::RightButton );

}

void graph::makeme()
{

}

