#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QTimer>
#include <QTextCursor>
#include "peer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int port, const char *server_ip, int server_port, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_As_triggered();

    void on_actionExit_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actioncursortop_triggered();

public slots:
    void printPosition();
    void textDidChange();
    void change(int pos, int del, int add);
    void updateText();

private:
    Ui::MainWindow *ui;
    QString currentFile = "";
    Peer peer;
    QTimer *timer;
    QTextCursor cursor;
    int cursorPos;
public:
    bool update;
    bool update_text;
};

#endif // MAINWINDOW_H
