#include "mylabel.h"

mylabel::mylabel(QWidget *parent):QLabel(parent)
{

}


mylabel::~mylabel()
{

}

void mylabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == (QEvent::MouseButtonPress))
    {
        qDebug() << "you click left button";
        emit myonclicked();
    }
}
