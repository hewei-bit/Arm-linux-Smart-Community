#include "LED.h"
#include "ui_LED.h"

#include "intelligent_community.h"


static bool flag_7 = true;
static bool flag_8 = true;
static bool flag_9 = true;
static bool flag_10 = true;





void LED::D7_open()
{
    char databuf[2]; //根据驱动来定义数据格式
    //databuf[0] --- 代表灯的状态：0 --- 关灯，1 ---开灯
    //databuf[1] ---- 代表灯的编号 ：7 8 9 10
    databuf[0] = 1; //开灯
    databuf[1] = 7;
    write(fd,databuf,sizeof(databuf));
    ui->d7Label_2->setStyleSheet("background-color: rgb(0, 255, 0)");
}

void LED::D7_close()
{
    char databuf[2]; //根据驱动来定义数据格式
    //databuf[0] --- 代表灯的状态：0 --- 关灯，1 ---开灯
    //databuf[1] ---- 代表灯的编号 ：7 8 9 10
    databuf[0] = 0; //关灯
    databuf[1] = 7;
    write(fd,databuf,sizeof(databuf));
    ui->d7Label_2->setStyleSheet("background-color: rgb(0, 0, 0)");
}

void LED::D8_open()
{
    char databuf[2]; //根据驱动来定义数据格式
    //databuf[0] --- 代表灯的状态：0 --- 关灯，1 ---开灯
    //databuf[1] ---- 代表灯的编号 ：7 8 9 10
    databuf[0] = 1; //开灯
    databuf[1] = 8;
    write(fd,databuf,sizeof(databuf));
    ui->D8Label_2->setStyleSheet("background-color: rgb(0, 255, 0)");
}

void LED::D8_close()
{
    char databuf[2]; //根据驱动来定义数据格式
    //databuf[0] --- 代表灯的状态：0 --- 关灯，1 ---开灯
    //databuf[1] ---- 代表灯的编号 ：7 8 9 10
    databuf[0] = 0; //关灯
    databuf[1] = 8;
    write(fd,databuf,sizeof(databuf));
    ui->D8Label_2->setStyleSheet("background-color: rgb(0, 0, 0)");
}

void LED::getname(QString &name)
{
    mmmname = name;
}


void LED::D9_close()
{
    char databuf[2]; //根据驱动来定义数据格式
    //databuf[0] --- 代表灯的状态：0 --- 关灯，1 ---开灯
    //databuf[1] ---- 代表灯的编号 ：7 8 9 10
    databuf[0] = 0; //关灯
    databuf[1] = 9;
    write(fd,databuf,sizeof(databuf));
    ui->D9Label_2->setStyleSheet("background-color: rgb(0, 0, 0)");
}

void LED::D9_open()
{
    char databuf[2]; //根据驱动来定义数据格式
    //databuf[0] --- 代表灯的状态：0 --- 关灯，1 ---开灯
    //databuf[1] ---- 代表灯的编号 ：7 8 9 10
    databuf[0] = 1; //开灯
    databuf[1] = 9;
    write(fd,databuf,sizeof(databuf));
    ui->D9Label_2->setStyleSheet("background-color: rgb(0, 255, 0)");
}

void LED::D10_close()
{
    char databuf[2]; //根据驱动来定义数据格式
    //databuf[0] --- 代表灯的状态：0 --- 关灯，1 ---开灯
    //databuf[1] ---- 代表灯的编号 ：7 8 9 10
    databuf[0] = 0; //关灯
    databuf[1] = 10;
    write(fd,databuf,sizeof(databuf));
    ui->D10Label_2->setStyleSheet("background-color: rgb(0, 0, 0)");
}
void LED::D10_open()
{
    char databuf[2]; //根据驱动来定义数据格式
    //databuf[0] --- 代表灯的状态：0 --- 关灯，1 ---开灯
    //databuf[1] ---- 代表灯的编号 ：7 8 9 10
    databuf[0] = 1; //开灯
    databuf[1] = 10;
    write(fd,databuf,sizeof(databuf));
    ui->D10Label_2->setStyleSheet("background-color: rgb(0, 255, 0)");
}

void LED::led_running()
{
    qDebug() << "ledd_run";

     if(isRunning == 0)
     {
         //D7
        D10_close();
        D7_open();
     }
     else if (isRunning == 1)
     {
         //D8
        D7_close();
        D8_open();
     }
     else if (isRunning == 2)
     {
         //D9
         D8_close();
         D9_open();
     }
     else if (isRunning == 3)
     {
         //D10
         D9_close();
         D10_open();
     }

     isRunning++;
     if(isRunning == 4)
     {
         isRunning = 0;
     }
}

LED::LED(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    isRunning = 0;
    //打开 灯的设备文件
    fd = open("/dev/gz13_led_drv",O_WRONLY); //底层硬件所对应的设备文件，由驱动程序来设置
    if(fd < 0)
    {
        perror("open");
        return;
    }
    qDebug() << "open";

    D7_close();
    D8_close();
    D9_close();
    D10_close();

}

LED::~LED()
{
    delete ui;
    ::close(fd);
    qDebug() <<"close";
}

void LED::on_d7Btn_clicked()
{
    disconnect(mtimer,&QTimer::timeout,this,&LED::led_running);
    mtimer->stop();

    char D7databuf[2];

    qDebug() << flag_7;
    if(flag_7)
    {
        D7_open();
    }
    else
    {
        D7_close();
    }
    flag_7 = flag_7^1;
    qDebug() << flag_7;
}

void LED::on_D8Btn_clicked()
{
    disconnect(mtimer,&QTimer::timeout,this,&LED::led_running);
    mtimer->stop();

    char D8databuf[2];

    qDebug() << flag_8;
    if(flag_8)
    {
        D8_open();
    }
    else
    {
        D8_close();
    }
    flag_8 = flag_8^1;
    qDebug() << flag_8;
}

void LED::on_D9Btn_clicked()
{
    disconnect(mtimer,&QTimer::timeout,this,&LED::led_running);
    mtimer->stop();

    char D9databuf[2];

    qDebug() << flag_9;
    if(flag_9)
    {
        D9_open();
    }
    else
    {
        D9_close();
    }
    flag_9 = flag_9^1;
    qDebug() << flag_9;
}

void LED::on_D10Btn_clicked()
{

    disconnect(mtimer,&QTimer::timeout,this,&LED::led_running);
    mtimer->stop();

    char D10databuf[2];

    qDebug() << flag_10;
    if(flag_10)
    {
        D10_open();
    }
    else
    {
        D10_close();
    }
    flag_10 = flag_10^1;
    qDebug() << flag_10;
}

void LED::on_all_close_clicked()
{

    disconnect(mtimer,&QTimer::timeout,this,&LED::led_running);
    mtimer->stop();


    D7_close();
    D8_close();
    D9_close();
    D10_close();

}



void LED::on_all_open_clicked()
{

    disconnect(mtimer,&QTimer::timeout,this,&LED::led_running);
    mtimer->stop();
    D7_open();
    D8_open();
    D9_open();
    D10_open();



}


void LED::on_loop_Btn_clicked()
{
//    lr->setObjectName("lr");
//    connect(lr,&led_run::send,this,&LED::led_running);
//    lr->start();

    connect(mtimer,&QTimer::timeout,this,&LED::led_running);
    mtimer->setInterval(1000);
    mtimer->start(1000);

}


void LED::on_back_clicked()
{
    mtimer->stop();
    delete mtimer;
    disconnect(mtimer,&QTimer::timeout,this,&LED::led_running);

    intelligent_community * ic = new intelligent_community();

    connect(this,&LED::sendname,ic,&intelligent_community::setusername);
    emit sendname(mmmname);
    disconnect(this,&LED::sendname,ic,&intelligent_community::setusername);

    ic->show();

    this->close();


}
