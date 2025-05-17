#ifndef GROUPSWIDGET_H
#define GROUPSWIDGET_H

#include <QWidget>
#include <QLabel>
#include "creategroup.h"
#include "database_manager.h"
#include "user.h"

namespace Ui {
class GroupsWidget;
}

class GroupsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GroupsWidget(QWidget *parent = nullptr);
    ~GroupsWidget();

private slots:
    void on_addGroupBtn_clicked();

public slots:
    void reloadGroups();

private:
    Ui::GroupsWidget *ui;
};

#endif // GROUPSWIDGET_H
