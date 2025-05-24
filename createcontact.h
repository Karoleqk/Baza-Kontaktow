#ifndef CREATECONTACT_H
#define CREATECONTACT_H

#include <QDialog>
#include "database_manager.h"
#include "user.h"

namespace Ui {
class CreateContact;
}

class CreateContact : public QDialog
{
    Q_OBJECT

public:
    explicit CreateContact(QWidget *parent = nullptr);
    ~CreateContact();

    void resetForm();

signals:
    void contactAdded();

private slots:
    void on_btnCancel_clicked();

    void on_btnCreate_clicked();

    void on_btnAddEmail_clicked();

    void on_btnAddPhone_clicked();

private:
    Ui::CreateContact *ui;

    void addEmailItem(const QString &email);
    void addPhoneItem(const QString &phone);

    QStringList getAllEmails() const;
    QStringList getAllPhones() const;
};

#endif // CREATECONTACT_H
