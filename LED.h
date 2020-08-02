#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QRunnable>
#include <QtDebug>
#include <QThread>
#include <QThreadPool>
#include <QMutex>


#ifndef __cplusplus
extern "C"{
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#ifndef __cplusplus
}
#endif


//static QMutex mutex;

//class led_run:public QThread
//{
//    Q_OBJECT
//public:
//    explicit led_run(QWidget *parent = nullptr){}
//    ~led_run(){}

//    void run() override
//    {
//        mutex.lock();
//        while(1)
//        {
//        QThread::sleep(1);
//        qDebug() << "led_run";
//        emit send();
//        mutex.unlock();
//    }}

//signals:
//    void send();
//};


namespace Ui {
class MainWindow;
}

class LED : public QMainWindow
{
    Q_OBJECT

public:
    explicit LED(QWidget *parent = nullptr);
    ~LED();

    void led_running();
    void D10_close();

    void D7_open();

    void D7_close();

    void D8_open();

    void D10_open();

    void D9_close();

    void D9_open();

    void D8_close();


signals:
    void sendname(QString &name);
public slots:
    void getname(QString &name);

private slots:
    void on_d7Btn_clicked();

    void on_D8Btn_clicked();

    void on_D9Btn_clicked();

    void on_D10Btn_clicked();

    void on_all_close_clicked();

    void on_back_clicked();

    void on_all_open_clicked();

    void on_loop_Btn_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *mtimer = new QTimer(this);
    int fd ;
    int isRunning;
//    led_run *lr = new led_run();

    QString mmmname;


};

#endif // MAINWINDOW_H
