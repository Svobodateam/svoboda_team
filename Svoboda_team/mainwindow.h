#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDebug>
#include <QFile>

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

    void on_actionAqua_triggered();

    void on_actionBlue_triggered();

    void on_actionmacOS_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
