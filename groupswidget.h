#ifndef GROUPSWIDGET_H
#define GROUPSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QFont>
#include <QMessageBox>
#include "creategroup.h"
#include "editgroup.h"
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
    void on_editBtn_clicked();
    void on_deleteBtn_clicked();
    void on_showBtn_clicked();

public slots:
    void reloadGroups();

private:
    Ui::GroupsWidget *ui;
    creategroup *grpPtr;
    editGroup *editGrpPtr;
};

#endif // GROUPSWIDGET_H
