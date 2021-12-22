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

    void on_actionLogin_triggered();

    void on_actionLogout_triggered();

    void on_calendar_endDate_selectionChanged();

    void on_calendar_startDate_selectionChanged();

    void on_btn_reqAbsence_clicked();

    void on_btn_reqUnpaidAbsence_clicked();

    void on_btn_reqSickness_clicked();

    void on_btn_req70PctSickness_clicked();

private:
    DBManager* m_dbManager;
    Ui::MainWindow *ui;
    QActionGroup *actionGroup;
    QVector<QWidget*> m_hiddenTabs;
    int m_selectedDaysCount;

    void setupMenuBar();
    void fillTextEdits();
    void authSuccessful();
    void showLoginScreen();
    void updateDaysCount();
    void updateSickness(LeaveType);
};

#endif // MAINWINDOW_H
