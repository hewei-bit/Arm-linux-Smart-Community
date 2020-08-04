#include "mange_owner.h"
#include "ui_mange_owner.h"
#include "login.h"

#include "business_center.h"

#include "edit_table_model.h"
#include "connect_database.h"


#include <QMessageBox>

mange_owner::mange_owner(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mange_owner)
{
    ui->setupUi(this);

    open_table();
    ui->widget->hide();

//    editmodel->clear();
//    /* 设置表格标题行(输入数据为QStringList类型) */
//    editmodel->setHorizontalHeaderLabels({"ID","种类","名称","库存","进价","售价","单位"});
//    /* 自适应所有列，让它布满空间 */
//    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

//    //打开数据库
//    if(!createConnection("./intell_com.db"))
//    {
//        qDebug() << "cannot open database";
//        return ;
//    }
//    //创建数据库表
//    isCreateDatabaseTable("owner","name","tele","account","password","birth","address","RFID");
//    edit_table_model editmodel;
//    initModel(editmodel,"SELECT * FROM owner");
//    //定义一个View
//    createView(editmodel,QObject::tr("可编辑的账户"));

//    ui->tableView->setModel(&editmodel);

}

mange_owner::~mange_owner()
{
    delete ui;
}

void mange_owner::open_table()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->clearContents();

    // 设置表头
    QStringList header;
    header<<tr("序列号")<<tr("姓名")<<("联系方式")<<tr("登录名")<<tr("密码")<<tr("生日")<<tr("地址")<<tr("RFID");
    ui->tableWidget->setHorizontalHeaderLabels(header);
    qDebug() <<header;

    // 数据库读取载入
    QString sqlall = QString("SELECT * FROM owner");

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
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(sqlQuery.value(6).toString()));


        ui->tableWidget->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->item(i,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->item(i,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->item(i,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->item(i,4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->item(i,5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        i++;
    }
}

void mange_owner::open_database()
{
    database = QSqlDatabase::addDatabase("QSQLITE");

    database.setDatabaseName(dbname);

    if(!database.open())
    {
        qDebug() << "fail to open database";
    }
}

void mange_owner::initModel(QSqlQueryModel &model, const QString &sql)
{
    model.setQuery(sql);
    model.setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
    model.setHeaderData(1,Qt::Horizontal,QObject::tr("name"));
    model.setHeaderData(2,Qt::Horizontal,QObject::tr("tele"));
    model.setHeaderData(3,Qt::Horizontal,QObject::tr("account"));
    model.setHeaderData(4,Qt::Horizontal,QObject::tr("password"));
    model.setHeaderData(5,Qt::Horizontal,QObject::tr("birth"));
    model.setHeaderData(6,Qt::Horizontal,QObject::tr("address"));
    model.setHeaderData(7,Qt::Horizontal,QObject::tr("RFID"));
}

QTableView *mange_owner::createView(QSqlQueryModel &model, const QString &title)
{
    static int offset = 0;
    QTableView* view = new QTableView;
    view->setModel(&model);
    view->setWindowTitle(title);
    view->move(100 + offset,100 + offset);

    offset += 20;
    view->show();
    return  view;
}

void mange_owner::on_back_clicked()
{
    business_center * bc = new business_center();
    bc->show();
    this->close();
}

void mange_owner::on_add_Btn_clicked()
{

//    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
//    ui->tableWidget->setItem(ui->tableWidget->rowCount(),1,new QTableWidgetItem(ui->name_lineEdit->text()));
//    ui->tableWidget->setItem(ui->tableWidget->rowCount(),2,new QTableWidgetItem(ui->tele_lineEdit->text()));
//    ui->tableWidget->setItem(ui->tableWidget->rowCount(),3,new QTableWidgetItem(ui->account_lineEdit->text()));
//    ui->tableWidget->setItem(ui->tableWidget->rowCount(),4,new QTableWidgetItem(ui->password_lineEdit->text()));
//    ui->tableWidget->setItem(ui->tableWidget->rowCount(),5,new QTableWidgetItem(ui->birth_lineEdit->text()));
//    ui->tableWidget->setItem(ui->tableWidget->rowCount(),6,new QTableWidgetItem(ui->addr_lineEdit->text()));
//    ui->tableWidget->setItem(ui->tableWidget->rowCount(),7,new QTableWidgetItem(ui->RFID_lineEdit->text()));

    if(ui->account_lineEdit->text() == "" or ui->password_lineEdit->text() == "")
    {
        QMessageBox::warning(this,"警告","信息录入不全");
        return ;
    }

    QString mid = ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text();
    QSqlQuery query;
//    query.prepare("insert into owner(name,tele,account,password,birth,address,RFID) values('','','123644621','12355','','','')");

    query.prepare("insert into owner(name,tele,account,password,birth,address,RFID) values(?,?,?,?,?,?,?)");
    query.addBindValue(ui->name_lineEdit->text());
    query.addBindValue(ui->tele_lineEdit->text());
    query.addBindValue(ui->account_lineEdit->text());
    query.addBindValue(ui->password_lineEdit->text());
    query.addBindValue(ui->dateEdit->text());
    query.addBindValue(ui->addr_lineEdit->text());
    query.addBindValue(ui->RFID_lineEdit->text());

    qDebug() <<ui->name_lineEdit->text()<< " "<<ui->tele_lineEdit->text()<<" "
            <<ui->account_lineEdit->text()<< " "<<ui->password_lineEdit->text()<<" "
           <<ui->dateEdit->text()<< " "<<ui->addr_lineEdit->text()<< " "
          <<ui->RFID_lineEdit->text();


    if(!query.exec())
    {
        qDebug() << "Error:Failed to sqlupdate record"<< database.lastError();
        QMessageBox::warning(this,"警告","信息录入失败，账号重复");
    }else
    {
        qDebug() << "sqlupdate success6666";
    }
    open_table();



}

void mange_owner::on_delete_Btn_clicked()
{
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
    query.prepare("DELETE FROM owner WHERE id = ?");
    query.addBindValue(mid.toInt());

    qDebug() <<mid;

    if(!query.exec())
    {
        qDebug() << "Error:Failed to sqldelete record"<< database.lastError();
    }else
    {
        qDebug() << "sqldelete success6666";
    }
    open_table();

}

void mange_owner::on_update_Btn_clicked()
{
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
    QString mitem = ui->tableWidget->item(ui->tableWidget->currentRow(),ui->tableWidget->currentColumn())->text();
    QSqlQuery query;
    if(ui->tableWidget->currentColumn() == 1)
    {

        query.prepare("update business set name = ? where id = ?");
        query.addBindValue(mitem);
        query.addBindValue(mid.toInt());
    }
    if(ui->tableWidget->currentColumn() == 2)
    {
        query.prepare("update business set tele = ? where id = ?");
        query.addBindValue(mitem);
        query.addBindValue(mid.toInt());
    }
    if(ui->tableWidget->currentColumn() == 3)
    {

        query.prepare("update business set account = ? where id = ?");
        query.addBindValue(mitem);
        query.addBindValue(mid.toInt());
    }
    if(ui->tableWidget->currentColumn() == 4)
    {

        query.prepare("update business set password = ? where id = ?");
        query.addBindValue(mitem);
        query.addBindValue(mid.toInt());
    }
    if(ui->tableWidget->currentColumn() == 5)
    {

        query.prepare("update business set birth = ? where id = ?");
        query.addBindValue(mitem);
        query.addBindValue(mid.toInt());
    }
    if(ui->tableWidget->currentColumn() == 6)
    {

        query.prepare("update business set address = ? where id = ?");
        query.addBindValue(mitem);
        query.addBindValue(mid.toInt());
    }
    if(ui->tableWidget->currentColumn() == 7)
    {

        query.prepare("update business set RFID = ? where id = ?");
        query.addBindValue(mitem);
        query.addBindValue(mid.toInt());
    }

    qDebug() <<mid;
    qDebug() <<mitem;
    if(!query.exec())
    {
        qDebug() << "Error:Failed to sqlupdate record"<< database.lastError();
    }else
    {
        qDebug() << "sqlupdate success6666";
    }
    open_table();
}

void mange_owner::on_RFID_lineEdit_selectionChanged()
{
ui->widget->show();
}

void mange_owner::on_RFID_lineEdit_editingFinished()
{
ui->widget->hide();
}

void mange_owner::on_addr_lineEdit_selectionChanged()
{
ui->widget->show();
}

void mange_owner::on_addr_lineEdit_editingFinished()
{
ui->widget->hide();
}

void mange_owner::on_password_lineEdit_editingFinished()
{
ui->widget->hide();
}

void mange_owner::on_password_lineEdit_selectionChanged()
{
ui->widget->show();
}

void mange_owner::on_account_lineEdit_editingFinished()
{
ui->widget->hide();
}

void mange_owner::on_account_lineEdit_selectionChanged()
{
ui->widget->show();
}

void mange_owner::on_tele_lineEdit_editingFinished()
{
ui->widget->hide();
}

void mange_owner::on_tele_lineEdit_selectionChanged()
{
ui->widget->show();
}

void mange_owner::on_name_lineEdit_selectionChanged()
{
ui->widget->show();
}

void mange_owner::on_name_lineEdit_editingFinished()
{
ui->widget->hide();
}

void mange_owner::on_tableWidget_itemSelectionChanged()
{
//    ui->widget->hide();
}

void mange_owner::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
//    ui->widget->show();
}
