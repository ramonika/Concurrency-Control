#include "mainwindow3.h"
#include "ui_mainwindow3.h"
#include "common.h"

MainWindow3::MainWindow3(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow3)
{
    ui->setupUi(this);
}

MainWindow3::~MainWindow3()
{
    delete ui;
}

void *threadfunAddReq1(void * i)
{

    ((Ui::MainWindow3 *)i)->label_2->setText("AddReq::Thread start");
    //sleep(5);
    while(1){


        struct timespec ts;
        ts.tv_sec=1;
        nanosleep(&ts,NULL);
       // if(MAXSEM1 >= mysemval(0)){
        // Sem1 Wait


        mysemp(0);
        QString qstr = "AddReq:: Semaphore acquired(decrement 1) : " +QString::number(mysemval(0));
        ((Ui::MainWindow3 *)i)->label_2->setText(qstr);


        // Add request in msg queue
        static int cntr=1;
        char str[100];
        memset(str,0,100);
        sprintf(str,"Customer%d",cntr++);
        msgsend(str);
        const int currentRow = ((Ui::MainWindow3 *)i)->tableWidget->rowCount();
        ((Ui::MainWindow3 *)i)->tableWidget->setRowCount(currentRow + 1);
        ((Ui::MainWindow3 *)i)->tableWidget->setItem(currentRow, 1, new QTableWidgetItem(QString::fromUtf8("Yes")));
        ((Ui::MainWindow3 *)i)->tableWidget->setItem(currentRow, 0, new QTableWidgetItem(QString::fromUtf8(str)));
        char tstr[100];
        ((Ui::MainWindow3 *)i)->tableWidget->setItem(currentRow, 2, new QTableWidgetItem(getLocalTime(tstr)));

        if(0 == mysemval(0)){
            ((Ui::MainWindow3 *)i)->label_3->setText("Queue Full, Customer Leave");
        } else {
            ((Ui::MainWindow3 *)i)->label_3->setText("Open, Customer Request Allowed");
        }
        // sem1 release
        //mysemv(0);

        //((Ui::MainWindow3 *)i)->label_2->setText("AddReq::Thread End");
        //sleep(2);
       // }
    }
    return NULL;
}
void *threadfunRecReq1(void * i)
{
    while(1){
        //printf("Inside Thread Service Provider Personnel\n");
       // ((Ui::MainWindow3 *)i)->label_3->setText("RecReq::Thread start");
        //sleep(2);

        // Sem2 Wait

        // Add request in msg queue

        // sem2 release

        //((Ui::MainWindow3 *)i)->label_3->setText("RecReq::Thread End");
        //sleep(2);
    }
    return NULL;
}
void MainWindow3::createthreads(){
    pthid1=0;
    if(0!=pthread_create(&pthid1,NULL,threadfunAddReq1,(void *)uihandle())){
        // error msg;
        return;
    }
    /*
    pthid2=0;
    if(0!=pthread_create(&pthid2,NULL,threadfunRecReq1,(void *)uihandle())){
        // error msg;
        return;
    }
    */

}
