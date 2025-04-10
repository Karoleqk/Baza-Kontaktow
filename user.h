#ifndef USER_H
#define USER_H

#include <QString>

class User
{
    int Id;
    QString Name;
    QString Password;

public:
    User();

    // Setters
    void setName(QString name) { Name = name; };
    void setPassword(QString password) { Password = password;};
    void setId(int id) { Id = id; };

    // Getters
    QString getName() { return Name; };
    QString getPassword() { return Password; };
    int getId() { return Id; };

};

extern User *currentUser;

#endif // USER_H
