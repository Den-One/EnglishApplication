#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication *a = new QApplication(argc, argv);

    //WebManager* myObject = new WebManager(a);
    //myObject->TestConnection();

    MainWindow w;
    w.show();
    return a->exec();
}
