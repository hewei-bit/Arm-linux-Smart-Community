#include "mange_business.h"
#include "ui_mange_business.h"

#include "login.h"

#include "business_center.h"

mange_business::mange_business(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mange_business)
{
    ui->setupUi(this);
//    open_database();
    open_table();
}

mange_business::~mange_business()
{
    delete ui;
}

void mange_business::open_database()
{
    database = QSqlDatabase::addDatabase("QSQLITE");

    database.setDatabaseName(dbname);

    if(!database.open())
    {
        qDebug() << "fail to open database";
    }
}

void mange_business::open_table()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->clearContents();

    // 设置表头
    QStringList header;
    header<<tr("序列号")<<tr("申请人")<<("联系方式")<<tr("地点")<<tr("申报内容")<<tr("任务状态");
    ui->tableWidget->setHorizontalHeaderLabels(header);
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

    int i = 0;

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    while(sqlQuery.next())
    {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(sqlQuery.value(0).toString()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(sqlQuery.value(1).toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(sqlQuery.value(2).toString()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(sqlQuery.value(3).toString()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(sqlQuery.value(4).toString()));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(sqlQuery.value(5).toString()));
//        ui->tableWidget->setItem(i,6,new QTableWidgetItem(sqlQuery.value(6).toString()));

        ui->tableWidget->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->item(i,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->item(i,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->item(i,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->item(i,4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->item(i,5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        i++;
    }
}




void mange_business::on_pushButton_2_clicked()
{
    //    change_state * cs = new change_state(this);
    //    connect(this,&mange_business::sendid,cs,&change_state::getid);
    //    ui->tableWidget->currentRow();
    //    QString mid = ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text();
    //    emit sendid(mid);
    //    disconnect(this,&mange_business::sendid,cs,&change_state::getid);
    //    cs->show();

        // 数据库读取载入
        QString sqlall = QString("SELECT * FROM business");

        if(!sqlQuery.exec(sqlall))
        {
            qDebug() << "Error:Failed to SELECT record"<< database.lastError();
        }else
        {
            qDebug() << "success";
        }

        QString mid = ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text();
        QSqlQuery query;
        query.prepare("update business set state = ? where id = ?");
        query.addBindValue(ui->comboBox->currentText());
        query.addBindValue(mid.toInt());

    //    sqlupdate = QString("update business set state = '%1' where id = %2")
    //            .arg(ui->comboBox->currentText()).arg(mid.toInt());

    //    QSqlQuery query;
    //    query.prepare("insert into business(notifier,tele,address,mission) values(?,?,?,?)");
    //    query.addBindValue("111");
    //    query.addBindValue("111");
    //    query.addBindValue("111");
    //    query.addBindValue("111");

        qDebug() <<mid;
        qDebug() <<sqlupdate;

        if(!query.exec())
        {
            qDebug() << "Error:Failed to sqlupdate record"<< database.lastError();
        }else
        {
            qDebug() << "sqlupdate success6666";
        }
        open_table();
}

void mange_business::on_back_2_clicked()
{
    business_center * bc = new business_center();
    bc->show();
    this->close();
}
