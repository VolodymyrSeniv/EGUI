#include "mainwindow.h"
#include <stdio.h>
#include <QApplication>
#include <fstream>
#include <QDebug>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
