#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file("D:/AgileProj/svoboda_team/Svoboda_team/aqua.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->widget->setStyleSheet(styleSheet);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAqua_triggered()
{
    QFile file("D:/AgileProj/svoboda_team/Svoboda_team/aqua.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->widget->setStyleSheet(styleSheet);
}

void MainWindow::on_actionBlue_triggered()
{
    QFile file("D:/AgileProj/svoboda_team/Svoboda_team/blue.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->widget->setStyleSheet(styleSheet);
}

void MainWindow::on_actionmacOS_triggered()
{
    QFile file("D:/AgileProj/svoboda_team/Svoboda_team/macOS.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->widget->setStyleSheet(styleSheet);
}
