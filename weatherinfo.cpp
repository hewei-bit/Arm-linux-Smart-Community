#include "weatherinfo.h"
#include "ui_weatherinfo.h"

WeatherInfo::WeatherInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeatherInfo)
{
    ui->setupUi(this);

//    Myclock *mc= new Myclock();
//    mc->setObjectName("mc");

//    connect(mc,&Myclock::send,this,&WeatherInfo::show_time);
//    mc->start();


    this->setStyleSheet("background-color: rgba(100, 100, 100, 0);");

    // 天气API已连接成功
    http_weather();
}

WeatherInfo::~WeatherInfo()
{
    delete ui;
}

void WeatherInfo::read_data(QNetworkReply* reply)
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

void WeatherInfo::run_time()
{

}

//void WeatherInfo::show_time()
//{
//    QTime time = QTime::currentTime();
//    ui->time_label->setText(time.toString("hh:mm:ss"));
//    QDate date = QDate::currentDate();
//    ui->date_label->setText(date.toString("yyyy-MM-dd"));
//}

void WeatherInfo::http_weather()
{
    manager = new QNetworkAccessManager();

    connect(manager,&QNetworkAccessManager::finished,this,&WeatherInfo::read_data);

    QUrl url("http://apis.juhe.cn/simpleWeather/query?"
             "city=%E5%B9%BF%E5%B7%9E"
             "&key=6eaaa433d136ff59653d126c67270943");
    QNetworkRequest request(url);
    manager->get(request);
}
