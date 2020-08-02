#include "caular.h"
#include "ui_caular.h"
#include <QtDebug>
#include "countdata.h"
#include "caular.h"
#include "leisure.h"

Caular::Caular(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Caular)
{
    ui->setupUi(this);
//    ui->label_scr->setText("Welcome!");
    this->setFixedSize(this->width(),this->height());
    this->setWindowTitle("MyCalculator");
//    connect(ui->pushButton_0,&QPushButton::clicked,this,&Caular::ui->label_scr->setText("as"));

    connect(ui->pushButton_1,&QPushButton::clicked,this,&Caular::button_1);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&Caular::button_2);
    connect(ui->pushButton_3,&QPushButton::clicked,this,&Caular::button_3);
    connect(ui->pushButton_4,&QPushButton::clicked,this,&Caular::button_4);
    connect(ui->pushButton_5,&QPushButton::clicked,this,&Caular::button_5);
    connect(ui->pushButton_6,&QPushButton::clicked,this,&Caular::button_6);
    connect(ui->pushButton_7,&QPushButton::clicked,this,&Caular::button_7);
    connect(ui->pushButton_8,&QPushButton::clicked,this,&Caular::button_8);
    connect(ui->pushButton_9,&QPushButton::clicked,this,&Caular::button_9);
    connect(ui->pushButton_0,&QPushButton::clicked,this,&Caular::button_0);
    connect(ui->pushButton_c,&QPushButton::clicked,this,&Caular::button_c);
    connect(ui->pushButton_a,&QPushButton::clicked,this,&Caular::button_a);
    connect(ui->pushButton_b,&QPushButton::clicked,this,&Caular::button_b);
    connect(ui->pushButton_d,&QPushButton::clicked,this,&Caular::button_d);
    connect(ui->pushButton_e,&QPushButton::clicked,this,&Caular::button_e);
    connect(ui->pushButton_point,&QPushButton::clicked,this,&Caular::button_point);
    connect(ui->pushButton_ZF,&QPushButton::clicked,this,&Caular::button_ZF);
    connect(ui->pushButton_enter,&QPushButton::clicked,this,&Caular::button_enter);
    connect(ui->pushButton_pre,&QPushButton::clicked,this,&Caular::button_pr);




}
int Caular::num = 0;
int Caular::flag = 0;
int Caular::pointflag = 0;
int Caular::opnum = 0;
int Caular::pecflag = 0;
Caular::~Caular()
{
    delete ui;
}

void Caular::button_1()
{
    this->inputdata("1");
//    qDebug()<< QString::fromStdString(this->data)<<num;
    ui->label->setText(QString::fromStdString(this->data));
}
void Caular::button_0()
{
    this->inputdata("0");
//    qDebug()<< QString::fromStdString(this->data)<<num;
    ui->label->setText(QString::fromStdString(this->data));
}
void Caular::button_2()
{
    this->inputdata("2");
//    qDebug()<< QString::fromStdString(this->data)<<num;
    ui->label->setText(QString::fromStdString(this->data));
}
void Caular::button_3()
{
    this->inputdata("3");
//    qDebug()<< QString::fromStdString(this->data)<<num;
    ui->label->setText(QString::fromStdString(this->data));
}
void Caular::button_4()
{
    this->inputdata("4");
//    qDebug()<< QString::fromStdString(this->data)<<num;
    ui->label->setText(QString::fromStdString(this->data));
}
void Caular::button_5()
{
    this->inputdata("5");
//    qDebug()<< QString::fromStdString(this->data)<<num;
    ui->label->setText(QString::fromStdString(this->data));
}
void Caular::button_6()
{
    this->inputdata("6");
//    qDebug()<< QString::fromStdString(this->data)<<num;
    ui->label->setText(QString::fromStdString(this->data));
}
void Caular::button_7()
{
    this->inputdata("7");
//    qDebug()<< QString::fromStdString(this->data)<<num;
    ui->label->setText(QString::fromStdString(this->data));
}
void Caular::button_8()
{
    this->inputdata("8");
//    qDebug()<< QString::fromStdString(this->data)<<num;
    ui->label->setText(QString::fromStdString(this->data));
}
void Caular::button_9()
{
    this->inputdata("9");
//    qDebug()<< QString::fromStdString(this->data)<<num;
    ui->label->setText(QString::fromStdString(this->data));
}

void Caular::button_c()
{
    this->data = "";
    this->num = 0;
    this->pointflag = 0;
    this->opnum = 0;
     qDebug()<< QString::fromStdString(this->data)<<" num"<<num;
     ui->label->setText(QString::fromStdString(this->data));
}

void Caular::button_a()
{
    if(this->data[this->num - 1] == '+')
        return;
    if(this->data[this->num - 1] == '.')
        return;
    if(this->num == 0)
        return;

    this->inputdata("+");
    this->pointflag =0;
    this->opnum++;
//    qDebug()<< QString::fromStdString(this->data)<<num;
    ui->label->setText(QString::fromStdString(this->data));
}
void Caular::button_b()
{
    if(this->data[this->num - 1] == '-')
        return;
    if(this->data[this->num - 1] == '.')
        return;
    if(this->num == 0)
        return;


    this->inputdata("-");
    this->pointflag =0;
//    qDebug()<< QString::fromStdString(this->data)<<num;
    this->opnum++;
    ui->label->setText(QString::fromStdString(this->data));
}
void Caular::button_d()
{
    if(this->data[this->num - 1] == '*')
        return;
    if(this->data[this->num - 1] == '.')
        return;
    if(this->num == 0)
        return;

    this->inputdata("*");
    this->pointflag =0;
//    qDebug()<< QString::fromStdString(this->data)<<num;
    this->opnum++;
    ui->label->setText(QString::fromStdString(this->data));
}
void Caular::button_e()
{
    if(this->data[this->num - 1] == '/')
        return;
    if(this->data[this->num - 1] == '.')
        return;
    if(this->num == 0)
        return;


    this->inputdata("/");
    this->pointflag =0;
//    qDebug()<< QString::fromStdString(this->data)<<num;
    this->opnum++;
    ui->label->setText(QString::fromStdString(this->data));
}

void Caular::button_point()
{
    if(this->data[this->num - 1] == '.')
        return;

    if(this->data[this->num - 1] < 48)
        return;

    if(this->num == 0)
        return;
    if(this->pointflag == 1)
        return;

    this->inputdata(".");
    this->pointflag = 1;
//    qDebug()<< QString::fromStdString(this->data)<<num;
    ui->label->setText(QString::fromStdString(this->data));
}

void Caular::button_ZF()
{
    int b = this->num;
    while(1){
        if(this->data[b-1] > 48)
        {
            b--;
        }
        else if(this->data[b-1] == '.')
        {
            b--;
        }
        else {

//            qDebug()<< "b"<<b<<"num"<<num;
            break;
        }
    }


    if(b == 1)
    {
        this->data.erase(b-1,1);

         this->num--;
         this->flag--;
        qDebug()<< "delete-";
        qDebug()<< QString::fromStdString(this->data)<<"num"<<num<<"flag"<<this->flag;
        ui->label->setText(QString::fromStdString(this->data));
        return;
    }

    if(b!=0)
    {
        if(this->data[b-1] < 48 && this->data[b-2] < 48)
        {

            this->data.erase(b-1,1);
            ui->label->setText(QString::fromStdString(this->data));
            this->num--;
            this->flag--;
            qDebug()<< "delete-";
            qDebug()<< QString::fromStdString(this->data)<<"num"<<num<<"flag"<<this->flag;

            return;
        }

    }




    this->data.insert(b,"-");
    this->num++;
    this->flag++;
    qDebug()<< "add-";
    qDebug()<< QString::fromStdString(this->data)<<"num"<<num<<"flag"<<this->flag;
    ui->label->setText(QString::fromStdString(this->data));

}

void Caular::button_enter()//计算结果
{
//     int i = getStringtarget(this->data);
//     qDebug()<<"i :"<<i;
//    string data;
//    cutData(this->data,i,data);


//    qDebug()<<"cutafter :"<<QString::fromStdString(data)<<"data cut:"
//           <<QString::fromStdString(this->data);

//    string op;
//    cutOpera(this->data,op);
//    qDebug()<<"cutop :"<<QString::fromStdString(op)<<"data cut:"
//           <<QString::fromStdString(this->data);
    if(this->data == "")
    {
        ui->label_2->setText("0");
        ui->label->setText("没有输入");
        return;
    }

    qDebug()<<"opnum:"<<this->opnum;
    double ret = 0;
    string tem = this->data;
    CountMain(tem,ret,opnum);

    ui->label_2->setText(QString::number(ret,100,2));

}

void Caular::button_pr()
{
    qDebug()<<"opnum:"<<this->opnum;
    if(this->data == "")
    {
        ui->label_2->setText("0");
        ui->label->setText("没有输入");
        return;
    }
    double ret = 0;
    string tem = this->data;
    CountMain(tem,ret,opnum);
    ret = ret/100;
    ui->label_2->setText(QString::number(ret,100,2));
}

void Caular::getname(QString &name)
{
    mmmname = name;
}






void Caular::on_back_clicked()
{
    leisure * np = new leisure();

    connect(this,&Caular::sendname,np,&leisure::getname);
    emit sendname(mmmname);
    disconnect(this,&Caular::sendname,np,&leisure::getname);

    np->show();
    this->close();
}
