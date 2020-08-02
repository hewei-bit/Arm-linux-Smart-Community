#include "community_service.h"
#include "ui_community_service.h"
#include "intelligent_community.h"


#include "for_business.h"

#include <QMessageBox>

void community_service::open_table(QString &name)
{
    ui->business_tableWidget->clear();
    ui->business_tableWidget->setRowCount(0);
    ui->business_tableWidget->clearContents();

    // 设置表头
    QStringList header;
    header<<tr("序列号")<<tr("申请人")<<("联系方式")<<tr("地点")<<tr("报修内容")<<tr("订单状态");
    ui->business_tableWidget->setHorizontalHeaderLabels(header);
    qDebug() <<header;


    // 数据库读取载入
    QString sqlall = QString("SELECT * FROM business");

    if(!sqlQuery.exec(sqlall))
    {
        qDebug() << "Error:Failed to SELECT record"<< database.lastError();
    }else
    {
        qDebug() << "success";
    }


    QString sqlorder = QString("SELECT * FROM business where notifier = '%1' ").arg(name);

    if(!sqlQuery.exec(sqlorder))
    {
        qDebug() << "Error:Failed to SELECT record"<< database.lastError();
    }else
    {
        qDebug() << "success6666";
    }

    int i = 0;

    ui->business_tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    while(sqlQuery.next())
    {

//        qDebug()<<sqlQuery.value(0)<<sqlQuery.value(1)<<sqlQuery.value(2)<<sqlQuery.value(3)<<sqlQuery.value(4);
        ui->business_tableWidget->insertRow(i);
        ui->business_tableWidget->setItem(i,0,new QTableWidgetItem(sqlQuery.value(0).toString()));
        ui->business_tableWidget->setItem(i,1,new QTableWidgetItem(sqlQuery.value(1).toString()));
        ui->business_tableWidget->setItem(i,2,new QTableWidgetItem(sqlQuery.value(2).toString()));
        ui->business_tableWidget->setItem(i,3,new QTableWidgetItem(sqlQuery.value(3).toString()));
        ui->business_tableWidget->setItem(i,4,new QTableWidgetItem(sqlQuery.value(4).toString()));
        ui->business_tableWidget->setItem(i,5,new QTableWidgetItem(sqlQuery.value(5).toString()));

        ui->business_tableWidget->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->business_tableWidget->item(i,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->business_tableWidget->item(i,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->business_tableWidget->item(i,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->business_tableWidget->item(i,4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        i++;
    }
}

void community_service::getname(QString &name)
{
    mmmname = name;
    open_table(mmmname);
}

community_service::community_service(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::community_service)
{
    ui->setupUi(this);
}

community_service::~community_service()
{
    delete ui;
}

void community_service::on_pushButton_clicked()
{
    intelligent_community * ic = new intelligent_community();

    connect(this,&community_service::sendname,ic,&intelligent_community::setusername);
    emit sendname(mmmname);
    disconnect(this,&community_service::sendname,ic,&intelligent_community::setusername);

    ic->show();

    this->close();
}

void community_service::on_pushButton_2_clicked()
{
    for_business *fb = new for_business();

    connect(this,&community_service::sendname,fb,&for_business::getname);
    emit sendname(mmmname);
    disconnect(this,&community_service::sendname,fb,&for_business::getname);

    fb->show();
    this->close();

}

void community_service::on_check_Btn_clicked()
{
    qDebug() <<mmmname;
    open_table(mmmname);
}
