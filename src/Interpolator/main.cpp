#include "mainwindow.h"
#include <QApplication>

#define ORG_NAME "scientificsoft"
#define ORG_DOMAIN "scienfic.soft"
#define APP_NAME "Interpolator"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QCoreApplication::setOrganizationName(ORG_NAME);
    QCoreApplication::setOrganizationDomain(ORG_DOMAIN);
    QCoreApplication::setApplicationName(APP_NAME);

    return a.exec();
}
