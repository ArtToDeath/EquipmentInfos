#include "mainwidget.h"
#include <QApplication>

/**
 * 错误崩溃记录：The inferior stopped because it received a signal from the Operating System.
 * 程序有空指针
 */
int main(int argc, char *argv[])
{
    if(!createXml()) return 0;

    QApplication a(argc, argv);

    MainWidget w;
    w.show();

    return a.exec();
}
