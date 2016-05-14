#include "file.h"

const QString allFileToString(QFile &aFile)
{
    if (!aFile.open(QFile::ReadOnly | QFile::Text)) {
        std::cout << "Error opening file!" << std::endl;
        return NULL;
    }
    QTextStream in(&aFile);
    return in.readAll();
}

void setDataToVector(const QStringList &aStringList,
                     QVector< QVector <double> > &aVector)
{
    size_t x = aStringList.size() - 1; // Count of line, 8
    size_t y = aStringList.at(0).count("\t") + 1; // Count of digits in line, 6

    for (size_t i = 0; i < x; ++i) {
        QVector<double> temp_vector;
        for (size_t j = 0; j < y; ++j) {
            temp_vector.push_back(aStringList.at(i).split("\t").at(j).toDouble());
        }
        aVector.push_back(temp_vector);
    }
}

void fun(const QVector< QVector <double> > &buf,QVector <QPolygonF> &FinalV)
{
    //QPolygonF nabor();
    for (int i = 0; i < buf.size(); i++) {
        FinalV.push_back(QPolygonF());
        for (int j = 0; j < buf.at(i).size(); j+=2) {
        FinalV[FinalV.size()-1]<<QPointF(buf.at(i).at(j),buf.at(i).at(j+1));
        }
    }
}


int SetFromFile(QString name,QVector <QPolygonF> &vector)
{
    QVector< QVector <double> > buf;
    QFile file(name);
vector.push_back(QPolygonF());
    setDataToVector(allFileToString(file).split("\n"), buf);
   // fun(buf,vector);
    return 0;
}
