#include "tskmngr.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    tskMngr w;
    w.show();
    return a.exec();
}
