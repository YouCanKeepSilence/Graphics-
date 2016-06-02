#include "mainwindow.h"
#include "mydialogcurve.h"
#include "workwithfiles.h"

void Txt::SaveTo(bool &flag, QFile &file, QVector<graph> &FF)
{
    QTextStream out(&file);
    for(int i=0; i<FF.size(); i++)
    {
        out << FF[i].name << "\n" << FF[i].red << "\n" << FF[i].green << "\n" << FF[i].blue << "\n" << FF[i].pen << "\n";
        for(int j=0; j<FF[i].tchk.size();j++)
            out<<FF[i].tchk[j].x()<<"\n"<<FF[i].tchk[j].y()<<"\n";
    }
    flag=true;

}
void Txt::AppendTo(bool &flag, QFile &file,graph &FF)
{

    QTextStream out(&file);
    out << FF.name << "\n" << FF.red << "\n" << FF.green << "\n" << FF.blue << "\n" << FF.pen << "\n";
    for(int j=0; j<FF.tchk.size();j++)
        out<<FF.tchk[j].x()<<"\n"<<FF.tchk[j].y()<<"\n";
    flag=true;
}
void Txt::ReadFrom(bool &flag, QFile &file,QVector <graph> &FF)
{
    bool ok;
    QTextStream in(&file);
    class graph nov;
    int i=-1;
    while(1)
    {
        QString buf;
        buf=in.readLine();
        if(buf.isEmpty())
        {

            flag=true;
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
            //addCurve(nov);
            FF.push_back(nov);
            i++;
        }
        else
        {
            QString bufy;
            bufy=in.readLine();
            FF[i].tchk.push_back(QPointF(buf.toDouble(),bufy.toDouble()));
        }

    }
}
void Txt::ReadOneFrom(bool &flag, QFile &file,graph &FF)
{
    QTextStream in(&file);
    //class graph nov;
    QString buf;
    buf=in.readLine();
    FF.name=buf;
    buf=in.readLine();
    FF.red=buf.toInt();
    buf=in.readLine();
    FF.green=buf.toInt();
    buf=in.readLine();
    FF.blue=buf.toInt();
    buf=in.readLine();
    FF.pen=buf.toDouble();
    //addCurve(FF);
    bool ok;
    while(1)
    {
        buf=in.readLine();
        buf.toDouble(&ok);
        if(buf.isEmpty() || ok==false)
            break;
        QString bufy;
        bufy=in.readLine();
        FF.tchk.push_back(QPointF(buf.toDouble(),bufy.toDouble()));
    }

    flag=true;
}
void Doc::ReadFrom(bool &flag, QFile &file,QVector <graph> &FF)
{
    class graph nov;
    QTextStream in(&file);
    int i=-1;
    while(1)
    {
        QString buf;
        buf=in.readLine();
        QStringList lst = buf.split("\t");
        if(lst.size()==5)
        {
            nov.name=lst.at(0);
            nov.red=lst.at(1).toInt();
            nov.green=lst.at(2).toInt();
            nov.blue=lst.at(3).toInt();
            nov.pen=lst.at(4).toDouble();
            FF.push_back(nov);
            i++;
        }
        else if(lst.size()==2)
        {
            FF[i].tchk.push_back(QPointF(lst.at(0).toDouble(),lst.at(1).toDouble()));
        }
        if(buf.isEmpty() && lst.size()<=1)
        {
            flag=true;
            break;
        }
    }
}
void Doc::SaveTo(bool &flag, QFile &file, QVector<graph> &FF)
{
    QTextStream out(&file);
    for(int i=0; i<FF.size(); i++)
    {
        out << FF[i].name << "\t" << FF[i].red << "\t" << FF[i].green
            << "\t" << FF[i].blue << "\t" << FF[i].pen << "\n";
        for(int j=0; j<FF[i].tchk.size();j++)
            out<<FF[i].tchk[j].x()<<"\t"<<FF[i].tchk[j].y()<<"\n";
    }
    flag=true;

}
void Doc::ReadOneFrom(bool &flag, QFile &file, graph &FF)
{
    QTextStream in(&file);
    QString buf;
    buf=in.readLine();
    QStringList lst = buf.split("\t");
    FF.name=lst.at(0);
    FF.red=lst.at(1).toInt();
    FF.green=lst.at(2).toInt();
    FF.blue=lst.at(3).toInt();
    FF.pen=lst.at(4).toDouble();
    while(1)
    {
        buf=in.readLine();
        QStringList lst1;
        lst1=buf.split("\t");
        if((buf.isEmpty() && lst1.size()<=1) || lst1.size()==5)
            break;
        FF.tchk.push_back(QPointF(lst1.at(0).toDouble(),lst1.at(1).toDouble()));
    }
    flag=true;
}
void Doc::AppendTo(bool &flag, QFile &file, graph &FF)
{
    QTextStream out(&file);
    out << FF.name << "\t" << FF.red << "\t" << FF.green << "\t" << FF.blue << "\t" << FF.pen << "\n";
    for(int j=0; j<FF.tchk.size();j++)
            out<<FF.tchk[j].x()<<"\t"<<FF.tchk[j].y()<<"\n";
    flag=true;

}
