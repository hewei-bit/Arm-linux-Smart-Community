#include "news.h"
#include "ui_news.h"
#include "intelligent_community.h"



news::news(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::news)
{
    ui->setupUi(this);


    http_news();
}

news::~news()
{
    delete ui;
}

void news::read_news(QNetworkReply *reply)
{
    QByteArray array = reply->readAll();

    QJsonDocument doc = QJsonDocument::fromJson(array);

    /*
   {"reason":"成功的返回",
    "result":{
        "stat":"1",
        "data":[
            {
                "uniquekey":"7f5911d3428f24591949981af32d056b",
                "title":"阿根廷三省准备在8月份复学 较此前计划有所减少",
                "date":"2020-07-30 22:07",
                "category":"头条",
                "author_name":"阿根廷中文播报",
                "url":"https:\/\/mini.eastday.com\/mobile\/200730220706781.html",
                "thumbnail_pic_s":"https:\/\/09imgmini.eastday.com\/mobile\/20200730\/20200730220706_7455bdb26fccf0b691edc51a4dc24c0d_1_mwpm_03200403.jpg"
            }
    */

    //获取整个文本
    QJsonObject object =  doc.object();
    //是否成功
    QString reason = object.value("reason").toString();
    qDebug() << reason;

    QJsonObject resultObject = object.value("result").toObject();
    //所在城市
    QString stat = resultObject.value("stat").toString();
    qDebug() << stat;
    //实时信息
    QJsonArray dataArray = resultObject.value("data").toArray();

    ItemModel = new QStandardItemModel(this);

    for (int i = 0; i < dataArray.size(); ++i) {
        QJsonObject dataObject = dataArray.at(i).toObject();
        QString mtitle = dataObject.value("title").toString();
        QString mdate = dataObject.value("date").toString();
        //        QString minfo = realtimeObject.value("info").toString();
//        QString mhumidity = realtimeObject.value("humidity").toString();
//        QString winddirect = realtimeObject.value("direct").toString();
//        QString windpower = realtimeObject.value("power").toString();

        QString string = mdate + "      " + mtitle;
        QStandardItem *item = new QStandardItem(string);
        ItemModel->appendRow(item);



    }
    ui->listView->setModel(ItemModel);


}

void news::getname(QString &name)
{
    mmmname = name;
}

void news::on_back_Btn_clicked()
{
    intelligent_community * ic = new intelligent_community();

    connect(this,&news::sendname,ic,&intelligent_community::setusername);
    emit sendname(mmmname);
    disconnect(this,&news::sendname,ic,&intelligent_community::setusername);

    ic->show();

    this->close();
}

void news::http_news()
{
    manager = new QNetworkAccessManager();

    connect(manager,&QNetworkAccessManager::finished,this,&news::read_news);

    QUrl url("http://v.juhe.cn/toutiao/index?"
             "type=&key=92e80f5c0e7b17650a3916961ccff818");
    QNetworkRequest request(url);
    manager->get(request);
}
