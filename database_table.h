#ifndef DATABASE_TABLE_H
#define DATABASE_TABLE_H
#include <QString>

class Database_table
{
public:
    Database_table(QString nameTable,QString name,
                   QString tele,QString account,
                   QString password,QString birth,QString address,QString RFID)
        :nameTable(nameTable),name(name),tele(tele),account(account),
          password(password),birth(birth),address(address),RFID(RFID)
    {

    }
    QString getTableName() const
    {
        return nameTable;
    }
    QString getName() const
    {
        return name;
    }
    QString getTele() const
    {
        return tele;
    }
    QString getAccount() const
    {
        return account;
    }
    QString getPassword() const
    {
        return password;
    }

    QString getBirth() const
    {
        return birth;
    }
    QString getAddress() const
    {
        return address;
    }
    QString getRFID() const
    {
        return RFID;
    }

private:
    QString nameTable;
    QString name;
    QString tele;
    QString account;
    QString password;
    QString birth;
    QString address;
    QString RFID;
};






























#endif // DATABASE_TABLE_H
