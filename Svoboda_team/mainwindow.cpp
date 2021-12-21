#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_dbManager(new DBManager()),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    on_actionAqua_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAqua_triggered()
{
    QFile file(":/aqua.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->widget->setStyleSheet(styleSheet);
}

void MainWindow::on_actionBlue_triggered()
{
    QFile file(":/blue.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->widget->setStyleSheet(styleSheet);
}

void MainWindow::on_actionmacOS_triggered()
{
    QFile file(":/macOS.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->widget->setStyleSheet(styleSheet);
}
