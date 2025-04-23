#ifndef CONTACTSWIDGET_H
#define CONTACTSWIDGET_H

#include <QWidget>
#include "createcontact.h"
#include "createcontact.h"

namespace Ui {
class ContactsWidget;
}

class ContactsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ContactsWidget(QWidget *parent = nullptr);
    ~ContactsWidget();

    void refreshContactsTable();

private slots:
    void on_btnCreateContact_clicked();

private:
    Ui::ContactsWidget *ui;
    CreateContact *ptrCreateContact;
};

#endif // CONTACTSWIDGET_H
