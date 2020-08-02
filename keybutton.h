#ifndef KEYBUTTON_H
#define KEYBUTTON_H

#include <QPushButton>



class KeyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit KeyButton(QWidget *parent = nullptr);
    explicit KeyButton(const QString &text, QWidget *parent = nullptr);
    KeyButton(const QIcon& icon, const QString &text, QWidget *parent = nullptr);

private slots:
    void button_click();
};

#endif // KEYBUTTON_H
