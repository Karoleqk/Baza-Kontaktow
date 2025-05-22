#ifndef CONTACTSWIDGET_H
#define CONTACTSWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include "createcontact.h"
#include "editcontact.h"

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
    void onEditButtonClicked();
    void onDeleteButtonClicked();


    void on_btnImport_clicked();

    void on_btnExport_clicked();

private:
    Ui::ContactsWidget *ui;
    CreateContact *ptrCreateContact;
    EditContact *ptrEditContact;

    int exportToCSV(QFile& file);
    int exportToJSON(QFile& file);
    int importFromCSV(QFile& file, int& errorCount);
    int importFromJSON(QFile& file, int& errorCount);
    QStringList parseCSVLine(const QString& line);
};

#endif // CONTACTSWIDGET_H
