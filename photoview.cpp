#include "photoview.h"
#include "ui_photoview.h"
#include <QImage>
#include <QPixmap>
#include <QMessageBox>
#include <QFile>
void photoview::showListonWidget()
{
    ui->listWidget->clear();
    qDebug()<<"haha";
    QString sqlSelect = QString("SELECT * FROM filepath");
    if(!sqlQuery.exec(sqlSelect))
    {
          qDebug() << "Error:Failed to select record"<< database.lastError();
    }else {
        qDebug() << "success select record";
    }

    while(sqlQuery.next())
    {
        QString name = sqlQuery.value(1).toString();
        qDebug()<<name;
        ui->listWidget->addItem(name);
    }
}

photoview::photoview(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::photoview)
{
    ui->setupUi(this);
    database = QSqlDatabase::addDatabase("QSQLITE");

    //给数据库定义一个名称，后缀 .db
    database.setDatabaseName("photolist.db");

    if(! database.open())
    {
        qDebug()<<"open failed"<<database.lastError();
    }

    //    sql语句由QsqlQuery
    //    创建一个表
    QString newTable = QString("CREATE TABLE filepath(id INTEGER PRIMARY KEY AUTOINCREMENT,name varchar(100) NOT NULL )");
    qDebug() << newTable;
    QSqlQuery sqlQuery1;
    sqlQuery = sqlQuery1;
    sqlQuery.prepare(newTable);
    if(! sqlQuery.exec())
    {
        qDebug()<<"newtable already exists";
    }
    qDebug()<<"data base loaded";
}

photoview::~photoview()
{
    delete ui;
}

void photoview::writeinPhotopath(QString filename)
{
    QString sqlInsert = QString("insert into filepath(name) "
                                "values('%1')").arg(filename);
    if(! sqlQuery.exec(sqlInsert))
    {
        qDebug()<<"insert table failed"<<database.lastError();

    }
    qDebug()<<"pohto path record";
}

void photoview::on_pushButton_clicked()
{
    this->hide();
}

void photoview::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString name = item->text();
    QString path = "./";
    path += name;
    int ret = QMessageBox::information(this,"delete","是否要删除这张图片？",QMessageBox::Yes,QMessageBox::No);
    if(ret == QMessageBox::Yes)
    {
        QString sqlDelete = QString("DELETE FROM filepath "
                                    "WHERE name='%1'").arg(name);
        qDebug() << sqlDelete;

        if(!sqlQuery.exec(sqlDelete))
        {
              qDebug() << "Error:Failed to delete record"<< database.lastError();
        }else {
             qDebug() << "success delete record";
        }
        QFile filede;
        filede.setFileName(path);
        filede.remove();

        this->showListonWidget();
        ui->label->clear();

    }
    else
    {
        return;
    }

}

void photoview::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QString name = item->text();
    QString path = "./";
    path += name;
    QImage image(path);
    QPixmap pixmap = QPixmap::fromImage(image);
    QPixmap firpix = pixmap.scaled(610,450,Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->label->setPixmap(firpix);
}


