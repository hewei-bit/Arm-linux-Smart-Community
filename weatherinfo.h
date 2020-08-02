#ifndef WEATHERINFO_H
#define WEATHERINFO_H

#include <QWidget>

#include <QMainWindow>
#include <QListWidgetItem>
#include <QProcess>
#include <QTime>
#include <QTimer>
#include <QRunnable>
#include <QtDebug>
#include <QThread>
#include <QThreadPool>
#include <QMutex>
#include <QPen>
#include <QPainter>
#include <QPixmap>
#include <QImage>
#include <QMutex>


//完成对网络数据的请求
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

//JSON数据解析
#include<QJsonArray>  //[]
#include <QJsonDocument> //JSON文档 --- 将服务器数据转换成一个QJsonDocument
#include <QJsonObject> //{}




namespace Ui {
class WeatherInfo;
}

class WeatherInfo : public QWidget
{
    Q_OBJECT

public:
    explicit WeatherInfo(QWidget *parent = nullptr);
    ~WeatherInfo();
    void read_data(QNetworkReply* reply);

    void run_time();
private slots:
//    void show_time();

    void http_weather();

private:
    Ui::WeatherInfo *ui;

    QTimer *mtimer;

    QNetworkAccessManager *manager;

};


//static QMutex mutex;
//class Myclock:public QThread
//{
//    Q_OBJECT
//public:
//    explicit Myclock(QWidget *parent = nullptr){}
//    ~Myclock(){}

//    void run() override
//    {
//        while(1)
//        {
//            mutex.lock();
//            QTime mtime = QTime::currentTime();
//            qDebug() << mtime.toString("hh:mm:ss");
//            QThread::sleep(1);
//            emit send();

//            mutex.unlock();
//        }
//    }
//signals:
//    void send();
//};


#endif // WEATHERINFO_H
