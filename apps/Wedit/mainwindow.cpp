#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(int port, const char *server_ip, int server_port, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    peer(port, server_ip, server_port, this),
    timer(new QTimer)
{
    this->update = false;
    this->update_text = false;
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

    // Initialize Cursor
    cursor = ui->textEdit->textCursor();
    cursorPos = cursor.position();

    connect( ui->textEdit->document(), SIGNAL(contentsChange(int,int,int)), this, SLOT(change(int,int,int)));
    timer->setInterval(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateText()));
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::printPosition(){};

void MainWindow::textDidChange(){};

void MainWindow::on_actioncursortop_triggered()
{
    QTextCursor c(ui->textEdit->textCursor());
    c.setPosition(3);
    c.deleteChar();
    c.insertText(QString("ø"));
    c.insertText(QString("∫"));
    ui->textEdit->setTextCursor(c);
}

void MainWindow::change(int pos, int del, int add) {
    if (this->update_text) {
        this->update_text = false;
    } else {
        if (del == 0 && add == 1) {
            QString added = ui->textEdit->toPlainText().mid(pos,add);
            Item item = peer.crdt.LocalInsert(added.toStdString()[0], pos);
            char* data = (char*) malloc(1024);
            data = item.Serialize(true);
            uint32_t act;
            memcpy(&act, data, 4);
            int size = 4 + 1 + 4 + 4 + 4 + (item.uid.global_index.size() * 4);
            peer.Send(item.Serialize(true), size);
        } else if (add == 0 && del == 1) {
            Item item = peer.crdt.LocalDelete(pos);
            int size = 4 + 1 + 4 + 4 + 4 + (item.uid.global_index.size() * 4);
            peer.Send(item.Serialize(false), size);
        }
    }
}

void MainWindow::updateText() {
    cursor = ui->textEdit->textCursor();
    cursorPos = cursor.position();
    if (this->update) {
        this->update_text = true;
        std::string new_str = peer.crdt.GetString();
        ui->textEdit->setText(QString(new_str.c_str()));
        this->update = false;
        cursor.setPosition(cursorPos);
        ui->textEdit->setTextCursor(cursor);
    }
}
