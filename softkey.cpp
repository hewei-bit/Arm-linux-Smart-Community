#include "softkey.h"
#include "ui_softkey.h"

SoftKey::SoftKey(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoftKey)
{
    ui->setupUi(this);
}

SoftKey::~SoftKey()
{
    delete ui;
}
