#include <QDateTime>
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
    QDateTime dateTime = QDateTime::currentDateTime();
    double value = ui->lcd->value();
    double diff = -1*(value - v);
    QString sgn = "";
    if(diff >= 0)
        sgn = "+";

    ui->log->appendPlainText(dateTime.toString("yyyy-MM-ddThh:mm:ss") + "\t" +
                             QString::number((int) value) + QString::fromUtf8(" \u21A6 ") + QString::number((int) v) + "\t(" + sgn + QString::number((int) diff) + ")");
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
    palette = new QPalette();
    decorate();
}

MainWindow::~MainWindow()
{
    delete palette;
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
    ui->log->clear();
    decorate();
    writefile();
}

void MainWindow::on_fileButton_clicked()
{
    ui->path->setText(QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Textfiles (*.txt)")));
}

void MainWindow::on_addButton_clicked()
{
    update(ui->lcd->value() + ui->addValue->value());
}
