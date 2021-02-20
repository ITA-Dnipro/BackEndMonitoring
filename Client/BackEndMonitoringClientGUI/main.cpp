#include "CMainWindow.h"
#include "CConnectionDialog.h"
#include "QDebug"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CMainWindow w;
    w.show();

    int res = 0;

    res = a.exec();
    qDebug("ended");
    return res;
}
