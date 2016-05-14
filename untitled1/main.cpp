#include <QApplication>
#include "libs.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WinMain *Wind=new WinMain(0);
    Wind->show();

    return a.exec();
}
