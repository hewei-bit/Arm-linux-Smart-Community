#include "runningtime.h"
#include "ui_runningtime.h"
#include "leisure.h"
int runningTimer::num = 0;

runningTimer::runningTimer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mTimer = new QTimer(this);
    connect(mTimer,&QTimer::timeout,this,&runningTimer::show_sec);
    mTimer->setInterval(1);

}

runningTimer::~runningTimer()
{
    delete ui;
}

void runningTimer::getname(QString &name)
{
    mmmname = name;
}

void runningTimer::on_start_Btn_clicked()
{
    mTimer->start();

}

void runningTimer::on_reset_Btn_clicked()
{
    mTimer->stop();
    num=0;
    QTime t(0,0,0);
    t = t.addMSecs(num);
    ui->show_label->setText(t.toString("hh:mm:ss:zzz"));

}

void runningTimer::on_count_Btn_clicked()
{
    ui->textBrowser->append(ui->show_label->text());
}

void runningTimer::on_stop_Btn_clicked()
{
    mTimer->stop();
}

void runningTimer::show_sec()
{
    num++;
    QTime t(0,0,0);
    t = t.addMSecs(num);
    ui->show_label->setText(t.toString("hh:mm:ss:zzz"));
}

void runningTimer::on_back_Btn_clicked()
{
    leisure * np = new leisure();

    connect(this,&runningTimer::sendname,np,&leisure::getname);
    emit sendname(mmmname);
    disconnect(this,&runningTimer::sendname,np,&leisure::getname);

    np->show();
    this->close();
}

void runningTimer::on_clear_Btn_clicked()
{
    ui->textBrowser->clear();
}
