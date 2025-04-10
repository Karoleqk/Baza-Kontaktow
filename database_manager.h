#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>

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
