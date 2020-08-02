#ifndef BUSINESS_CENTER_H
#define BUSINESS_CENTER_H

#include <QMainWindow>

namespace Ui {
class business_center;
}

class business_center : public QMainWindow
{
    Q_OBJECT

public:
    explicit business_center(QWidget *parent = nullptr);
    ~business_center();

private slots:
    void on_owner_manage_Btn_clicked();

    void on_business_Btn_clicked();

    void on_back_Btn_clicked();

private:
    Ui::business_center *ui;
};

#endif // BUSINESS_CENTER_H
