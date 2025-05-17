#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <QString>
#include <QCoreApplication>
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
    QString dbPath;

    Database_Manager();
    ~Database_Manager();

    QSqlDatabase getDatabase();

private:
    QSqlDatabase db;
};

#endif // DATABASE_MANAGER_H
