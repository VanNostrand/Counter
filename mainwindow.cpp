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
    QDateTime dateTime = QDateTime::currentDateTime();
    double value = ui->lcd->value();
    ui->log->appendPlainText(dateTime.toString("yyyy-MM-ddThh:mm:ss") + "    " +
                             QString::number((int) value) + " -> " + QString::number((int) value + 1) + "    (+1)");
    ui->lcd->display(value + 1);
    writefile();
}

void MainWindow::on_minusButton_clicked()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    double value = ui->lcd->value();
    ui->log->appendPlainText(dateTime.toString("yyyy-MM-ddThh:mm:ss") + "    " +
                             QString::number((int) value) + " -> " + QString::number((int) value - 1) + "    (-1)");
    ui->lcd->display(value - 1);
    writefile();
}

void MainWindow::on_setButton_clicked()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    double value = ui->lcd->value();
    double setvalue = ui->setvalue->value();
    QString mod = "";
    if(value > setvalue) {
        mod = "    (-" + QString::number((int) value - setvalue) + ")";
    } else {
        if(value < setvalue) {
            mod = "    (+" + QString::number((int) setvalue - value) + ")";
        }
    }
    ui->log->appendPlainText(dateTime.toString("yyyy-MM-ddThh:mm:ss") + "    " +
                             QString::number((int) value) + " -> " + QString::number((int) setvalue) + mod);
    ui->lcd->display(setvalue);
    writefile();
}

void MainWindow::on_resetButton_clicked()
{
    ui->lcd->display(ui->resetValue->value());
    ui->log->clear();
    writefile();
}

void MainWindow::on_fileButton_clicked()
{
    ui->path->setText(QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    QDir::homePath(),
                                                    tr("Textfiles (*.txt)")));
}
