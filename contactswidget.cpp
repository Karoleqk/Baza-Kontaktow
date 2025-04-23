#include "contactswidget.h"
#include "ui_contactswidget.h"

ContactsWidget::ContactsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ContactsWidget)
{
    ui->setupUi(this);

    ptrCreateContact = new CreateContact();

    connect(ptrCreateContact, &CreateContact::contactAdded, this, &ContactsWidget::refreshContactsTable);

    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();

    if(!db.open()){
        qDebug() << "Error: Unable to open database..";
    }
    else{
        qDebug() << "Database open successfully..";

        QSqlQuery query(db);
        query.exec("CREATE TABLE IF NOT EXISTS contacts ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "firstName TEXT, "
                   "lastName TEXT, "
                   "phone TEXT, "
                   "email TEXT, "
                   "address TEXT)");

        if(query.lastError().isValid()) {
            qDebug() << "Table creation error:" << query.lastError().text();
        } else {
            qDebug() << "Table verified/created successfully";
        }

        QStringList headers;
        headers << "ID" << "Imie" << "Nazwisko" << "Numer telefonu" << "Email" << "Adres";
        ui->tableContacts->setColumnCount(headers.size());
        ui->tableContacts->setHorizontalHeaderLabels(headers);

        refreshContactsTable();

        ui->tableContacts->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableContacts->setSelectionBehavior(QAbstractItemView::SelectRows);

    }
}

ContactsWidget::~ContactsWidget()
{
    delete ui;
}

void ContactsWidget::on_btnCreateContact_clicked()
{
    ptrCreateContact->show();
}

void ContactsWidget::refreshContactsTable()
{
    QTableWidget* tableWidget = ui->tableContacts;

    tableWidget->setRowCount(0);

    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();

    int userId = currentUser->getId();

    if(db.open()) {
        QSqlQuery query(db);
        query.prepare(R"(
            SELECT id, first_name, last_name, phone, email,
                address_city || ', ' || address_street || ' ' || address_number || ', ' ||
                address_postal_code AS address
            FROM contacts
            WHERE user_id = :user_id
        )");

        query.bindValue(":user_id", userId);

        if(query.exec()) {
            QStringList headers;
            headers << "ID" << "Imię" << "Nazwisko" << "Telefon" << "Email" << "Adres";
            tableWidget->setColumnCount(headers.size());
            tableWidget->setHorizontalHeaderLabels(headers);

            tableWidget->verticalHeader()->setVisible(false);

            int row = 0;
            while(query.next()) {
                tableWidget->insertRow(row);

                QTableWidgetItem *idItem = new QTableWidgetItem(query.value(0).toString());
                idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
                tableWidget->setItem(row, 0, idItem);

                tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
                tableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
                tableWidget->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
                tableWidget->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
                tableWidget->setItem(row, 5, new QTableWidgetItem(query.value(5).toString()));

                row++;
            }

            tableWidget->setShowGrid(true);
            tableWidget->setGridStyle(Qt::SolidLine);
            tableWidget->setSortingEnabled(true);
            tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
            tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
            tableWidget->setAlternatingRowColors(true);
            tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

            tableWidget->resizeColumnsToContents();
            tableWidget->horizontalHeader()->setStretchLastSection(true);

        } else {
            qDebug() << "Failed to execute query:" << query.lastError().text();
        }
    } else {
        qDebug() << "Failed to open database";
    }
}
