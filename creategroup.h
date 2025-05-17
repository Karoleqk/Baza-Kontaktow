#ifndef CREATEGROUP_H
#define CREATEGROUP_H

#include <QWidget>
#include "database_manager.h"
#include "user.h"

namespace Ui {
class creategroup;
}

class creategroup : public QWidget
{
    Q_OBJECT

public:
    explicit creategroup(QWidget *parent = nullptr);
    ~creategroup();

signals:
    void groupCreated();

private slots:

    void on_closeBtn_clicked();

    void on_addBtn_clicked();

private:
    Ui::creategroup *ui;
};

#endif // CREATEGROUP_H
