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
    bool application_change = true;
    cursor = ui->textEdit->textCursor();
    // connect( ui->textEdit->document(), &QTextDocument::contentsChange, this->change(int, int, int)));
    connect(ui->textEdit->document(), &QTextDocument::contentsChange,
    [=, &application_change](int pos, int del, int add){
        // std::cout << "Update_text: " << this->update_text << std::endl;
        if (this->update_text) {
            this->update_text = false;
        } else {
            // std::cout << "change - pos: " << pos << ", del: " << del << ", add: " << add << std::endl;
            if (del == 0 && add == 1) {
                QString added = ui->textEdit->toPlainText().mid(pos,add);
                // std::cout << added.toStdString() << std::endl;
                Item item = peer.crdt.LocalInsert(added.toStdString()[0], pos);
                char* data = (char*) malloc(1024);
                data = item.Serialize(true);
                Item itemasu(data);
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
    });
    timer->setInterval(100); // one second
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

void MainWindow::printPosition() {
    // std::cout << ui->textEdit->textCursor().position() << std::endl;
}

void MainWindow::on_actioncursortop_triggered()
{
    QTextCursor c(ui->textEdit->textCursor());
    c.setPosition(3);
    c.deleteChar();
    c.insertText(QString("ø"));
    c.insertText(QString("∫"));
    ui->textEdit->setTextCursor(c);
}

void MainWindow::textDidChange() {
    // std::cout << "textdidchange\n";
}

void MainWindow::contentsChange(int pos, int del, int add) {
    // std::cout << "content: " << pos << " " << del << " " << add << std::endl;
}

void MainWindow::change(int pos, int del, int add) {
    // std::cout << "change - pos: " << pos << ", del: " << del << ", add: " << add << std::endl;
    if (!this->update) {
        if (del == 0 && add == 1) {
            QString added = ui->textEdit->toPlainText().mid(pos,add);
            // std::cout << added.toStdString() << std::endl;
            Item item = peer.crdt.LocalInsert(added.toStdString()[0], pos);
            char* data = (char*) malloc(1024);
            data = item.Serialize(true);
            Item itemasu(data);
            uint32_t act;
            memcpy(&act, data, 4);
            int size = 4 + 1 + 4 + 4 + (item.uid.global_index.size() * 4);
            //    std::cout << "jembut " << act << std::endl;
            //    std::cout << "kentuuuu " << itemasu.value << std::endl;
            peer.Send(item.Serialize(true), size);
        } else if (add == 0 && del == 1) {
            //    std::cout << pos << "ewe" << std::endl;
            Item item = peer.crdt.LocalDelete(pos);
            int size = 4 + 1 + 4 + 4 + (item.uid.global_index.size() * 4);
            peer.Send(item.Serialize(false), size);
        }
        cursor = ui->textEdit->textCursor();
    }
}

void MainWindow::updateText() {
    // std::cout << "UPDATE: " << this->update << std::endl;
    if (this->update) {
        this->update_text = true;
        std::string new_str = peer.crdt.GetString();
        ui->textEdit->setText(QString(new_str.c_str()));
        this->update = false;
        ui->textEdit->setTextCursor(cursor);
    }
}
