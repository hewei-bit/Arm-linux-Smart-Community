#include "advertisement.h"

#include "intelligent_community.h"
#include "community_service.h"

#include "login.h"
#include "caular.h"
#include "news.h"
#include "nodepad.h"

#include "mange_owner.h"

#include <QFile>
#include <QApplication>

#include "edit_table_model.h"
#include "connect_database.h"

void initModel(QSqlQueryModel *model, const QString &sql)
{
    model->setQuery(sql);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("name"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("tele"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("account"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("password"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("birth"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("address"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("RFID"));
}

QTableView *createView(QSqlQueryModel *model, const QString &title)
{
    static int offset = 0;
    QTableView* view = new QTableView;
    view->setModel(model);
    view->setWindowTitle(title);
    view->move(100 + offset,100 + offset);

    offset += 20;
    view->show();
    return  view;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //定制皮肤在程序运行之前设置
    QFile file(":/qss/mystyle.qss");
    file.open(QIODevice::ReadOnly);
    QByteArray array =  file.readAll();
    #define qApp (static_cast<QApplication *>(QCoreApplication::instance()))
    qApp->setStyleSheet(array);

//    //打开数据库
//    if(!createConnection("./intell_com.db"))
//    {
//      return  1;
//    }
//    //创建数据库表
//    isCreateDatabaseTable("owner","name","tele","account","password","birth","address","RFID");
//    edit_table_model editmodel;
//    initModel(&editmodel,"select * from owner");
//    //定义一个View
//    createView(&editmodel,QObject::tr("可编辑的账户"));

//    mange_owner mo;
//    mo.show();

    login lin;
    lin.show();

//    Nodepad np;
//    np.show();

//    Caular w;
//    w.show();

//    news n;
//    n.show();

//    community_service cs;
//    cs.show();

//    intelligent_community w;
//    w.show();

//    advertisement ad;
//    ad.show();

    return a.exec();
}
