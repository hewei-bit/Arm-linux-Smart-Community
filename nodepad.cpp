#include "nodepad.h"
#include "ui_nodepad.h"
#include <QFileDialog>
#include <QFile>
#include <QColorDialog>
#include <QColor>
#include <QFontDialog>
#include <QFont>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QTextCodec>

#include "leisure.h"

Nodepad::Nodepad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Nodepad)
{
    ui->setupUi(this);
    ui->showfile->setReadOnly(true);
    this->setWindowTitle("记事本");
    ui->widget->hide();
}

Nodepad::~Nodepad()
{
    delete ui;
    qDebug() << "Nodepad::~Nodepad()";
}

void Nodepad::getname(QString &name)
{
    mmmname = name;
}

void Nodepad::on_openpb_clicked()
{
    QTextCodec *codec = QTextCodec::codecForName("GBK");
    QString name=QFileDialog::getOpenFileName();
    qDebug() << name;
    QFile f(name);
    if(!f.open(QIODevice::ReadOnly|QIODevice::Text))
        return;
    QString text=codec->toUnicode(f.readAll());
    ui->showfile->append(text);
    f.close();
    qDebug() << "ui->showfile->append(text);";
}

void Nodepad::on_editpb_clicked()
{

    QString name=QString("是否确定启动%1？").arg(ui->editpb->text());
    int ret=QMessageBox::warning(this,"提示",name,"确定","取消");
    if(ui->editpb->text()=="编辑模式")
    {
        if(ret==0)
        {
            ui->showfile->setReadOnly(false);
            ui->editpb->setText("非编辑模式");
            ui->widget->show();
        }
        else
        {
            return ;
        }
    }
    else
    {
    ui->showfile->setReadOnly(true);
    ui->editpb->setText("编辑模式");
    ui->widget->hide();
    }
}

void Nodepad::on_savepb_clicked()
{
    int ret=QMessageBox::warning(this,"提示界面","是否确定保存该文件？","确定","取消");
    qDebug()<<ret;
    if(ret==0)
    {
        QString name=QFileDialog::getSaveFileName();
        QFile f(name);
        if(!f.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append))
            return;
       QString text=ui->showfile->toPlainText();
        f.write(text.toUtf8());
        f.close();
    }
    else {
        return;
    }

}

void Nodepad::on_clearpb_clicked()
{
    ui->showfile->clear();
}

void Nodepad::on_setcolorpb_clicked()
{
    QColor color= QColorDialog::getColor();
    if(!color.isValid())return;
    QString oldinfo=ui->showfile->styleSheet();
    QString name=QString("%1;color: %2;").arg(oldinfo).arg(color.name());
    ui->showfile->setStyleSheet(name);
}

void Nodepad::on_setfont_clicked()
{
    bool ok;
    QFont font=QFontDialog::getFont(&ok,this);
    if(ok)
    {
        ui->showfile->setFont(font);
    }
}

void Nodepad::on_setbgcolorpb_clicked()
{
    QColor color= QColorDialog::getColor();
    if(!color.isValid())return;
    QString oldinfo=ui->showfile->styleSheet();
    QString name=QString("%1;background-color: %2;").arg(oldinfo).arg(color.name());
    ui->showfile->setStyleSheet(name);
}

void Nodepad::on_back_btn_clicked()
{
    leisure * np = new leisure();

    connect(this,&Nodepad::sendname,np,&leisure::getname);
    emit sendname(mmmname);
    disconnect(this,&Nodepad::sendname,np,&leisure::getname);

    np->show();
    this->close();
}
