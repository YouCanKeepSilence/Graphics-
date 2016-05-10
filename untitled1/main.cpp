#include <QApplication>
#include "mywin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Win1 *Wind=new Win1(0);
    Wind->show();

    return a.exec();
}
