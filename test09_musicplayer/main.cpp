#include "playmainwindow.h"
#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    PlayMainWindow w;
//    w.show();
    //修改起始页面
    LoginDialog l;
    l.show();
    return a.exec();
}
