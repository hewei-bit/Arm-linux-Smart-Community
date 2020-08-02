#include "advertisement.h"
#include "ui_advertisement.h"
#include "login.h"
#include "mylabel.h"


advertisement::advertisement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::advertisement)
{
    ui->setupUi(this);

//   connect(ui->label_2,&mylabel::myonclicked,this,&advertisement::onClicked);

    //播放视频广告
//    ad_video();

    QImage img;
    img.load(":/pic/manchester.jpg");
    QPixmap originalPixmap = QPixmap::fromImage(img);
    ui->label->setPixmap(originalPixmap.scaled(ui->label->size(),
                         Qt::IgnoreAspectRatio,
                         Qt::SmoothTransformation));



    //倒计时
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&advertisement::skip_advertisement);
    timer->start(1000);
}

advertisement::~advertisement()
{
    delete ui;
}

void advertisement::skip_advertisement()
{
    ui->commandLinkButton->setText(QString("跳过广告（%1）").arg(ad_sec));
    ui->commandLinkButton->setDisabled(true);

    if(--ad_sec == -1)
    {
        ui->commandLinkButton->setEnabled(true);
        timer->stop();
        ui->commandLinkButton->setText("跳过广告");
    }


}

void advertisement::onClicked()
{
     QMessageBox::information(this,"哈哈","label被点击了");
}


void advertisement::ad_video()
{
    if(ad_video_Process.state() == QProcess::Running)
    {
        ad_video_Process.kill();
        ad_video_Process.waitForFinished();
    }
    QString cmd = QString("mplayer -slave -quiet "
                          " -geometry 0:0 -zoom -x %1 -y %2 "
                          " -wid %3 "
                          " ./Manchester.mp4")
            .arg(ui->label->width())
            .arg(ui->label->height())
            .arg(QString::number(ui->label->winId()));
    qDebug() << "cmd = " << cmd;

    ad_video_Process.start(cmd);
}

void advertisement::on_commandLinkButton_clicked()
{
    //显示登录界面
    ((login *)this->parentWidget())->show();

    ad_video_Process.kill();
    timer->stop();

    ad_sec = 3;

    this->close();
}
