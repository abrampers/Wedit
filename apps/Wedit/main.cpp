#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    if (argc != 4) {
        puts("Usage: ./wedit <PEER_PORT> <SERVER_IP> <SERVER_PORT>");
        exit(1);
    }

    QApplication a(argc, argv);
    MainWindow w(stoi(argv[1]), argv[2], stoi(argv[3]));
    w.show();

    return a.exec();
}
