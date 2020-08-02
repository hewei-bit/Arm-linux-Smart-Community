#include "for_business.h"
#include "ui_for_business.h"
#include "community_service.h"


#include <QMessageBox>
for_business::for_business(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::for_business)
{
    ui->setupUi(this);
    ui->widget->hide();
}

for_business::~for_business()
{
    delete ui;
}

void for_business::getname(QString &name)
{
    mmmname = name;
    ui->name_lineEdit->setText(mmmname);
}



void for_business::on_beg_Btn_clicked()
{
    if(ui->tele_lineEdit->text() == "" or
            ui->addrr_lineEdit->text() == "" or ui->thing_lineEdit->text() == "")
    {
        QMessageBox::information(this,"警告","信息不全");
        return;
    }
    else {


//        sqlInsert = QString("insert into business(notifier,tele,address,mission) values('%1','%2','%3','%4')")
//                .arg(ui->name_lineEdit->text()).arg(ui->tele_lineEdit->text().arg(ui->addrr_lineEdit->text()).arg(ui->thing_lineEdit->text()));

        QSqlQuery query;
        query.prepare("insert into business(notifier,tele,address,mission) values(?,?,?,?)");
        query.addBindValue(ui->name_lineEdit->text());
        query.addBindValue(ui->tele_lineEdit->text());
        query.addBindValue(ui->addrr_lineEdit->text());
        query.addBindValue(ui->thing_lineEdit->text());
        if(!query.exec())
        {
            qDebug() << "Error:Failed to sqlInsert record"<< database.lastError();
        }else
        {
            qDebug() << "sqlInsert success6666";
        }

    }
}

void for_business::on_back_Btn_clicked()
{

    community_service * ic = new community_service();

    connect(this,&for_business::sendname,ic,&community_service::getname);
    emit sendname(mmmname);
    disconnect(this,&for_business::sendname,ic,&community_service::getname);

    ic->show();

    this->close();

}

void for_business::on_name_lineEdit_selectionChanged()
{
    ui->widget->show();
}

void for_business::on_name_lineEdit_editingFinished()
{
    ui->widget->hide();
}

void for_business::on_tele_lineEdit_selectionChanged()
{
    ui->widget->show();
}

void for_business::on_tele_lineEdit_editingFinished()
{
    ui->widget->hide();
}

void for_business::on_addrr_lineEdit_selectionChanged()
{
    ui->widget->show();
}

void for_business::on_addrr_lineEdit_editingFinished()
{
    ui->widget->hide();
}

void for_business::on_thing_lineEdit_editingFinished()
{
    ui->widget->hide();
}

void for_business::on_thing_lineEdit_selectionChanged()
{
    ui->widget->show();
}
