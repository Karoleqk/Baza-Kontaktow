#ifndef USER_H
#define USER_H

#include <QString>


/**
 * @class User
 *
 * Deklaracja klasy, która tworzy zmienna globalną aktualnie zalogowanego użytkownika
 */
class User
{
    /**
     * @brief Id
     *
     * ID zalogowanego użytkownika
     */
    int Id;

    /**
     * @brief Name
     *
     * Login zalogowanego użytkownika
     */
    QString Name;

    /**
     * @brief Password
     *
     * Hasło zalogowanego użytkownika
     */
    QString Password;

public:
    /**
     * @brief Konstruktor klasy User
     *
     * Przypisuje domyślne wartości zmiennym Id, Name i Password
     */
    User();

    // Setters
    /**
     * @brief setName
     * @param name - nazwa którą przypiszemy do naszej globalnej zmiennej currentUser
     */
    void setName(QString name) { Name = name; };

    /**
     * @brief setPassword
     * @param password - hasło, które przypiszemy do naszej globalnej zmiennej currentUser
     */
    void setPassword(QString password) { Password = password;};

    /**
     * @brief setId
     * @param id - ID, które przypiszemy do naszej globalnej zmiennej currentUser
     */
    void setId(int id) { Id = id; };

    // Getters
    /**
     * @brief getName
     * @return zwraca nam Login aktualnie zalogowanego użytkownika
     */
    QString getName() { return Name; };

    /**
     * @brief getPassword
     * @return zwraca nam Hasło aktualnie zalogowanego użytkownika
     */
    QString getPassword() { return Password; };

    /**
     * @brief getId
     * @return zwraca nam ID aktualnie zalogowanego użytkownika
     */
    int getId() { return Id; };

};

/**
 * @brief currentUser
 *
 * Tworzy zmienną globalną, która przechowuje dane aktualnie zalogowanego użytkownika
 */
extern User *currentUser;

#endif // USER_H
