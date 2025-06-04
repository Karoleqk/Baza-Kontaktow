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


/**
 * @class Database_Manager
 *
 * @brief Deklaracja klasy, która zajmuje się wszelkimi operacjami na bazie danych
 */

class Database_Manager
{
public:
    /**
     * @brief connectionName
     *
     * Zmienna publiczna zawierająca nazwę bazy danych
     */
    QString connectionName;

    /**
     * @brief dbPath
     *
     * Zmienna publiczna zawierająca ściężkę do bazy danych
     */
    QString dbPath;

    /**
     * @brief Konstruktor klasy Database_Manager
     *
     * Przy wywołaniu, przypisuje nazwę bazy danych do zmiennej connectionName, ściężkę do bazy danych do zmiennej dbPath, po czym łączy się z bazą danych
     */
    Database_Manager();

    /**
     * @brief Destruktor klasy Database_Manager
     *
     * Zamyka połączenie z bazą danych
    */
    ~Database_Manager();

    /**
     * @brief getDatabase
     * @return zwraca połączenie z bazą danych
     *
     * Metoda, która sprawdza czy jest aktualnie połączenie z bazą danych. Jeśli tak, to zwraca to połączenie, jeśli nie to tworzy nowe i również je zwraca
     */
    QSqlDatabase getDatabase();

private:

    /**
     * @brief db
     *
     * Zmienna prywatna db przechowująca połączenie z bazą danych
     */
    QSqlDatabase db;
};

#endif // DATABASE_MANAGER_H
