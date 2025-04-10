#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QMainWindow>

#include "baza_kontaktow.h"
#include "database_manager.h"
#include "hash.h"

namespace Ui {
class Registration;
}

class Registration : public QMainWindow
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);
    ~Registration();

private slots:
    void on_loginBtn_clicked();

    void on_registerBtn_clicked();

private:
    Ui::Registration *ui;
};

#endif // REGISTRATION_H
