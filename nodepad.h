#ifndef NODEPAD_H
#define NODEPAD_H

#include <QMainWindow>

namespace Ui {
class Nodepad;
}

class Nodepad : public QMainWindow
{
    Q_OBJECT

public:
    explicit Nodepad(QWidget *parent = nullptr);
    ~Nodepad();

signals:
    void sendname(QString &name);
public slots:
    void getname(QString &name);


private slots:


    void on_openpb_clicked();

    void on_editpb_clicked();

    void on_savepb_clicked();

    void on_clearpb_clicked();

    void on_setcolorpb_clicked();

    void on_setfont_clicked();

    void on_setbgcolorpb_clicked();

    void on_back_btn_clicked();

private:
    Ui::Nodepad *ui;

    QString mmmname;
};

#endif // NODEPAD_H
