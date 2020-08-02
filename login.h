#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QSqlError>
#include <QtDebug>
#include <QTimer>

#include <QProcess>
#include <QtDebug>

#include <QListWidgetItem>
#include <QTime>
#include <QTimer>
#include <QRunnable>
#include <QtDebug>
#include <QThread>
#include <QThreadPool>
#include <QMutex>
#include <QPen>
#include <QPainter>
#include <QPixmap>
#include <QImage>
#include <QMutex>
#include "readrfidid.h"


class RID:public QThread
{
    Q_OBJECT
public:
    explicit RID(QWidget *parent = nullptr){}
    ~RID(){}
    void run() override
    {
        while(1)
        {
            int id;
            id = readCardId();
            qDebug() << "id "<< id;
            QThread::sleep(1);
            if(id != 0)
            {
              emit send();
            }
        }
    }
signals:
    void send();
};



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

    void jump_to_ic();

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
    RID *rid = new RID();
    QSqlDatabase database;
    QSqlQuery sqlQuery;
    QString sqlSelect;
    QString sqlInsert;
    QString sqlupdate;
    QString sqldelete;
};

#endif // LOGIN_H
