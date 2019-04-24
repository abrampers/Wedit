#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(int port, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    peer(port, this)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    connect( ui->textEdit->document(), SIGNAL(contentsChange(int,int,int)), this, SLOT(change(int,int,int)));
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

}

void MainWindow::change(int pos, int del, int add) {
    // std::cout << pos << " " << del << " " << add << std::endl;
   if (del == 0 && add != 0) {
       QString added = ui->textEdit->toPlainText().mid(pos,add);
       std::cout << added.toStdString() << std::endl;
       Item item = peer.crdt.LocalInsert(added.toStdString()[0], pos);
       char* data = (char*) malloc(1024);
       data = item.Serialize(true);
       Item itemasu(data);
       uint32_t act;
       memcpy(&act, data, 4);
       int size = 4 + 1 + 4 + 4 + (item.uid.global_index.size() * 4);
       std::cout << "jembut " << act << std::endl;
       std::cout << "kentuuuu " << itemasu.value << std::endl;
       peer.Send(item.Serialize(true), size);
   } else if (add == 0 && del != 0) {
       std::cout << pos << "ewe" << std::endl;
       Item item = peer.crdt.LocalDelete(pos);
       int size = 4 + 1 + 4 + 4 + (item.uid.global_index.size() * 4);
       peer.Send(item.Serialize(false), size);
   }
}

void MainWindow::setText(std::string s) {
    ui->textEdit->setText(QString(s.c_str()));
}
