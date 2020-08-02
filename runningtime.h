#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>

namespace Ui {
class MainWindow;
}

class runningTimer : public QMainWindow
{
    Q_OBJECT

public:
    explicit runningTimer(QWidget *parent = nullptr);
    ~runningTimer();
signals:
    void sendname(QString &name);
public slots:
    void getname(QString &name);
private slots:
    void on_start_Btn_clicked();

    void on_reset_Btn_clicked();

    void on_count_Btn_clicked();

    void on_stop_Btn_clicked();

    void show_sec();
    void on_back_Btn_clicked();

    void on_clear_Btn_clicked();

private:
    Ui::MainWindow *ui;
    QTimer* mTimer;
    static int num;
QString mmmname;

};

#endif // MAINWINDOW_H
