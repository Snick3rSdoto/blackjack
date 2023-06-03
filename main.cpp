#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QMultiMap>
#include <QString>
#include <QDebug>
#include <ctime>

int main(int argc, char *argv[])
{
    srand(static_cast<unsigned int>(time(nullptr)));

    QApplication a(argc, argv);


    MainWindow w;
    w.show();

    return a.exec();
}
