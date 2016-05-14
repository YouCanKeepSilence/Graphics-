#include "libs.h"

VisualGraph::VisualGraph(QWidget *parent, QVector<graphic *> vector)
{
    setWindowTitle("Вывод графиков");
    QVector <QwtPlotCurve*> curves;
    QwtPlot *gr = new QwtPlot;
    QHBoxLayout *a =new QHBoxLayout;
    a->addWidget(gr);
    setLayout(a);
    gr->setTitle( "Графики" ); // заголовок
    gr->setCanvasBackground( Qt::white ); // цвет фона
    // Параметры осей координат
    gr->setAxisTitle(QwtPlot::yLeft, "Y");
    gr->setAxisTitle(QwtPlot::xBottom, "X");
    gr->insertLegend( new QwtLegend() );
    // #include <qwt_plot_grid.h>
    QwtPlotGrid *grid = new QwtPlotGrid(); //
    grid->setMajorPen(QPen( Qt::gray, 2 )); // цвет линий и толщина
    grid->attach( gr );
    qDebug()<< "ok";
    for(int i=0;i<vector.size();i++)
    {
        curves.push_back(new QwtPlotCurve());
        curves[i]->setTitle(vector[i]->name);
        curves[i]->setPen( Qt::blue, vector[i]->tolshina ); // цвет и толщина кривой
        curves[i]->setRenderHint
                 ( QwtPlotItem::RenderAntialiased, true );
        symbol = new QwtSymbol( QwtSymbol::Ellipse,QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
        curves[i]->setSymbol( symbol );
        curves[i]->setSamples(vector[i]->points);
        curves[i]->attach(gr);

        qDebug()<<i;
    }
    QwtPlotMagnifier *magnifier = new QwtPlotMagnifier(gr->canvas());
        // клавиша, активирующая приближение/удаление
    magnifier->setMouseButton(Qt::MidButton);
    QwtPlotPanner *d_panner = new QwtPlotPanner( gr->canvas() );
    // клавиша, активирующая перемещение
    d_panner->setMouseButton( Qt::RightButton );

}
