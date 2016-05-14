#include "libs.h"

WinMain::WinMain(QWidget *parent) : QDialog(parent)
{
    sost=new QLabel("Тут будут точки");

    name=new QLabel("Введите имя файла и выберете одно из расширений");
    Postr=new QPushButton("Построить");
    //Postr->setEnabled(false);
    ext=new QPushButton("Выход");
    NewGR=new QPushButton("Добавить новый график");
    connect(ext,SIGNAL(clicked()),this,SLOT(close()));
    filename=new QLineEdit;

    //connect(filename,SIGNAL(textChanged(QString)),this,SLOT(FileAdd(QString)));

    res1=new QRadioButton(".txt");
    res2=new QRadioButton(".doc");
    x=new QLineEdit;
    y=new QLineEdit;
    QHBoxLayout *a=new QHBoxLayout;
    a->addWidget(name);
    a->addWidget(filename);

    QHBoxLayout *b=new QHBoxLayout;
    QHBoxLayout *c=new QHBoxLayout;
    QHBoxLayout *d=new QHBoxLayout;

    QVBoxLayout *main=new QVBoxLayout;
    QVBoxLayout *V1=new QVBoxLayout;
    V1->addWidget(res1);
    V1->addWidget(res2);
    QVBoxLayout *V2=new QVBoxLayout;
    V2->addWidget(x);
    V2->addWidget(y);
    b->addLayout(V1);

    b->addLayout(V2);
    c->addWidget(sost);
    d->addWidget(Postr);
    d->addWidget(NewGR);
    d->addWidget(ext);


    main->addLayout(a);
    main->addLayout(b);
    main->addLayout(c);
    main->addLayout(d);

    setLayout(main);
    setWindowTitle("Beta 0.2.3");


    connect(Postr,SIGNAL(clicked()),this,SLOT(PostrClick()));
    connect(NewGR,SIGNAL(clicked()),this,SLOT(NewGr()));


}


void WinMain::NewGr()
{

    if(AddGr!=NULL)
    {
        AddGr->close();
        delete AddGr;
    }
    graphic* buf=new class graphic();
    AddGr=new NewGraphicWindow(this,buf );
    AddGr->show();
    AddGr->exec();
    vec.push_back(buf);
    countGR=vec.size();
}

/*void Win1::FileAdd(QString str)
{
    if(res1->isChecked()||res2->isChecked())//Сначала выбрать формат, потом имя.
        Postr->setEnabled(!str.isEmpty());
}*/




void WinMain::PostrClick()
{
    qDebug()<<vec[0]->points;
    if(mgr!=NULL)
    {
        mgr->close();
        delete mgr;
    }
    mgr=new VisualGraph(this,vec);
    mgr->show();
    mgr->exec();
}





