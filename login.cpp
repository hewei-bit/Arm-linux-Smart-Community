#include "login.h"
#include "ui_login.h"

#include "intelligent_community.h"

#include "business_center.h"
#include "new_owner.h"

static int count = 0;
login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/pic/school.png"));
    QImage img;
    img.load(":/pic/school.png");
    QPixmap originalPixmap = QPixmap::fromImage(img);
    ui->pic_label->setPixmap(originalPixmap.scaled(ui->pic_label->size(),
                         Qt::IgnoreAspectRatio,
                         Qt::SmoothTransformation));
//    this->setObjectName("mainWindow");
//    this->setStyleSheet("#mainWindow{border-image:url(:/pic/manchester.jpg);}");
//    this->setStyleSheet("background-image: url(:/weather/sunny_rain.png);");
//    this->setStyleSheet("background-color: rgba(255, 250, 242, 25);");

    //播广告
//    advertisement *adv = new advertisement(this);
//    adv->show();
//    this->hide();

    //隐藏键盘
    ui->widget_4->hide();

    //打开数据库
    if(count == 0)
    {
        database = QSqlDatabase::addDatabase("QSQLITE");

        database.setDatabaseName(dbname);

        if(!database.open())
        {
            qDebug() << "fail to open database";
        }
        count+=1;
    }

}

login::~login()
{
    delete ui;
    qDebug() << "login::~login()";
}

void login::open_database()
{
    database = QSqlDatabase::addDatabase("QSQLITE");

    database.setDatabaseName(dbname);

    if(!database.open())
    {
        qDebug() << "fail to open database";
    }
}

void login::on_out_btn_clicked()
{
    this->close();
}

void login::on_owner_Btn_clicked()
{

    //获取员工账号密码
    QString input_account = ui->account_lineEdit->text();
    QString input_password = ui->password_lineEdit->text();

    if((input_account=="") || (input_account == "") )
    {
        QMessageBox::warning(this,"警告","输入为空");
        return;
    }

    qDebug()<<input_account;
    qDebug()<<input_password;

    static int count = 0;

    //打开数据库
    sqlQuery = QSqlQuery(database);

    //打开整张表
    sqlSelect = QString("SELECT * FROM owner");
    if(!sqlQuery.exec(sqlSelect))
    {
        qDebug() << "Error:Failed to select record"<< database.lastError();
        QMessageBox::warning(this,"警告","用户数据丢失");
        return ;
    }
    else
    {
        qDebug() << "success select record";

    }

    //搜索
    QString sqlcheck = QString("SELECT * FROM owner where account = '%1' and password = '%2'")
            .arg(input_account).arg(input_password);
    qDebug() << sqlcheck;
    if(!sqlQuery.exec(sqlcheck))
    {
        qDebug() << "Error:Failed to select record"<< database.lastError();
        QMessageBox::warning(this,"警告","用户数据丢失");
        return ;
    }
    else
    {
        qDebug() << "success select record";
    }

    sqlQuery.next();
    QString account = sqlQuery.value(3).toString();
    QString password = sqlQuery.value(4).toString();
    QString username = sqlQuery.value(1).toString();

    if(account == input_account)
    {
        if(password == input_password)
        {
            count = 0;
//            QMessageBox QM;
            //设置文本框的大小
//            QMessageBox::information(this,QString(" %1 成功").arg(username),"success");
            //跳转
            intelligent_community * intc = new intelligent_community();
            connect(this,&login::send,intc,&intelligent_community::setusername);
            emit send(username);
            disconnect(this,&login::send,intc,&intelligent_community::setusername);
//            database.close();
            intc->show();
            this->close();
        }
        else
        {
            QMessageBox QM;
            //设置文本框的大小
            QM.setStyleSheet("QLabel{"
                             "min-width:130px;"
                             "min-height:100px; "
                                  "font-size:16px;"
                                  "}");
            QM.warning(this,"fail","password wrong");
            count+=1;
            return ;
        }
    }
    else
    {
        QMessageBox QM;
        //设置文本框的大小
        QM.setStyleSheet("QLabel{"
                         "min-width:130px;"
                         "min-height:100px; "
                              "font-size:16px;"
                              "}");
        QM.warning(this,"fail","account wrong");
        count+=1;
        return;
    }

    //超过次数
    if(count == 3)
    {
        QMessageBox QM;
        //设置文本框的大小
        QM.setStyleSheet("QLabel{"
                         "min-width:130px;"
                         "min-height:100px; "
                              "font-size:16px;"
                              "}");
        QM.warning(this,"fail","you have try 3 times");
        return;
        //        this->close();
    }
}

void login::on_property_Btn_clicked()
{

    static int count_1 = 0;
    //获取员工账号密码
    QString input_account = ui->account_lineEdit->text();
    QString input_password = ui->password_lineEdit->text();

    if((input_account=="") || (input_account == "") )
    {
        QMessageBox::warning(this,"警告","输入为空");
        return;
    }

    qDebug()<<input_account;
    qDebug()<<input_password;

    //打开数据库
    sqlQuery = QSqlQuery(database);

    //打开整张表
    sqlSelect = QString("SELECT * FROM manager");
    if(!sqlQuery.exec(sqlSelect))
    {
        qDebug() << "Error:Failed to select manager"<< database.lastError();
        QMessageBox::warning(this,"警告","用户数据丢失");
        return;

    }
    else
    {
        qDebug() << "success select manager";
    }

    //搜索
    QString sqlcheck = QString("SELECT * FROM manager where account = '%1' and password = '%2'")
            .arg(input_account).arg(input_password);
    qDebug() << sqlcheck;

    if(!sqlQuery.exec(sqlcheck))
    {
        qDebug() << "Error:Failed to select manager account and password"<< database.lastError();
        QMessageBox::warning(this,"警告","用户数据丢失");
        return;
    }
    else
    {
        qDebug() << "success select manager";
    }
    sqlQuery.next();
    QString account = sqlQuery.value(2).toString();
    QString password = sqlQuery.value(3).toString();


    if(account == input_account)
    {
        if(password == input_password)
        {
            count_1 = 0;
            QMessageBox QM;
            //设置文本框的大小
//            QMessageBox::information(this,QString(" %1 成功").arg("管理员"),"success");
            //跳转
            business_center * busi = new business_center();
//           database.close();
            busi->show();
            this->close();
        }
        else
        {
            QMessageBox QM;
            //设置文本框的大小
            QM.setStyleSheet("QLabel{"
                             "min-width:130px;"
                             "min-height:100px; "
                                  "font-size:16px;"
                                  "}");
            QM.warning(this,"fail","password wrong");
            count_1+=1;
            return;
        }
    }
    else
    {
        QMessageBox QM;
        //设置文本框的大小
        QM.setStyleSheet("QLabel{"
                         "min-width:130px;"
                         "min-height:100px; "
                              "font-size:16px;"
                              "}");
        QM.warning(this,"fail","account wrong");
        count_1+=1;
        return;
    }

    //超过次数
    if(count_1 == 3)
    {
        QMessageBox QM;
        //设置文本框的大小
        QM.setStyleSheet("QLabel{"
                         "min-width:130px;"
                         "min-height:100px; "
                              "font-size:16px;"
                              "}");
        QM.warning(this,"fail","you have try 3 times");
        this->close();
    }
}

void login::on_password_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    ui->widget_4->show();
}

void login::on_password_lineEdit_editingFinished()
{
    ui->widget_4->hide();
}

void login::on_account_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    ui->widget_4->show();
}

void login::on_account_lineEdit_editingFinished()
{
    ui->widget_4->hide();
}

void login::on_register_Btn_clicked()
{
    new_owner *now = new new_owner (this);
    now->show();
    this->hide();
}

void login::on_password_lineEdit_selectionChanged()
{
    ui->widget_4->show();
}

void login::on_account_lineEdit_selectionChanged()
{
    ui->widget_4->show();
}
