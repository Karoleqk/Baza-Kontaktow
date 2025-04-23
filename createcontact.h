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

signals:
    void contactAdded();

private slots:
    void on_btnCancel_clicked();

    void on_btnCreate_clicked();

private:
    Ui::CreateContact *ui;
};

#endif // CREATECONTACT_H
