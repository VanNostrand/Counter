#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::writefile() {
    if(ui->path->text() != "File" && ui->path->text() != "") {
        QFile file(ui->path->text());
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        out << ui->lcd->value();
        // optional, as QFile destructor will already do it:
        file.close();
    }
}

void MainWindow::decorate() {
    ui->lcd->setAutoFillBackground(true);
    QPalette* palette = new QPalette();
    palette->setColor(QPalette::Window,Qt::lightGray);

    double value = ui->lcd->value();
    ushort cases = 0;

    if(value < 15) cases = 4;
    if(value < 10) cases = 5;
    if(value <= 5) cases = 1;
    if(value <= 0) cases = 2;
    if(value <= -5) cases = 99;

    if(value >= 15) cases = 3;
    if(value > 20) cases = 6;
    if(value >= 50) cases = 7;
    if(value >= 100) cases = 8;

    switch(cases) {
        case 1:     palette->setColor(QPalette::WindowText,Qt::red);        break;
        case 2:     palette->setColor(QPalette::WindowText,Qt::darkRed);    break;
        case 3:     palette->setColor(QPalette::WindowText,Qt::green);      break;
        case 4:     palette->setColor(QPalette::WindowText,Qt::yellow);     break;
        case 5:     palette->setColor(QPalette::WindowText,Qt::magenta);    break;
        case 6:     palette->setColor(QPalette::WindowText,Qt::blue);       break;
        case 7:     palette->setColor(QPalette::WindowText,Qt::cyan);       break;
        case 8:     palette->setColor(QPalette::WindowText,Qt::white);      break;
        default:    palette->setColor(QPalette::WindowText,Qt::black);
    }

    ui->lcd->setPalette(*palette);
}

void MainWindow::update(double v) {
    ui->lcd->display(v);
    decorate();
    writefile();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(),this->geometry().height());
    decorate();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_plusButton_clicked()
{
    update(ui->lcd->value() + 1);
}

void MainWindow::on_minusButton_clicked()
{
    update(ui->lcd->value() - 1);
}

void MainWindow::on_setButton_clicked()
{
    update(ui->setValue->value());
}

void MainWindow::on_resetButton_clicked()
{
    ui->lcd->display(ui->resetValue->value());
    decorate();
    writefile();
}

void MainWindow::on_fileButton_clicked()
{
    ui->path->setText(QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Textfiles (*.txt)")));
}

void MainWindow::on_plusTwo_clicked()
{
    update(ui->lcd->value() + 2);
}

void MainWindow::on_plusThree_clicked()
{
    update(ui->lcd->value() + 3);
}

void MainWindow::on_plusFour_clicked()
{
    update(ui->lcd->value() + 4);
}

void MainWindow::on_plusFive_clicked()
{
    update(ui->lcd->value() + 5);
}

void MainWindow::on_minusTwo_clicked()
{
    update(ui->lcd->value() - 2);
}

void MainWindow::on_minusThree_clicked()
{
    update(ui->lcd->value() - 3);
}

void MainWindow::on_minusFour_clicked()
{
    update(ui->lcd->value() - 4);
}

void MainWindow::on_minusFive_clicked()
{
    update(ui->lcd->value() - 5);
}

