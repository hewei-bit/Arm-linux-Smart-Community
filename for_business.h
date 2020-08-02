#ifndef FOR_BUSINESS_H
#define FOR_BUSINESS_H

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
class for_business;
}

class for_business : public QMainWindow
{
    Q_OBJECT

public:
    explicit for_business(QWidget *parent = nullptr);
    ~for_business();
signals:
    void sendname(QString &name);
public slots:
    void getname(QString &name);
private slots:
    void on_beg_Btn_clicked();

    void on_back_Btn_clicked();

    void on_name_lineEdit_selectionChanged();

    void on_name_lineEdit_editingFinished();

    void on_tele_lineEdit_selectionChanged();

    void on_tele_lineEdit_editingFinished();

    void on_addrr_lineEdit_selectionChanged();

    void on_addrr_lineEdit_editingFinished();

    void on_thing_lineEdit_editingFinished();

    void on_thing_lineEdit_selectionChanged();

private:
    Ui::for_business *ui;

    QString dbname = "../intelligent_community/intell_com.db";
    QSqlDatabase database;
    QSqlQuery sqlQuery;
    QString sqlSelect;
    QString sqlInsert;
    QString sqlupdate;
    QString sqldelete;

    QString mmmname;
};

#endif // FOR_BUSINESS_H
