#ifndef SOFTKEY_H
#define SOFTKEY_H

#include <QWidget>

namespace Ui {
class SoftKey;
}

class SoftKey : public QWidget
{
    Q_OBJECT

public:
    explicit SoftKey(QWidget *parent = nullptr);
    ~SoftKey();

private:
    Ui::SoftKey *ui;
};

#endif // SOFTKEY_H
