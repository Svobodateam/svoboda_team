#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_dbManager(new DBManager()),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
    setupMenuBar();
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

