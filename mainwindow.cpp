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
    writefile();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(),this->geometry().height());
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
    ui->log->clear();
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
