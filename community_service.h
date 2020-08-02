#ifndef COMMUNITY_SERVICE_H
#define COMMUNITY_SERVICE_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QtDebug>
#include <QFile>
#include <QSqlQuery>
#include <QApplication>
#include <QTableView>
#include <QSqlQueryModel>

namespace Ui {
class community_service;
}

class community_service : public QMainWindow
{
    Q_OBJECT

public:
    explicit community_service(QWidget *parent = nullptr);
    ~community_service();
public slots:
    void open_table(QString &name);

    void getname(QString &name);
signals:
    void sendname(QString &myname);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_check_Btn_clicked();

private:
    Ui::community_service *ui;

    QString dbname = "../intelligent_community/intell_com.db";
    QSqlDatabase database;
    QSqlQuery sqlQuery;
    QString sqlSelect;
    QString sqlInsert;
    QString sqlupdate;
    QString sqldelete;

    QString mmmname;
};

#endif // COMMUNITY_SERVICE_H
