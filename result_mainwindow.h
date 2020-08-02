#ifndef RESULT_MAINWINDOW_H
#define RESULT_MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class result_MainWindow;
}

class result_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit result_MainWindow(QWidget *parent = nullptr);
    ~result_MainWindow();
signals:
    void sendname(QString s);
    void sendevaluation(QString s);
    void sendscore(QString s);

public slots:
    void showname(QString s);
    void showscore(QString s);
    void showevaluation(QString s);

private slots:
    void on_pushButton_clicked();

private:
    Ui::result_MainWindow *ui;
};

#endif // RESULT_MAINWINDOW_H
