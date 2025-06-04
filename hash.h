#ifndef HASH_H
#define HASH_H

#include <QString>
#include <QCryptographicHash>


/**
 * @class hash
 *
 * @brief Deklaracja klasy do hashowania haseł
 */
class hash
{
public:

    /**
     * @brief Konstruktor klasy hash
     */
    hash();
};

/**
 * @brief hashPassword
 * @param password - hasło które chcemy zahashować
 * @return Zwraca zahashowane hasło
 *
 * Metoda zwraca nam hasło, w formacie Sha256
 */
QString hashPassword(QString password);

#endif // HASH_H
