#include "character_calc_mainwindow.h"
#include "ui_character_calc_mainwindow.h"
#include "result_mainwindow.h"
#include "leisure.h"
#include <QtDebug>
#include <QMessageBox>

#include <iostream>
#include <cstdlib>
#include <ctime>

character_calc_MainWindow::character_calc_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::character_calc_MainWindow)
{
    ui->setupUi(this);

    connect(ui->test_PB,&QPushButton::clicked,this,&character_calc_MainWindow::showresult);

    ui->widget->hide();
}

character_calc_MainWindow::~character_calc_MainWindow()
{
    delete ui;
}

void character_calc_MainWindow::getname(QString &name)
{
    mmmname = name;
}

void character_calc_MainWindow::showresult()
{
    qDebug() << "------";
    QString Qname = ui->name->text();
    if (Qname == "")
    {
        QMessageBox::warning(this,"警告","名字不能为空");
        return ;
    }
    result_MainWindow* rm = new result_MainWindow(this);
    rm->show();


    srand((int)time(0));

    int num = rand()%100;


    connect(rm,&result_MainWindow::sendname,rm,&result_MainWindow::showname);
    emit rm->sendname(Qname);

    connect(rm,&result_MainWindow::sendscore,rm,&result_MainWindow::showscore);
    emit rm->sendscore(QString::number(num));
    QString Qevalution;
    if(num >90)
    {
        Qevalution = "你的人品很好";
    }
    else if(60 < num)
    {
        Qevalution = "你的人品一般";
    }
    else
    {
        Qevalution = "你的人品不行呀";
    }

    connect(rm,&result_MainWindow::sendevaluation,rm,&result_MainWindow::showevaluation);
    emit rm->sendevaluation(Qevalution);


    ui->name->clear();
    this->hide();

}

void character_calc_MainWindow::on_pushButton_clicked()
{
    leisure * np = new leisure();

    connect(this,&character_calc_MainWindow::sendname,np,&leisure::getname);
    emit sendname(mmmname);
    disconnect(this,&character_calc_MainWindow::sendname,np,&leisure::getname);

    np->show();
    this->close();
}

void character_calc_MainWindow::on_name_editingFinished()
{
    ui->widget->hide();
}

void character_calc_MainWindow::on_name_selectionChanged()
{
    ui->widget->show();
}
