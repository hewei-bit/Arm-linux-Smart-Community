#include "leisure.h"
#include "ui_leisure.h"
#include "intelligent_community.h"

#include "nodepad.h"
#include "runningtime.h"
#include "caular.h"
#include "character_calc_mainwindow.h"

leisure::leisure(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::leisure)
{
    ui->setupUi(this);
}

leisure::~leisure()
{
    delete ui;
}

void leisure::getname(QString &name)
{
    mmmname = name;
}

void leisure::on_back_btn_clicked()
{   
    intelligent_community * ic = new intelligent_community();

    connect(this,&leisure::sendname,ic,&intelligent_community::setusername);
    emit sendname(mmmname);
    disconnect(this,&leisure::sendname,ic,&intelligent_community::setusername);

    ic->show();
    this->close();
}

void leisure::on_notepad_Btn_clicked()
{
    Nodepad * np = new Nodepad();

    connect(this,&leisure::sendname,np,&Nodepad::getname);
    emit sendname(mmmname);
    disconnect(this,&leisure::sendname,np,&Nodepad::getname);


    np->show();
    this->close();
}

void leisure::on_calc_btn_clicked()
{
    Caular *ca = new Caular();

    connect(this,&leisure::sendname,ca,&Caular::getname);
    emit sendname(mmmname);
    disconnect(this,&leisure::sendname,ca,&Caular::getname);


    ca->show();
    this->close();
}

void leisure::on_stopwatch_Btn_clicked()
{

    runningTimer *runT = new runningTimer();

    connect(this,&leisure::sendname,runT,&runningTimer::getname);
    emit sendname(mmmname);
    disconnect(this,&leisure::sendname,runT,&runningTimer::getname);


    runT->show();
    this->close();


}

void leisure::on_game_Btn_clicked()
{
    character_calc_MainWindow *w = new character_calc_MainWindow();

    connect(this,&leisure::sendname,w,&character_calc_MainWindow::getname);
    emit sendname(mmmname);
    disconnect(this,&leisure::sendname,w,&character_calc_MainWindow::getname);

    w->show();
    this->close();


}
