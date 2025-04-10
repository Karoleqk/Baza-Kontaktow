#include "hash.h"

hash::hash() {}

QString hashPassword(QString password){
    QByteArray hashed = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return QString(hashed.toHex());
}
