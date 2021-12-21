#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
      
    setupMenuBar();
}

void MainWindow::setupMenuBar()
{
    actionGroup = new QActionGroup(this);

    actionGroup->setExclusive(true);
    ui->menuTheme->actions().first()->setChecked(true);
    for (int i = 0; i < ui->menuTheme->actions().size(); ++i) {
        actionGroup->addAction(ui->menuTheme->actions()[i]);
    }
    on_actionDiffnes_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionDiffnes_triggered()
{
    QFile file("D:/AgileProj/svoboda_team/Svoboda_team/Diffnes.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->widget->setStyleSheet(styleSheet);
}

void MainWindow::on_actionMedize_triggered()
{
    QFile file("D:/AgileProj/svoboda_team/Svoboda_team/Medize.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->widget->setStyleSheet(styleSheet);
}

