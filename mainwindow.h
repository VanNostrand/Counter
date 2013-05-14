#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_plusButton_clicked();

    void on_minusButton_clicked();

    void on_resetButton_clicked();

    void on_setButton_clicked();

    void on_fileButton_clicked();

    void on_plusTwo_clicked();

    void on_plusThree_clicked();

    void on_plusFour_clicked();

    void on_minusTwo_clicked();

    void on_minusThree_clicked();

    void on_minusFour_clicked();

    void on_minusFive_clicked();

    void on_plusFive_clicked();

private:
    Ui::MainWindow *ui;
    void update(double);
    void decorate();
    void writefile();
};

#endif // MAINWINDOW_H
