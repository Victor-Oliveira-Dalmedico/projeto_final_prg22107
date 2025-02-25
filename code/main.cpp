#include "helloqt.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HelloQT window1;
    window1.show();

    return a.exec();
}
