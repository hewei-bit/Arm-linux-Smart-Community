#ifndef CHARACTER_CALC_MAINWINDOW_H
#define CHARACTER_CALC_MAINWINDOW_H


#include <QMainWindow>

namespace Ui {
class character_calc_MainWindow;
}

class character_calc_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit character_calc_MainWindow(QWidget *parent = nullptr);
    ~character_calc_MainWindow();

signals:
    void sendname(QString &name);
public slots:
    void getname(QString &name);

public slots:
    void showresult();


private slots:
    void on_pushButton_clicked();

    void on_name_editingFinished();

    void on_name_selectionChanged();

private:
    Ui::character_calc_MainWindow *ui;
    QString mmmname;
};

#endif // CHARACTER_CALC_MAINWINDOW_H
