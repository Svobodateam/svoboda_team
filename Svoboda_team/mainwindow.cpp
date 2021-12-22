#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_dbManager(new DBManager()),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
    setupMenuBar();

    m_hiddenTabs.push_back(ui->tab_balances);
    m_hiddenTabs.push_back(ui->tab_requests);
    ui->tab_base->removeTab(ui->tab_base->indexOf(ui->tab_balances));
    ui->tab_base->removeTab(ui->tab_base->indexOf(ui->tab_requests));
}

void MainWindow::setupMenuBar() {

    actionGroup = new QActionGroup(this);
    actionGroup->setExclusive(true);
    ui->menuTheme->actions().first()->setChecked(true);
    for (int i = 0; i < ui->menuTheme->actions().size(); ++i) {
        actionGroup->addAction(ui->menuTheme->actions()[i]);
    }
    on_actionDiffnes_triggered();
}

MainWindow::~MainWindow() {
    delete m_dbManager;
    delete ui;
}

void MainWindow::on_actionDiffnes_triggered()
{
    QFile file(":/themes/diffnes.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->widget->setStyleSheet(styleSheet);
    file.close();
}

void MainWindow::on_actionMedize_triggered()
{
    QFile file(":/themes/medize.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->widget->setStyleSheet(styleSheet);
    file.close();
}


void MainWindow::on_btn_refresh_clicked() {

    m_dbManager->refreshLeaveCount();
    fillTextEdits();
}

void MainWindow::fillTextEdits() {

    User* user = m_dbManager->getCurrentUser();
    ui->edit_vacation->setText(QString::number(user->leavesCount[LeaveType::Vacation]));
    ui->edit_unpaidVacation->setText(QString::number(user->leavesCount[LeaveType::UnpaidVacation]));
    ui->edit_sickness->setText(QString::number(user->leavesCount[LeaveType::Sickness100]));
    ui->edit_70PctSickness->setText(QString::number(user->leavesCount[LeaveType::Sickness75]));
}

void MainWindow::authSuccessful() {

    ui->tab_base->insertTab(3, m_hiddenTabs.last(), "Balances");
    m_hiddenTabs.removeLast();
    ui->tab_base->insertTab(3, m_hiddenTabs.last(), "Requests");
    m_hiddenTabs.removeLast();
    m_hiddenTabs.push_back(ui->tab_auth);
    ui->tab_base->removeTab(0);
}

void MainWindow::on_btn_login_clicked() {

    ui->lbl_error->clear();
    if (!m_dbManager->authorizeUser(ui->edit_username->text())) {
        ui->lbl_error->setText("User is unavailable! Try another username.");
        return;
    }
    authSuccessful();
}

void MainWindow::on_tab_base_currentChanged(int index) {

    if (ui->tab_base->indexOf(ui->tab_requests) == index) {
        on_btn_refresh_clicked();
    }
}
