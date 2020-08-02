#ifndef NEWS_H
#define NEWS_H

#include <QMainWindow>
//完成对网络数据的请求
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

//JSON数据解析
#include<QJsonArray>  //[]
#include <QJsonDocument> //JSON文档 --- 将服务器数据转换成一个QJsonDocument
#include <QJsonObject> //{}

#include "QtDebug"

#include <QStandardItem>
#include <QStringListModel>
namespace Ui {
class news;
}

class news : public QMainWindow
{
    Q_OBJECT

public:
    explicit news(QWidget *parent = nullptr);
    ~news();

    void read_news(QNetworkReply* reply);
signals:
    void sendname(QString &name);
public slots:
    void getname(QString &name);

private slots:
    void on_back_Btn_clicked();

    void http_news();

private:
    Ui::news *ui;
    QNetworkAccessManager *manager;
    QStringListModel *Model;
    QStandardItemModel *ItemModel;

    QString mmmname;
};

#endif // NEWS_H
