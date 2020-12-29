#ifndef MAINWINDOW4_H
#define MAINWINDOW4_H

#include "msgq.h"
#include <QMainWindow>


namespace Ui {
class MainWindow4;
}

class MainWindow4 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow4(QWidget *parent = nullptr);
    ~MainWindow4();

private:
    Ui::MainWindow4 *ui;

   // my declaration
private:
    pthread_t pthid1,pthid2;
public:

    friend void * threadfun2(void *);
    void createthreads();
    Ui::MainWindow4 * uihandle()
    {
        return ui;
    }
    void addintable(Servstatpacket  oServstatpacket);

};

#endif // MAINWINDOW4_H
