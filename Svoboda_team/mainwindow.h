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

    void on_btn_refresh_clicked();

    void on_btn_login_clicked();

    void on_tab_base_currentChanged(int index);

private:
    DBManager* m_dbManager;
    Ui::MainWindow *ui;
    QActionGroup *actionGroup;
    QVector<QWidget*> m_hiddenTabs;

    void setupMenuBar();
    void fillTextEdits();
    void authSuccessful();
};

#endif // MAINWINDOW_H
