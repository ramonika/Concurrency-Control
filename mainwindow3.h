#ifndef MAINWINDOW3_H
#define MAINWINDOW3_H


#include <QMainWindow>

namespace Ui {
class MainWindow3;
}

class MainWindow3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow3(QWidget *parent = nullptr);
    ~MainWindow3();

private:
    Ui::MainWindow3 *ui;

   // my declaration
private:
    pthread_t pthid1,pthid2;
public:

    friend void * threadfunAddReq1(void *);
    friend void * threadfunRecReq1(void *);
    void createthreads();
    Ui::MainWindow3 * uihandle()
    {
        return ui;
    }
};

#endif // MAINWINDOW3_H
