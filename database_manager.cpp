#include "database_manager.h"

Database_Manager::Database_Manager() {
    connectionName = "mainConnection";
    dbPath = QCoreApplication::applicationDirPath() + "/../../baza danych/contacts.db";

    if(!QSqlDatabase::contains(connectionName)){
        db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
        db.setDatabaseName(dbPath);
    }
}

Database_Manager::~Database_Manager(){
    if(QSqlDatabase::contains(connectionName)){
        QSqlDatabase::database(connectionName).close();
    }
}

QSqlDatabase Database_Manager::getDatabase(){
    if(QSqlDatabase::contains(connectionName)){
        return QSqlDatabase::database(connectionName);
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
        db.setDatabaseName(dbPath);
        return db;
    }
}
