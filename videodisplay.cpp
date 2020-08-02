#include "videodisplay.h"
#include "ui_videodisplay.h"
#include <string.h>
#include <QMessageBox>

#include "intelligent_community.h"

VideoDisplay::VideoDisplay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VideoDisplay), bufrgb(NULL)
{
    ui->setupUi(this);
    connect(ui->beginButton, SIGNAL(clicked()), this, SLOT(beginCapture()));
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(savebmpData()));
    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(reject()));
    start_tcp=0;

    timer = new QTimer(this);
    timer->setInterval(30);
    socket=new QTcpSocket();
    tcp_server=new QTcpServer();
    tcp_server->listen(QHostAddress::Any,8888);
    connect(timer, SIGNAL(timeout()), this, SLOT(flushBuff()));
    connect(tcp_server,SIGNAL(newConnection()),this,SLOT(tcp_receive()));
    pd.dev_name = (char*)"/dev/video7";
}

VideoDisplay::~VideoDisplay()
{

    if (timer->isActive()) {
        timer->stop();
    }
    delete ui;

}

void VideoDisplay::getname(QString &name)
{
    mmmname = name;
}
void VideoDisplay::tcp_receive()
{
    socket=tcp_server->nextPendingConnection();
    start_tcp=1;
}

void VideoDisplay::beginCapture()
{
    int flag = init_dev(&pd);
    if (flag == -1) {
        QMessageBox::information(this,tr("Tip"),tr("no device"));
        exit(1);
    }
    else if (flag == -2) {
        QMessageBox::information(this,tr("Tip"),tr("device is wrong"));
        exit(2);
    }
    else if (flag == -3) {
        QMessageBox::information(this,tr("Tip"),tr("can not open device"));
        exit(3);
    }
    timer->start();
    ui->beginButton->setDisabled(1);
}


void VideoDisplay::flushBuff()
{
    read_frame (&pd);
    if (!bufrgb) {
        bufrgb = (unsigned char *)malloc(640 * 480* 3);
    }
    memset(bufrgb, 0, 640 * 480* 3);

    convert_yuv_to_rgb_buffer((unsigned char *)pd.buffers[pd.buf.index].start,bufrgb,640,480);
    QImage image(bufrgb,640,480,QImage::Format_RGB888);
    ui->displayLabel->setPixmap(QPixmap::fromImage(image));
    return_data(&pd);
    if(start_tcp==1)
    {
        QByteArray byte;
        QBuffer buf(&byte);
        image.save(&buf,"JPEG");
        QByteArray ss=qCompress(byte,1);
        QByteArray vv=ss.toBase64();

        QByteArray ba;
        QDataStream out(&ba,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_6);
        out<<(quint64)0;
        out<<vv;
        out.device()->seek(0);
        out<<(quint64)(ba.size()-sizeof(quint64));
        socket->write(ba);
    }
}

void VideoDisplay::savebmpData()
{
    time_t now;
    struct tm *tm_time;
    time(&now);

    if (bufrgb > 0 && strlen((char *)bufrgb) > 0) {
        tm_time = localtime(&now);
        char filename[30] = {0};
        sprintf(filename,"%4d-%02d-%02d_%02d.%02d.%02d.jpg",1900+tm_time->tm_year,1+tm_time->tm_mon,tm_time->tm_mday,
                tm_time->tm_hour,tm_time->tm_min,tm_time->tm_sec);
       QImage image(bufrgb,640,480,QImage::Format_RGB888);
       image.save(filename);
    }
}


void VideoDisplay::on_exitButton_clicked()
{
    intelligent_community * ic = new intelligent_community();

    connect(this,&VideoDisplay::sendname,ic,&intelligent_community::setusername);
    emit sendname(mmmname);
    disconnect(this,&VideoDisplay::sendname,ic,&intelligent_community::setusername);

    ic->show();
    this->close();
}
