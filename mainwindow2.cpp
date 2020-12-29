#include "mainwindow2.h"
#include "ui_mainwindow2.h"
#include "common.h"

MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow2)
{
    ui->setupUi(this);
}

MainWindow2::~MainWindow2()
{
    delete ui;
}

void MainWindow2::on_pushButton_clicked()
{



    myseminit(ui->comboBox_2->currentText().toInt());

    MainWindow3 * ui3 = new MainWindow3();
    //vecptrui2.push_back(ui2);
    ui3->createthreads();
    ui3->show();

    int intSerPer = ui->comboBox->currentText().toInt();

    for(int i=0;i<intSerPer;i++){
        MainWindow4 * ui4 = new MainWindow4();
        //vecptrui2.push_back(ui2);
        ui4->createthreads();
        ui4->show();

    }


    ui->label_6->setText(ui->comboBox->currentText());
    ui->label_7->setText(ui->comboBox_2->currentText());

}

void MainWindow2::on_pushButton_2_clicked()
{
    exit(0);
}
