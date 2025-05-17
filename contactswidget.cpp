#include "contactswidget.h"
#include "ui_contactswidget.h"

ContactsWidget::ContactsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ContactsWidget)
{
    ui->setupUi(this);

    ptrCreateContact = new CreateContact(this);
    ptrEditContact = new EditContact(this);

    connect(ptrCreateContact, &CreateContact::contactAdded, this, &ContactsWidget::refreshContactsTable);
    connect(ptrEditContact, &EditContact::contactUpdated, this, &ContactsWidget::refreshContactsTable);
    connect(ui->inputSearch, &QLineEdit::textChanged, this, &ContactsWidget::refreshContactsTable);



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
    ptrCreateContact->setModal(true);
    ptrCreateContact->show();
}

void ContactsWidget::refreshContactsTable()
{
    QTableWidget* tableWidget = ui->tableContacts;

    tableWidget->setRowCount(0);

    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();

    int userId = currentUser->getId();

    QString searchText = ui->inputSearch->text().trimmed();
    bool isSearching = !searchText.isEmpty();

    if(db.open()) {
        QString countSql = R"(
            SELECT COUNT(*) FROM contacts
            WHERE user_id = :user_id
        )";

        if (isSearching) {
            searchText = "%" + searchText + "%";
            countSql += R"(
                AND (
                    first_name LIKE :search OR
                    last_name LIKE :search OR
                    phone LIKE :search OR
                    email LIKE :search OR
                    address_city LIKE :search OR
                    address_street LIKE :search OR
                    address_postal_code LIKE :search
                )
            )";
        }

        QSqlQuery countQuery(db);
        countQuery.prepare(countSql);
        countQuery.bindValue(":user_id", userId);

        if (isSearching) {
            countQuery.bindValue(":search", searchText);
        }

        int totalContacts = 0;
        if (countQuery.exec() && countQuery.next()) {
            totalContacts = countQuery.value(0).toInt();
            ui->labelTotal->setText(QString::number(totalContacts));
        } else {
            ui->labelTotal->setText("0");
        }


        QSqlQuery query(db);

        QString sql = R"(
            SELECT id, first_name, last_name, phone, email,
                address_city || ', ' || address_street || ' ' || address_number || ', ' ||
                address_postal_code AS address
            FROM contacts
            WHERE user_id = :user_id
        )";

        if (isSearching) {
            searchText = "%" + searchText + "%";
            sql += R"(
                AND (
                    first_name LIKE :search OR
                    last_name LIKE :search OR
                    phone LIKE :search OR
                    email LIKE :search OR
                    address_city LIKE :search OR
                    address_street LIKE :search OR
                    address_postal_code LIKE :search
                )
            )";
        }


        query.prepare(sql);
        query.bindValue(":user_id", userId);

        if(isSearching){
            query.bindValue(":search", searchText);
        }

        if(query.exec()) {
            QStringList headers;
            headers << "ID" << "Imię" << "Nazwisko" << "Telefon" << "Email" << "Adres" << "Akcje";
            tableWidget->setColumnCount(headers.size());
            tableWidget->setHorizontalHeaderLabels(headers);

            tableWidget->verticalHeader()->setVisible(false);

            int row = 0;
            while(query.next()) {
                tableWidget->insertRow(row);

                int contactId = query.value(0).toInt();

                QTableWidgetItem *idItem = new QTableWidgetItem(query.value(0).toString());
                idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
                tableWidget->setItem(row, 0, idItem);

                tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
                tableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
                tableWidget->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
                tableWidget->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
                tableWidget->setItem(row, 5, new QTableWidgetItem(query.value(5).toString()));

                QWidget* buttonsWidget = new QWidget();
                QHBoxLayout* buttonsLayout = new QHBoxLayout(buttonsWidget);
                buttonsLayout->setContentsMargins(2, 2, 2, 2);
                buttonsLayout->setSpacing(4);

                QPushButton* editButton = new QPushButton("Edytuj");
                editButton->setProperty("contactId", contactId);
                editButton->setProperty("class", "editButton");
                connect(editButton, &QPushButton::clicked, this, &ContactsWidget::onEditButtonClicked);

                QPushButton* deleteButton = new QPushButton("Usuń");
                deleteButton->setProperty("contactId", contactId);
                deleteButton->setProperty("class", "deleteButton");
                connect(deleteButton, &QPushButton::clicked, this, &ContactsWidget::onDeleteButtonClicked);

                buttonsLayout->addWidget(editButton);
                buttonsLayout->addWidget(deleteButton);

                tableWidget->setCellWidget(row, 6, buttonsWidget);

                tableWidget->setCellWidget(row, 6, buttonsWidget);

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

void ContactsWidget::onEditButtonClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
        int contactId = button->property("contactId").toInt();

        if (ptrEditContact->loadContactData(contactId)) {
            ptrEditContact->setModal(true);
            ptrEditContact->show();
        } else {
            QMessageBox::critical(this, "Błąd", "Nie można załadować danych kontaktu");
        }
    }
}

void ContactsWidget::onDeleteButtonClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
        int contactId = button->property("contactId").toInt();

        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Usuń kontakt");
        msgBox.setText("Jesteś pewny że chcesz usunąć kontakt?");

        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

        msgBox.button(QMessageBox::Yes)->setText("Usuń");
        msgBox.button(QMessageBox::No)->setText("Anuluj");

        msgBox.setDefaultButton(QMessageBox::No);
        msgBox.setEscapeButton(QMessageBox::No);

        msgBox.setLayoutDirection(Qt::RightToLeft);

        msgBox.setProperty("class", "msgBox");

        msgBox.button(QMessageBox::No)->setStyleSheet(R"(
            QPushButton#btnCancel {
                background: transparent;
                color: black;
                border: 1px solid #007BFF;
                text-decoration: none;
                padding-top: 7px;
                padding-bottom: 7px;
            }

            QPushButton#btnCancel:hover {
                background-color: #F5F5F5;
            }
        )");


        int reply = msgBox.exec();

        if (reply == QMessageBox::Yes) {
            Database_Manager dbManager;
            QSqlDatabase db = dbManager.getDatabase();

            if (db.open()) {
                QSqlQuery query(db);
                query.prepare("DELETE FROM contacts WHERE id = :id AND user_id = :user_id");
                query.bindValue(":id", contactId);
                query.bindValue(":user_id", currentUser->getId());

                if (query.exec()) {
                    refreshContactsTable();
                    QMessageBox::information(this, "Sukces", "Kontakt usunięty pomyślnie");
                } else {
                    QMessageBox::critical(this, "Błąd", "Błąd przy usuwaniu kontaktu: " + query.lastError().text());
                }
            } else {
                QMessageBox::critical(this, "Błąd", "Blad bazy danych");
            }
        }
    }
}
