#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_dbManager(new DBManager()),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
    setupMenuBar();
    showLoginScreen();
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

void MainWindow::on_actionDiffnes_triggered() {

    QFile file(":/themes/diffnes.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->widget->setStyleSheet(styleSheet);
    file.close();
}

void MainWindow::on_actionMedize_triggered() {

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

    ui->edit_username->clear();

    ui->actionLogin->setVisible(false);
    ui->actionLogout->setVisible(true);

    ui->tab_base->insertTab(3, m_hiddenTabs.last(), "Balances");
    m_hiddenTabs.removeLast();
    ui->tab_base->insertTab(3, m_hiddenTabs.last(), "Requests");
    m_hiddenTabs.removeLast();

    m_hiddenTabs.push_back(ui->tab_auth);
    ui->tab_base->removeTab(0);

    on_btn_refresh_clicked();
}

void MainWindow::showLoginScreen() {

    ui->actionLogin->setVisible(true);
    ui->actionLogout->setVisible(false);

    m_hiddenTabs.push_back(ui->tab_auth);
    ui->tab_base->insertTab(0, m_hiddenTabs.last(), "Authorization");
    m_hiddenTabs.removeLast();

    m_hiddenTabs.push_back(ui->tab_requests);
    m_hiddenTabs.push_back(ui->tab_balances);

    ui->tab_base->removeTab(ui->tab_base->indexOf(ui->tab_balances));
    ui->tab_base->removeTab(ui->tab_base->indexOf(ui->tab_requests));
}

void MainWindow::updateDaysCount() {

    QDate startDate = ui->calendar_startDate->selectedDate();
    QDate endDate = ui->calendar_endDate->selectedDate();

    m_selectedDaysCount = startDate.daysTo(endDate);
    ui->lbl_daysSelectedCount->setText(QString::number(m_selectedDaysCount));
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

void MainWindow::on_actionLogin_triggered() {

    on_btn_login_clicked();
}

void MainWindow::on_actionLogout_triggered() {

    showLoginScreen();
}

void MainWindow::on_calendar_endDate_selectionChanged() {

    updateDaysCount();
}

void MainWindow::on_calendar_startDate_selectionChanged() {

    updateDaysCount();
}

void MainWindow::on_btn_reqAbsence_clicked() {

    m_dbManager->refreshLeaveCount();
    int daysAvailable = m_dbManager->getCurrentUser()->leavesCount[LeaveType::Vacation];
    if (daysAvailable >= m_selectedDaysCount) {
        m_dbManager->updateLeaveCount(LeaveType::Vacation, daysAvailable - m_selectedDaysCount);
    } else {

    }

    ui->calendar_startDate->setSelectedDate(QDate::currentDate());
    ui->calendar_endDate->setSelectedDate(QDate::currentDate());
}
