#ifndef HASH_H
#define HASH_H

#include <QString>
#include <QCryptographicHash>

class hash
{
public:
    hash();
};

QString hashPassword(QString password);

#endif // HASH_H
