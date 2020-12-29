#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "common.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    MainWindow2 * ui1 = new MainWindow2();

    ui1->show();
    ui->pushButton->setDisabled(true);
}


void MainWindow::on_pushButton_2_clicked()
{
    exit(0);
}
