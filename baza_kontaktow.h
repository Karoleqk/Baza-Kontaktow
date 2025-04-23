#ifndef BAZA_KONTAKTOW_H
#define BAZA_KONTAKTOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "registration.h"
#include "dashboard.h"
#include "user.h"
#include "database_manager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Baza_Kontaktow;
}
QT_END_NAMESPACE

class Baza_Kontaktow : public QMainWindow
{
    Q_OBJECT

public:
    Baza_Kontaktow(QWidget *parent = nullptr);
    ~Baza_Kontaktow();

private slots:
    void on_registerBtn_clicked();

    void on_loginBtn_clicked();

private:
    Ui::Baza_Kontaktow *ui;
};
#endif // BAZA_KONTAKTOW_H
