#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QSqlError>
#include <QtDebug>


namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    void open_database();

signals:
    void send(QString name);

private slots:
    void on_out_btn_clicked();

    void on_owner_Btn_clicked();

    void on_property_Btn_clicked();

    void on_password_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_password_lineEdit_editingFinished();

    void on_account_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_account_lineEdit_editingFinished();

    void on_register_Btn_clicked();

    void on_password_lineEdit_selectionChanged();

    void on_account_lineEdit_selectionChanged();

private:
    Ui::login *ui;

    QString dbname = "./intell_com.db";

//    QString dbname = "../intelligent_community/intell_com.db";

    QSqlDatabase database;
    QSqlQuery sqlQuery;
    QString sqlSelect;
    QString sqlInsert;
    QString sqlupdate;
    QString sqldelete;

};

#endif // LOGIN_H
