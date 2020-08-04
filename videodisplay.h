#ifndef VIDEODISPLAY_H
#define VIDEODISPLAY_H

#include <QWidget>
#include "v4l2.h"
#include <QTimer>
#include "photoview.h"
namespace Ui {
class videodisplay;
}

class videodisplay : public QWidget
{
    Q_OBJECT

public:
    explicit videodisplay(QWidget *parent = nullptr);
    ~videodisplay();
signals:
    void sendname(QString &name);
public slots:
    void getname(QString &name);
    void on_startBtn_clicked();
    void flushButff();

//    void shotscreen();


private slots:
    void on_shotBtn_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::videodisplay *ui;
    pass_data pd; //定义一个相关的摄像头对象
    photoview *filelist;
     unsigned char *bufrgb; //获取摄像头数据指针
     QTimer *timer;
     QString mmmname;
};

#endif // VIDEODISPLAY_H
