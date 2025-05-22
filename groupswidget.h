#ifndef GROUPSWIDGET_H
#define GROUPSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QFont>
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonObject>
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

    void on_btnImport_clicked();

    void on_btnExport_clicked();

public slots:
    void reloadGroups();

private:
    Ui::GroupsWidget *ui;
    creategroup *grpPtr;
    editGroup *editGrpPtr;

    int exportToCSV(QFile& file);
    int exportToJSON(QFile& file);
    int importGroupsFromCSV(QFile& file, int& errorCount);
    int importGroupsFromJSON(QFile& file, int& errorCount);
    QStringList parseCSVLine(const QString& line);
};

#endif // GROUPSWIDGET_H
