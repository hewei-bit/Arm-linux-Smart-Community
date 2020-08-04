#ifndef PHOTOVIEW_H
#define PHOTOVIEW_H

#include <QMainWindow>
#include <QtDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
//#include <QFile>
#include <QMessageBox>
#include <QtDebug>
#include <QList>
#include <QWidgetItem>
#include <QTableWidgetItem>
#include <QListWidgetItem>
#include <QListWidget>

namespace Ui {
class photoview;
}

class photoview : public QMainWindow
{
    Q_OBJECT
signals:
    void sendshowList();
public slots:
    void showListonWidget();
public:

    explicit photoview(QWidget *parent = nullptr);
    ~photoview();
    void writeinPhotopath(QString filename);
private slots:
    void on_pushButton_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_itemClicked(QListWidgetItem *item);

//    void on_listWidget_itemPressed(QListWidgetItem *item);

private:
    Ui::photoview *ui;
    QSqlQuery sqlQuery;

    QSqlDatabase database;
};

#endif // PHOTOVIEW_H


