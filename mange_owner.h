#ifndef MANGE_OWNER_H
#define MANGE_OWNER_H

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
class mange_owner;
}

class mange_owner : public QMainWindow
{
    Q_OBJECT

public:
    explicit mange_owner(QWidget *parent = nullptr);
    ~mange_owner();

    void open_table();
    void open_database();

    void initModel(QSqlQueryModel &model,const QString&sql);

    QTableView* createView(QSqlQueryModel &model,const QString& title = "");

private slots:
    void on_back_clicked();

    void on_add_Btn_clicked();

    void on_delete_Btn_clicked();

    void on_update_Btn_clicked();

    void on_RFID_lineEdit_selectionChanged();

    void on_RFID_lineEdit_editingFinished();

    void on_addr_lineEdit_selectionChanged();

    void on_addr_lineEdit_editingFinished();

    void on_password_lineEdit_editingFinished();

    void on_password_lineEdit_selectionChanged();

    void on_account_lineEdit_editingFinished();

    void on_account_lineEdit_selectionChanged();

    void on_tele_lineEdit_editingFinished();

    void on_tele_lineEdit_selectionChanged();

    void on_name_lineEdit_selectionChanged();

    void on_name_lineEdit_editingFinished();

private:
    Ui::mange_owner *ui;

    QString dbname = "./intell_com.db";
    QSqlDatabase database;
    QSqlQuery sqlQuery;
    QString sqlSelect;
    QString sqlInsert;
    QString sqlupdate;
    QString sqldelete;


};

#endif // MANGE_OWNER_H
