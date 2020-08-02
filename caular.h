#ifndef CAULAR_H
#define CAULAR_H
#include <string.h>
#include <iostream>
#include <QtDebug>
#include <QMainWindow>
using namespace std;

namespace Ui {
class Caular;
}

class Caular : public QMainWindow
{
    Q_OBJECT

public:
    explicit Caular(QWidget *parent = nullptr);
    ~Caular();
signals:
    void sendname(QString &name);
private:
    Ui::Caular *ui;
public slots:
    void button_0();
    void button_1();
    void button_2();
    void button_3();
    void button_4();
    void button_5();
    void button_6();
    void button_7();
    void button_8();
    void button_9();
    void button_c();
    void button_a();
    void button_b();
    void button_d();
    void button_e();
    void button_point();
    void button_ZF();
    void button_enter();
    void button_pr();

    void getname(QString &name);
private:
    string  data;
    static int num;
    static int flag;
    static int pointflag;
    static int opnum;
    static int pecflag;
    QString mmmname;

public:
    void inputdata(string a)
    {
//        this->data[this->num] = a;
        this->num ++;
        this->data+=a;
         qDebug()<< QString::fromStdString(this->data)<<" num"<<num;
    }
private slots:
    void on_back_clicked();
};





#endif // CAULAR_H
