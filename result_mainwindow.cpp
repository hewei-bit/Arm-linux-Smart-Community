#include "result_mainwindow.h"
#include "ui_result_mainwindow.h"
#include "character_calc_mainwindow.h"


result_MainWindow::result_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::result_MainWindow)
{
    ui->setupUi(this);
}

void result_MainWindow::showname(QString s)
{
    ui->name_textBrowser->setText(s);
}

void result_MainWindow::showscore(QString s)
{
    ui->score_textBrowser_2->setText(s);
}

void result_MainWindow::showevaluation(QString s)
{
    ui->con_textBrowser_3->setText(s);
}



result_MainWindow::~result_MainWindow()
{
    delete ui;
}

void result_MainWindow::on_pushButton_clicked()
{
    ((character_calc_MainWindow *)this->parentWidget())->show();

    this->close();
}
