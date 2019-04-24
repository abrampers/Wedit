#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        puts("Usage: ./wedit <PORT>");
        exit(1);
    }

    QApplication a(argc, argv);
    MainWindow w(stoi(argv[1]));
    w.show();

    return a.exec();
}
