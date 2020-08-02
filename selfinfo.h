#ifndef SELFINFO_H
#define SELFINFO_H

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
class selfinfo;
}

class selfinfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit selfinfo(QWidget *parent = nullptr);
    ~selfinfo();
    void read_owner_data();

signals:
    void sendname(QString &name);
public slots:
    void getname(QString &name);
private slots:
    void on_back_Btn_clicked();

private:
    Ui::selfinfo *ui;

    QString dbname = "../intelligent_community/intell_com.db";
    QSqlDatabase database;
    QSqlQuery sqlQuery;
    QString sqlSelect;
    QString sqlInsert;
    QString sqlupdate;
    QString sqldelete;

    QString mmmname;
};

#endif // SELFINFO_H
