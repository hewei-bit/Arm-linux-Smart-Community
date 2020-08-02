#ifndef NEW_OWNER_H
#define NEW_OWNER_H

#include <QMainWindow>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QSqlError>
#include <QtDebug>
#include <QMessageBox>
namespace Ui {
class new_owner;
}

class new_owner : public QMainWindow
{
    Q_OBJECT

public:
    explicit new_owner(QWidget *parent = nullptr);
    ~new_owner();

    void open_database();

private slots:
    void on_register_Btn_clicked();

    void on_back_Btn_clicked();


    void on_name_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_address_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_birth_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_RFID_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_password_ms_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_password_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_account_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_tele_lineEdit_cursorPositionChanged(int arg1, int arg2);


    void on_address_lineEdit_editingFinished();

    void on_birth_lineEdit_editingFinished();

    void on_RFID_lineEdit_editingFinished();

    void on_password_ms_lineEdit_editingFinished();

    void on_password_lineEdit_editingFinished();

    void on_account_lineEdit_editingFinished();

    void on_tele_lineEdit_editingFinished();

    void on_name_lineEdit_editingFinished();

    void on_address_lineEdit_selectionChanged();

    void on_birth_lineEdit_selectionChanged();

    void on_RFID_lineEdit_selectionChanged();

    void on_password_ms_lineEdit_selectionChanged();

    void on_tele_lineEdit_selectionChanged();

    void on_name_lineEdit_selectionChanged();

    void on_password_lineEdit_selectionChanged();

    void on_account_lineEdit_selectionChanged();

private:
    Ui::new_owner *ui;

//    QString dbname = "../intelligent_community/intell_com.db";

    QString dbname = "./intell_com.db";

    QSqlDatabase database;
    QSqlQuery sqlQuery;
    QString sqlSelect;
    QString sqlInsert;
    QString sqlupdate;
    QString sqldelete;
};

#endif // NEW_OWNER_H
