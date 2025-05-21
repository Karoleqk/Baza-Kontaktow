#ifndef EDITCONTACT_H
#define EDITCONTACT_H

#include <QDialog>
#include <QMessageBox>
#include "user.h"
#include "database_manager.h"

namespace Ui {
class EditContact;
}

class EditContact : public QDialog
{
    Q_OBJECT

public:
    explicit EditContact(QWidget *parent = nullptr);
    ~EditContact();

    bool loadContactData(int contactId);

signals:
    void contactUpdated();

private slots:
    void on_btnCancel_2_clicked();

    void on_btnSave_clicked();

    void on_btnAddEmail_clicked();

    void on_btnAddPhone_clicked();

private:
    Ui::EditContact *ui;
    int m_contactId;

    void addEmailItem(const QString &email);
    void addPhoneItem(const QString &phone);
};

#endif // EDITCONTACT_H
