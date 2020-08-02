#ifndef ADVERTISEMENT_H
#define ADVERTISEMENT_H

#include <QWidget>
#include <QTimer>

#include <QProcess>
#include <QtDebug>
#include <QMessageBox>




namespace Ui {
class advertisement;
}

class advertisement : public QWidget
{
    Q_OBJECT

public:
    explicit advertisement(QWidget *parent = nullptr);
    ~advertisement();

    void skip_advertisement();

    void ad_video();

private slots:
    void on_commandLinkButton_clicked();

    void onClicked();

private:
    Ui::advertisement *ui;
    QProcess ad_video_Process;
    QTimer *timer;

};
static int ad_sec = 3;

#endif // ADVERTISEMENT_H
