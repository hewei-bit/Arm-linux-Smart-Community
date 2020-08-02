#include "intelligent_community.h"
#include "ui_intelligent_community.h"

#include "weatherinfo.h"

#include "selfinfo.h"
#include "community_service.h"
#include "news.h"
#include "leisure.h"
#include "LED.h"
#include "videodisplay.h"


#include "login.h"




static QString myname="";

intelligent_community::intelligent_community(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::intelligent_community)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/pic/school.png"));
    QImage img;
    img.load(":/pic/school.png");
    QPixmap originalPixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(originalPixmap.scaled(ui->label->size(),
                         Qt::IgnoreAspectRatio,
                         Qt::SmoothTransformation));
    this->setObjectName("mainWindow");
    this->setStyleSheet("#mainWindow{border-image:url(:/pic/manchester.jpg);}");
    //天气信息
//    ui->widget_2->show();

    ui->widget->setStyleSheet("background-color: rgba(250, 250, 250,0)");

    //显示时间
//    Myclock *mc= new Myclock();

    connect(mtimer,&QTimer::timeout,this,&intelligent_community::show_time);
    mtimer->setInterval(1000);
    mtimer->start(1000);

//    mc->setObjectName("mc");
//    connect(mc,&Myclock::send,this,&intelligent_community::show_time);
//    mc->start();

    // 天气API已连接成功
    http_weather();

    //播广告
    ad_video();

}

intelligent_community::~intelligent_community()
{
    delete ui;
    qDebug() << "intelligent_community::~intelligent_community()";
}

void intelligent_community::exit_video()
{
    if(in_video_Process.state() == QProcess::Running)
    {
        in_video_Process.kill();
        in_video_Process.waitForFinished();
    }
}

void intelligent_community::ad_video()
{
    exit_video();
    QString cmd = QString("mplayer -slave -quiet "
                          " -geometry 40:120 -zoom -x %1 -y %2 "
                          " -wid %3 "
                          " ./Manchester.mp4")
            .arg(ui->label_17->width())
            .arg(ui->label_17->height())
            .arg(QString::number(ui->label_17->winId()));
    qDebug() << "cmd = " << cmd;

    in_video_Process.start(cmd);
}

void intelligent_community::run_time()
{

}

void intelligent_community::read_data(QNetworkReply *reply)
{
    QByteArray array = reply->readAll();

    QJsonDocument doc = QJsonDocument::fromJson(array);

    /*
    {
    "reason":"查询成功!",
    "result":{
        "city":"广州",
        "realtime":{
            "temperature":"29",
            "humidity":"75",
            "info":"多云",
            "wid":"01",
            "direct":"东南风",
            "power":"2级",
            "aqi":"15"
        }}
    */

    //获取整个文本
    QJsonObject object =  doc.object();
    //是否成功
    QString reason = object.value("reason").toString();
    qDebug() << reason;
    QJsonObject resultObject = object.value("result").toObject();
    //所在城市
    QString mcity = resultObject.value("city").toString();
    qDebug() << mcity;
    //实时信息
    QJsonObject realtimeObject = resultObject.value("realtime").toObject();

    QString mtemperature = realtimeObject.value("temperature").toString();
    QString minfo = realtimeObject.value("info").toString();
    QString mhumidity = realtimeObject.value("humidity").toString();
    QString winddirect = realtimeObject.value("direct").toString();
    QString windpower = realtimeObject.value("power").toString();

    qDebug() << minfo;
    qDebug() << mtemperature;
    qDebug() << mhumidity;
    qDebug() << winddirect;
    qDebug() << windpower;



    ui->city_label->setText(mcity);
    ui->info_label->setText(minfo);
    ui->temper_label->setText(mtemperature);
//    ui->winddir_label->setText(winddirect);
//    ui->windpow_label->setText(windpower);
    ui->humidity_label->setText(mhumidity);


    //气温预警提示
    if(mtemperature.toInt() >= 37)
    {
        QPalette pe;
        pe.setColor(QPalette::WindowText, Qt::red);
        ui->temper_warning_label->setPalette(pe);
        ui->temper_warning_label->setText("高温预警，记得浇花");
    }
    else if(mtemperature.toInt() >= 30 or mtemperature.toInt() < 37)
    {
        QPalette pe;
        pe.setColor(QPalette::WindowText, Qt::yellow);
        ui->temper_warning_label->setPalette(pe);
        ui->temper_warning_label->setText("高温预警，记得浇花");
    }
    else if(mtemperature.toInt() >= 16 or mtemperature.toInt() < 30)
    {
        QPalette pe;
        pe.setColor(QPalette::WindowText, Qt::green);
        ui->temper_warning_label->setPalette(pe);
        ui->temper_warning_label->setText("气温适宜出行");
    }
    else if(mtemperature.toInt() >= 16 or mtemperature.toInt() < 30)
    {
        QPalette pe;
        pe.setColor(QPalette::WindowText, Qt::green);
        ui->temper_warning_label->setPalette(pe);
        ui->temper_warning_label->setText("天凉了，记得保暖");
    }

    //湿度预警提示
    if(mhumidity.toInt() >= 50)
    {
        QPalette pe;
        pe.setColor(QPalette::WindowText, Qt::green);
        ui->humi_warining_label->setPalette(pe);
        ui->humi_warining_label->setText("湿度适宜");
    }
    else if(mhumidity.toInt() < 50)
    {
        QPalette pe;
        pe.setColor(QPalette::WindowText, Qt::red);
        ui->humi_warining_label->setPalette(pe);
        ui->humi_warining_label->setText("天干物燥，小心火烛");
    }

    //天气图片
    if(minfo.contains("云",Qt::CaseSensitive))
    {
        QImage img ;
        img.load(":/weather/cloudy (2).png");
        QPixmap originmap = QPixmap::fromImage(img);


        ui->info_pic_label->setPixmap(originmap.scaled(ui->info_pic_label->size(),
                                                       Qt::IgnoreAspectRatio,
                                                       Qt::SmoothTransformation));
    }
    if(minfo.contains("雨",Qt::CaseSensitive))
    {
        QImage img ;
        img.load(":/weather/raining.png");
        QPixmap originmap = QPixmap::fromImage(img);


        ui->info_pic_label->setPixmap(originmap.scaled(ui->info_pic_label->size(),
                                                       Qt::IgnoreAspectRatio,
                                                       Qt::SmoothTransformation));
    }
    if(minfo.contains("阴",Qt::CaseSensitive))
    {
        QImage img ;
        img.load(":/weather/cloudy.png");
        QPixmap originmap = QPixmap::fromImage(img);


        ui->info_pic_label->setPixmap(originmap.scaled(ui->info_pic_label->size(),
                                                       Qt::IgnoreAspectRatio,
                                                       Qt::SmoothTransformation));
    }
    if(minfo.contains("晴",Qt::CaseSensitive))
    {
        QImage img ;
        img.load(":/weather/sunny.png");
        QPixmap originmap = QPixmap::fromImage(img);


        ui->info_pic_label->setPixmap(originmap.scaled(ui->info_pic_label->size(),
                                                       Qt::IgnoreAspectRatio,
                                                       Qt::SmoothTransformation));
    }
}

//打开报修服务
void intelligent_community::on_server_Btn_clicked()
{
    community_service *coms = new community_service();

    connect(this,&intelligent_community::sendname,coms,&community_service::getname);
    emit sendname(myname);
    disconnect(this,&intelligent_community::sendname,coms,&community_service::getname);
//    disconnect(mc,&Myclock::send,this,&intelligent_community::show_time);
    mtimer->stop();
    delete mtimer;
    exit_video();

    coms->show();
    this->close();
}

//打开休闲娱乐
void intelligent_community::on_leien_Btn_clicked()
{
    leisure *leien = new leisure();

    connect(this,&intelligent_community::sendname,leien,&leisure::getname);
    emit sendname(myname);
    disconnect(this,&intelligent_community::sendname,leien,&leisure::getname);
//disconnect(mc,&Myclock::send,this,&intelligent_community::show_time);
    mtimer->stop();
    delete mtimer;
    exit_video();
    leien->show();
    this->close();
}

//
void intelligent_community::on_selfinfo_Btn_clicked()
{
    selfinfo *sinfo = new selfinfo();

    connect(this,&intelligent_community::sendname,sinfo,&selfinfo::getname);
    emit sendname(myname);
    disconnect(this,&intelligent_community::sendname,sinfo,&selfinfo::getname);
//disconnect(mc,&Myclock::send,this,&intelligent_community::show_time);
    mtimer->stop();
    delete mtimer;
    exit_video();
    sinfo->show();
    this->close();
}


//打开新闻
void intelligent_community::on_news_Btn_clicked()
{
    news *nn = new news ();

    connect(this,&intelligent_community::sendname,nn,&news::getname);
    emit sendname(myname);
    disconnect(this,&intelligent_community::sendname,nn,&news::getname);
    mtimer->stop();
    delete mtimer;
    exit_video();

    nn->show();
    this->close();
}


//打开监控
void intelligent_community::on_video_Btn_clicked()
{
    VideoDisplay *VD = new VideoDisplay ();

    connect(this,&intelligent_community::sendname,VD,&VideoDisplay::getname);
    emit sendname(myname);
    disconnect(this,&intelligent_community::sendname,VD,&VideoDisplay::getname);
    mtimer->stop();
    delete mtimer;
    exit_video();

    VD->show();
    this->close();
}


//点灯
void intelligent_community::on_light_Btn_clicked()
{
    LED *LL = new LED ();

    connect(this,&intelligent_community::sendname,LL,&LED::getname);
    emit sendname(myname);
    disconnect(this,&intelligent_community::sendname,LL,&LED::getname);
    mtimer->stop();
    delete mtimer;
    exit_video();

    LL->show();
    this->close();
}

void intelligent_community::on_back_Btn_clicked()
{
    login *lg = new login ();
    lg->show();
//    disconnect(mc,&Myclock::send,this,&intelligent_community::show_time);

    mtimer->stop();
    delete mtimer;
    exit_video();
    this->close();
}

void intelligent_community::show_time()
{
    QTime time = QTime::currentTime();
    ui->time_label->setText(time.toString("hh:mm:ss"));
    if(5 <= time.hour() and time.hour() < 11)
    {
        ui->time_greetings_label->setText("早上好");
    }
    else if (11<=time.hour() and time.hour()<14) {
        ui->time_greetings_label->setText("中午好");
    }
    else if (14<=time.hour() and time.hour()<17) {
        ui->time_greetings_label->setText("下午好");
    }
    else if (17<=time.hour() and time.hour()< 24) {
        ui->time_greetings_label->setText("晚上好");
    }
    else if (0<=time.hour() and time.hour()< 5) {
        ui->time_greetings_label->setText("夜深了");
    }

    if((time.minute() == 00 and time.second() == 00)or(time.minute() == 30 and time.second() == 00))
    {
        http_weather();
    }

    QDate date = QDate::currentDate();
    ui->date_label->setText(date.toString("yyyy-MM-dd"));
}

void intelligent_community::http_weather()
{
    manager = new QNetworkAccessManager();

    connect(manager,&QNetworkAccessManager::finished,this,&intelligent_community::read_data);

    QUrl url("http://apis.juhe.cn/simpleWeather/query?"
             "city=%E5%B9%BF%E5%B7%9E"
             "&key=6eaaa433d136ff59653d126c67270943");
    QNetworkRequest request(url);
    manager->get(request);
}

void intelligent_community::setusername(QString name)
{
    myname = name;
    ui->name_label->setText(QString("亲爱的 %1 ").arg(name));
}


