#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include "contactswidget.h"
#include "groupswidget.h"
#include "baza_kontaktow.h"
#include "user.h"

namespace Ui {
class Dashboard;
}

class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();

private slots:
    void showGroupsPage();
    void showContactsPage();
    void on_btnLogout_clicked();

private:
    Ui::Dashboard *ui;
    ContactsWidget *contactsWidget;
    GroupsWidget *groupsWidget;
};

#endif // DASHBOARD_H
