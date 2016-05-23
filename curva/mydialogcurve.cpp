#include "mydialogcurve.h"
#include "mainwindow.h"
MyNewCurve::MyNewCurve(class graph &nov,QWidget *parent)
{
    curva=&nov;
    text=new QLabel("&Enter");
    name=new QLineEdit;
    text->setBuddy(name);
    Lname=new QHBoxLayout;
    Lname->addWidget(text);
    Lname->addWidget(name);
    ok=new QPushButton("&ok");
    ok->setEnabled(0);
    cancel=new QPushButton("&cancel");
    LPushButton=new QHBoxLayout;
    LPushButton->addWidget(ok);
    LPushButton->addWidget(cancel);

    TextRed=new QLabel("&Red");
    BoxRed=new QSpinBox;
    BoxRed->setRange(0,256);
    TextRed->setBuddy(BoxRed);
    LRed=new QHBoxLayout;
    LRed->addWidget(TextRed);
    LRed->addWidget(BoxRed);

    TextGreen=new QLabel("&Green");
    BoxGreen=new QSpinBox;
    BoxGreen->setRange(0,256);
    TextGreen->setBuddy(BoxGreen);
    LGreen=new QHBoxLayout;
    LGreen->addWidget(TextGreen);
    LGreen->addWidget(BoxGreen);

    TextBlue=new QLabel("&Blue");
    BoxBlue=new QSpinBox;
    BoxBlue->setRange(0,256);
    TextBlue->setBuddy(BoxBlue);
    LBlue=new QHBoxLayout;
    LBlue->addWidget(TextBlue);
    LBlue->addWidget(BoxBlue);

    TextThickness=new QLabel("&Ширина");
    BoxThickness=new QDoubleSpinBox;
    BoxThickness->setRange(0.5,10);
    TextThickness->setBuddy(BoxThickness);
    LThickness=new QHBoxLayout;
    LThickness->addWidget(TextThickness);
    LThickness->addWidget(BoxThickness);

    Final=new QVBoxLayout;
    Final->addLayout(Lname);
    Final->addLayout(LRed);
    Final->addLayout(LGreen);
    Final->addLayout(LBlue);
    Final->addLayout(LThickness);
    Final->addLayout(LPushButton);
    //доступность книпки ok
    connect(name,SIGNAL(textChanged(QString)),this,SLOT(TextChanged(QString)));
    //выход с 0
    connect(cancel,SIGNAL(clicked()),this,SLOT(reject()));
    //выход с 1
    connect(ok,SIGNAL(clicked()),this,SLOT(OkClicked()));
    setLayout(Final);
}

void MyNewCurve::OkClicked()
{//заполнение переданного объекта типа class graph
    this->accept();
    curva->name=name->text();
    curva->red=BoxRed->value();
    curva->green=BoxGreen->value();
    curva->blue=BoxBlue->value();
    curva->pen=BoxThickness->value();
}

void MyNewCurve::TextChanged(QString str)
{
    ok->setEnabled(!str.isEmpty());// isEmpty -пустая или нет
}


MyDeleteCurve::MyDeleteCurve(QWidget *parent, QString name)
{

    text=new QLabel("Удалить кривую : "+ name +" ?");
    this->setWindowTitle("Delete curve");
    ok=new QPushButton("Удалить");
    cancel=new QPushButton("Отмена");
    Lone=new QHBoxLayout;
    Lone->addWidget(text);
    Ltwo=new QHBoxLayout;
    Ltwo->addWidget(ok);
    Ltwo->addWidget(cancel);
    Final=new QVBoxLayout;
    Final->addLayout(Lone);
    Final->addLayout(Ltwo);
    setLayout(Final);
    connect(ok,SIGNAL(clicked(bool)),this,SLOT(accept()));
    connect(cancel,SIGNAL(clicked(bool)),this,SLOT(reject()));

};
