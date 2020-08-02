#include "new_owner.h"
#include "ui_new_owner.h"
#include "login.h"


new_owner::new_owner(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::new_owner)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/pic/school.png"));

    //隐藏键盘
    ui->widget_4->hide();

    open_database();

}

new_owner::~new_owner()
{
    delete ui;
}

void new_owner::open_database()
{
    database = QSqlDatabase::addDatabase("QSQLITE");

    database.setDatabaseName(dbname);

    if(!database.open())
    {
        qDebug() << "fail to open database";
    }
}

void new_owner::on_register_Btn_clicked()
{
    //获取输入信息
    QString input_name = ui->name_lineEdit->text();
    QString input_tele = ui->tele_lineEdit->text();

    QString input_account = ui->account_lineEdit->text();
    QString input_password = ui->password_lineEdit->text();
    QString input_password_ms = ui->password_ms_lineEdit->text();

    QString input_birth = ui->birth_lineEdit->text();
    QString input_address = ui->address_lineEdit->text();
    QString input_RFID = ui->RFID_lineEdit->text();

    if((input_account=="") || (input_password == "") )
    {
        QMessageBox::warning(this,"警告","输入为空");
        return;
    }

    qDebug()<<input_account;
    qDebug()<<input_password;

    //打开数据库
    sqlQuery = QSqlQuery(database);

    //打开整张表
    sqlSelect = QString("SELECT * FROM owner");
    if(!sqlQuery.exec(sqlSelect))
    {
        qDebug() << "Error:Failed to select manager"<< database.lastError();
        QMessageBox::warning(this,"警告","用户数据丢失");
        return;
    }
    else
    {
        qDebug() << "success select owner";
    }

    //插入并检测重复
    if(input_password == input_password_ms)
    {
        sqlInsert = QString("insert into owner(name,tele,account,password,address) values('%1','%2','%3','%4','%5')")
                .arg(input_name).arg(input_tele).arg(input_account)
                .arg(input_password).arg(input_address);
        if(!sqlQuery.exec(sqlInsert))
        {
            qDebug() << "Error:Failed to Insert owner"<< database.lastError();
            QMessageBox::warning(this,"警告","用户名重复");
            return;
        }
        else
        {
            qDebug() << "success Insert owner";
        }
    }
    else
    {
        QMessageBox::warning(this,"警告","两次密码不一致");
        return;
    }
}

void new_owner::on_back_Btn_clicked()
{
    ((login *)this->parentWidget())->show();
    this->close();
}


void new_owner::on_name_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    ui->widget_4->show();
}
void new_owner::on_address_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    ui->widget_4->show();
}
void new_owner::on_birth_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    ui->widget_4->show();
}

void new_owner::on_RFID_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    ui->widget_4->show();
}

void new_owner::on_password_ms_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    ui->widget_4->show();
}

void new_owner::on_password_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    ui->widget_4->show();
}

void new_owner::on_account_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    ui->widget_4->show();
}

void new_owner::on_tele_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    ui->widget_4->show();
}


void new_owner::on_address_lineEdit_editingFinished()
{
    ui->widget_4->hide();
}
void new_owner::on_birth_lineEdit_editingFinished()
{
    ui->widget_4->hide();
}

void new_owner::on_RFID_lineEdit_editingFinished()
{
    ui->widget_4->hide();
}

void new_owner::on_password_ms_lineEdit_editingFinished()
{
    ui->widget_4->hide();
}

void new_owner::on_password_lineEdit_editingFinished()
{
    ui->widget_4->hide();
}

void new_owner::on_account_lineEdit_editingFinished()
{
    ui->widget_4->hide();
}

void new_owner::on_tele_lineEdit_editingFinished()
{
    ui->widget_4->hide();
}

void new_owner::on_name_lineEdit_editingFinished()
{
    ui->widget_4->hide();
}


void new_owner::on_address_lineEdit_selectionChanged()
{
     ui->widget_4->show();
}

void new_owner::on_birth_lineEdit_selectionChanged()
{
     ui->widget_4->show();
}

void new_owner::on_RFID_lineEdit_selectionChanged()
{
     ui->widget_4->show();
}

void new_owner::on_password_ms_lineEdit_selectionChanged()
{
     ui->widget_4->show();
}

void new_owner::on_tele_lineEdit_selectionChanged()
{
     ui->widget_4->show();
}

void new_owner::on_name_lineEdit_selectionChanged()
{
     ui->widget_4->show();
}

void new_owner::on_password_lineEdit_selectionChanged()
{
     ui->widget_4->show();
}

void new_owner::on_account_lineEdit_selectionChanged()
{
     ui->widget_4->show();
}
