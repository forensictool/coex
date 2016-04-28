#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("coex");
    QCoreApplication::setOrganizationName("CompanyCoex");
    QCoreApplication::setOrganizationDomain("www.coex.com");

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
