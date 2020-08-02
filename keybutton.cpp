#include "keybutton.h"

#include <QApplication>
#include <QKeyEvent>
#include <QDebug>

KeyButton::KeyButton(QWidget *parent)
    :QPushButton(parent)
{
    connect(this, &KeyButton::clicked, this, &KeyButton::button_click);
}

KeyButton::KeyButton(const QString &text, QWidget *parent)
    :QPushButton(text,parent)
{
    connect(this, &KeyButton::clicked, this, &KeyButton::button_click);
}

KeyButton::KeyButton(const QIcon &icon, const QString &text, QWidget *parent)
    :QPushButton(icon,text,parent)
{
    connect(this, &KeyButton::clicked, this, &KeyButton::button_click);
}

void KeyButton::button_click()
{
    QString str = this->text();//获取按键字符串
    qDebug()<<str;

    //模拟键盘q键按下--自定义一个q键的事件
    QKeyEvent *key = nullptr ;

    if(QString("0123456789qwertyuiopasdfghjklzxcvbnm,.").contains(str) && !str.isEmpty())
    {
       char ch = str.at(0).toLatin1();//获取字符串中的第一个字符
       key = new QKeyEvent(QKeyEvent::KeyPress, ch,Qt::NoModifier, str);
    }else if(str == "Del")
    {
        //定义一个事件，Key_Backspace撤消按钮
       key = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Backspace,Qt::NoModifier);

    }else if(str == "Enter")
    {
       key = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Return,Qt::NoModifier);

    }
    else if(str.isEmpty())
    {
       key = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Space,Qt::NoModifier," ");
    }

    //通过postEvent将事件key发送出去
    QApplication::postEvent(QApplication::focusWidget(), key);
}
