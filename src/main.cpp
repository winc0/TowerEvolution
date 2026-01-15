#include "include/mainwindow.h"

#include <QApplication>
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("TowerDefenseStudio");
    QCoreApplication::setApplicationName("TowerDefenseGame");

    qDebug() << "Application starting...";

    MainWindow w;
    qDebug() << "MainWindow created, showing...";
    w.show();

    qDebug() << "Application running";
    return a.exec();
}
