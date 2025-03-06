#include "RRR.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    RRR window1;
    window1.show();

    return a.exec();
}
