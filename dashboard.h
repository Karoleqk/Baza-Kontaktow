#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include "createcontact.h"

namespace Ui {
class Dashboard;
}

class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();

    void refreshContactsTable();

private slots:
    void on_btnCreateContact_clicked();

private:
    Ui::Dashboard *ui;
    CreateContact *ptrCreateContact;
};

#endif // DASHBOARD_H
