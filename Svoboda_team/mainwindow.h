#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QActionGroup>

#include "dbmanager.h"

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

    void on_actionDiffnes_triggered();

    void on_actionMedize_triggered();

private:
    Ui::MainWindow *ui;
    DBManager* m_dbManager;
    QActionGroup *actionGroup;

    void setupMenuBar();
};

#endif // MAINWINDOW_H
