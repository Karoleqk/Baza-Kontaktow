#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlTableModel>
#include <QFile>

class Database_Manager
{
public:
    QString connectionName;

    Database_Manager();
    ~Database_Manager();

    QSqlDatabase getDatabase();

private:
    QSqlDatabase db;
};

#endif // DATABASE_MANAGER_H
