#include "libs.h"

NewGraphicWindow::NewGraphicWindow(QWidget *parent,class graphic *work)
{
    nameline=new QLabel("Введите имя прямой");
    nameenter=new QLineEdit();
    yname=new QLabel("Введите Y:");
    xname=new QLabel("Введите X:");
    yenter= new QLineEdit();
    xenter= new QLineEdit();
    AddPoint=new QPushButton("Добавить точку");
    //Тут что-нибудь с цветом...
    nametolshina=new QLabel("Выберете толщину:");
    toshinaenter=new QSpinBox();
    WhatPoints=new QLabel("Тут будут точки выводится");
    AddGraph=new QPushButton("Добавить прямую");
    AddGraph->setEnabled(false);
    Cancel=new QPushButton("Отмена");
    QHBoxLayout *a , *b, *c, *d, *i, *f;
    QVBoxLayout *itog;
    a=new QHBoxLayout();
    a->addWidget(nameline);
    a->addWidget(nameenter);
    b=new QHBoxLayout();
    b->addWidget(xname);
    b->addWidget(xenter);
    b->addWidget(yname);
    b->addWidget(yenter);
    c=new QHBoxLayout();
    c->addWidget(AddPoint);
    d=new QHBoxLayout();
    d->addWidget(nametolshina);
    d->addWidget(toshinaenter);
    i=new QHBoxLayout();
    i->addWidget(WhatPoints);
    f=new QHBoxLayout();
    f->addWidget(AddGraph);
    f->addWidget(Cancel);
    itog=new QVBoxLayout;
    itog->addLayout(a);
    itog->addLayout(b);
    itog->addLayout(c);
    itog->addLayout(d);
    itog->addLayout(i);
    itog->addLayout(f);
    setLayout(itog);
    connect(AddPoint,SIGNAL(clicked()),this,SLOT(AddPointClicked()));
    connect(nameenter,SIGNAL(textEdited(QString)),this,SLOT(EnableAddGraph()));
    connect(AddGraph,SIGNAL(clicked(bool)),this,SLOT(AddGraphClicked()));
    inwork=work;
    setWindowTitle("Добавление графика.");
}

void NewGraphicWindow::AddGraphClicked()
{
    QMessageBox *ok;
    inwork->name=QString(nameenter->text());
    inwork->points=localpoint;
    inwork->tolshina=toshinaenter->value();
    inwork->color=Qt::red;
    ok=new QMessageBox(this);
    ok->setText("Done.");
    ok->show();
    ok->exec();
    this->close();
}

void NewGraphicWindow::EnableAddGraph()
{
    AddGraph->setEnabled(((!nameenter->text().isEmpty()) && (localpoint.size()!=0)));
}

void NewGraphicWindow::AddPointClicked()
{
    localpoint<<QPointF(xenter->text().toDouble(),yenter->text().toDouble());
    qDebug()<<localpoint;
}
