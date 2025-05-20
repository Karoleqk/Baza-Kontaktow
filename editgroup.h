#ifndef EDITGROUP_H
#define EDITGROUP_H

#include <QWidget>
#include <QMessageBox>
#include "database_manager.h"
#include "user.h"


namespace Ui {
class editGroup;
}

class editGroup : public QWidget
{
    Q_OBJECT

signals:
    void groupEdited();

public:
    explicit editGroup(QWidget *parent = nullptr);
    ~editGroup();
    int currentGroupId;

    bool loadGroupData(int groupId);

private slots:
    void on_saveBtn_clicked();

    void on_closeBtn_clicked();

private:
    Ui::editGroup *ui;
};

#endif // EDITGROUP_H
