#include "mainwindow4.h"
#include "ui_mainwindow4.h"
#include "common.h"

#include <pthread.h>
pthread_mutex_t lock1;

//extern MainWindow w;

MainWindow4::MainWindow4(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow4)
{
    ui->setupUi(this);
}

MainWindow4::~MainWindow4()
{
    delete ui;
}

void MainWindow4::addintable(Servstatpacket  oServstatpacket)
{

      const int currentRow = ui->tableWidget->rowCount();
      ui->tableWidget->setRowCount(currentRow + 1);

      ui->tableWidget->setItem(currentRow, 0, new QTableWidgetItem(QString::number(oServstatpacket.CustReqNo)));
      ui->tableWidget->setItem(currentRow, 1, new QTableWidgetItem(QString::fromUtf8(oServstatpacket.CustReqTime)));
      ui->tableWidget->setItem(currentRow, 2, new QTableWidgetItem(QString::number(oServstatpacket.ServPerAllocated)));
      ui->tableWidget->setItem(currentRow, 3, new QTableWidgetItem(QString::fromUtf8(oServstatpacket.SerStartTime)));
      ui->tableWidget->setItem(currentRow, 4, new QTableWidgetItem(QString::fromUtf8(oServstatpacket.SerEndTime)));

}

void *threadfunRecReq2(void * i)
{
    //printf("Inside Thread Service Provider Personnel\n");
    ((Ui::MainWindow4 *)i)->label_2->setText("RecReq::Thread start");
    //sleep(5);
    while(1){

        if(getMAXSEM1() > mysemval(0)){
            ((Ui::MainWindow4 *)i)->label_3->setText("Open, Service Person Processing Request");
            // Sem1 Wait
            //mysemp(0);

            // Recieve request in msg queue
        	char str[200];
            Servstatpacket oServstatpacket;
            memset(&oServstatpacket,0,sizeof(oServstatpacket));

            pthread_mutex_lock(&lock1);
            msgreceive(oServstatpacket);
            pthread_mutex_unlock(&lock1);
            // sem1 release
            mysemv(0);
            QString qstr = "AddReq:: Semaphore Release (Increment 1) : " +QString::number(mysemval(0));
            ((Ui::MainWindow4 *)i)->label_2->setText(qstr);
            //((Ui::MainWindow4 *)i)->label_2->setText("RecReq::Thread End");

            //Service Process Execution  start
            strcpy(str,oServstatpacket.msgstr);
            strcpy(oServstatpacket.SerStartTime,getLocalTime(oServstatpacket.SerStartTime));
            //sleep(10);
            struct timespec ts;
            ts.tv_sec=5;
            nanosleep(&ts,NULL);
            strcpy(oServstatpacket.SerEndTime,getLocalTime(oServstatpacket.SerEndTime));
            //Service Process Execution  End
            //cleanup execution


            //((Ui::MainWindow4 *)i)->tableWidget;
            const int currentRow = ((Ui::MainWindow4 *)i)->tableWidget->rowCount();
            ((Ui::MainWindow4 *)i)->tableWidget->setRowCount(currentRow + 1);

            ((Ui::MainWindow4 *)i)->tableWidget->setItem(currentRow, 0, new QTableWidgetItem(QString::number(oServstatpacket.CustReqNo)));
            ((Ui::MainWindow4 *)i)->tableWidget->setItem(currentRow, 1, new QTableWidgetItem(QString::fromUtf8(oServstatpacket.msgstr)));
            ((Ui::MainWindow4 *)i)->tableWidget->setItem(currentRow, 2, new QTableWidgetItem(QString::fromUtf8(oServstatpacket.CustReqTime)));
            ((Ui::MainWindow4 *)i)->tableWidget->setItem(currentRow, 3, new QTableWidgetItem(QString::number(oServstatpacket.ServPerAllocated)));
            ((Ui::MainWindow4 *)i)->tableWidget->setItem(currentRow, 4, new QTableWidgetItem(QString::fromUtf8(oServstatpacket.SerStartTime)));
            ((Ui::MainWindow4 *)i)->tableWidget->setItem(currentRow, 5, new QTableWidgetItem(QString::fromUtf8(oServstatpacket.SerEndTime)));


        } else {
            ((Ui::MainWindow4 *)i)->label_3->setText("Queue Empty, Service Person Closed");
            struct timespec ts;
            ts.tv_sec=5;
            nanosleep(&ts,NULL);
        }

    }
    return NULL;
}
void *threadfunAddReq2(void * i)
{
    while(1){
        //printf("Inside Thread Service Provider Personnel\n");
        ((Ui::MainWindow4 *)i)->label_3->setText("AddReq::Thread start");
        //sleep(3);

        // Sem1 Wait

        // Add request in msg queue

        // sem1 release

        ((Ui::MainWindow4 *)i)->label_3->setText("AddReq::Thread End");
        //sleep(2);
    }
    return NULL;
}

void MainWindow4::createthreads(){
    pthid1=0;
    if(0!=pthread_create(&pthid1,NULL,threadfunRecReq2 ,(void *)uihandle())){
        // error msg;
        return;
    }

    /*pthid2=0;
    if(0!=pthread_create(&pthid2,NULL,threadfunAddReq2,(void *)uihandle())){
        // error msg;
        return;
    }
    */

}
