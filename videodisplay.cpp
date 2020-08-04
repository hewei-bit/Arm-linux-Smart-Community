#include "videodisplay.h"
#include "ui_videodisplay.h"
#include <QMessageBox>
#include <QImage>
#include <QPixmap>
//#include <shotshow.h>
#include <QDate>
#include <QFile>
#include <photoview.h>

#include "intelligent_community.h"

videodisplay::videodisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::videodisplay)
  ,bufrgb(nullptr)
{
    ui->setupUi(this);
    pd.dev_name = (char*)"/dev/video7";
    timer = new QTimer;
    connect(timer,&QTimer::timeout,this,&videodisplay::flushButff);
    timer->setInterval(20);
    filelist = new photoview;
//    connect(ui->shotBtn,&QPushButton::clicked,this,&videodisplay::shotscreen);
}

videodisplay::~videodisplay()
{
    delete ui;
}

void videodisplay::getname(QString &name)
{
    mmmname = name;
}

void videodisplay::on_startBtn_clicked()
{
//    printf("%d\n",__LINE__);
    int flag = init_dev(&pd);
     if(flag == -1)
     {
         QMessageBox::information(this,"tip","no device");
         exit(1);
     }else if (flag == -2) {
         QMessageBox::information(this,"tip"," device is worng");
         exit(2);
    } else if (flag == -3) {
         QMessageBox::information(this,"tip"," can not open device");
         exit(3);
    }
     ui->startBtn->setDisabled(1);
     timer->start(); //开启捕获数据
}

void videodisplay::flushButff()
{
//    printf("%d\n",__LINE__);
    read_frame(&pd); //读取数据
//    printf("%d\n",__LINE__);
    if(!bufrgb)
        bufrgb = (unsigned char *)malloc(640*480*3);
    memset(bufrgb,0,640*480*3);
//    printf("%d\n",__LINE__);
    convert_yuv_to_rgb_buffer((unsigned char*)pd.buffers[pd.buf.index].start,
            bufrgb,640,480);
//    printf("%d\n",__LINE__);
    QImage image(bufrgb,640,480,QImage::Format_RGB888);
         ui->displaytLabel->setPixmap(QPixmap::fromImage(image));
//    printf("%d\n",__LINE__);
    return_data(&pd);
}

void videodisplay::on_shotBtn_clicked()
{



        QImage image(bufrgb,640,480,QImage::Format_RGB888);
        QTime data = QTime::currentTime();

        QString filename = QString("%1.jpg").arg(data.toString("hh-mm-ss"));



        image.save(filename);
        printf("jpg got\n");
        filelist->writeinPhotopath(filename);
//        filelist->show();
        QPixmap pixmap = QPixmap::fromImage(image);
        QPixmap firpix = pixmap.scaled(110,90,Qt::KeepAspectRatio, Qt::SmoothTransformation);

        ui->label->setPixmap(firpix);


        //             printf("%d\n",__LINE__);
}



void videodisplay::on_pushButton_clicked()
{
    filelist->show();
    connect(filelist,&photoview::sendshowList,filelist,&photoview::showListonWidget);
    emit filelist->sendshowList();
}

void videodisplay::on_pushButton_2_clicked()
{
    intelligent_community * ic = new intelligent_community();

    connect(this,&videodisplay::sendname,ic,&intelligent_community::setusername);
    emit sendname(mmmname);
    disconnect(this,&videodisplay::sendname,ic,&intelligent_community::setusername);

    ic->show();

    this->close();
}
