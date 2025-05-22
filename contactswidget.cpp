#include "contactswidget.h"
#include "ui_contactswidget.h"
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>
#include <QMessageBox>
#include <QProgressDialog>
#include <QApplication>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QStringConverter>
#endif

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
    ptrCreateContact->resetForm();
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

    if (db.open()) {
        QString countSql = R"(
            SELECT COUNT(*) FROM contacts
            WHERE user_id = :user_id
        )";

        if (isSearching) {
            searchText = "%" + searchText + "%";
            countSql += R"(
                AND id IN (
                    SELECT contacts.id FROM contacts
                    LEFT JOIN contacts_emails ON contacts.id = contacts_emails.contact_id
                    LEFT JOIN contacts_phones ON contacts.id = contacts_phones.contact_id
                    WHERE
                        first_name LIKE :search OR
                        last_name LIKE :search OR
                        contacts_emails.email LIKE :search OR
                        contacts_phones.phone LIKE :search OR
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
            SELECT id, first_name, last_name,
                   address_city || ', ' || address_street || ' ' || address_number || ', ' || address_postal_code AS address
            FROM contacts
            WHERE user_id = :user_id
        )";

        if (isSearching) {
            sql += R"(
                AND id IN (
                    SELECT contacts.id FROM contacts
                    LEFT JOIN contacts_emails ON contacts.id = contacts_emails.contact_id
                    LEFT JOIN contacts_phones ON contacts.id = contacts_phones.contact_id
                    WHERE
                        first_name LIKE :search OR
                        last_name LIKE :search OR
                        contacts_emails.email LIKE :search OR
                        contacts_phones.phone LIKE :search OR
                        address_city LIKE :search OR
                        address_street LIKE :search OR
                        address_postal_code LIKE :search
                )
            )";
        }

        query.prepare(sql);
        query.bindValue(":user_id", userId);

        if (isSearching) {
            query.bindValue(":search", searchText);
        }

        if (query.exec()) {
            QStringList headers;
            headers << "ID" << "Imię" << "Nazwisko" << "Telefon" << "Email" << "Adres" << "Akcje";
            tableWidget->setColumnCount(headers.size());
            tableWidget->setHorizontalHeaderLabels(headers);
            tableWidget->verticalHeader()->setVisible(false);

            int row = 0;
            while (query.next()) {
                tableWidget->insertRow(row);

                int contactId = query.value(0).toInt();

                QStringList phones;
                QSqlQuery phoneQuery(db);
                phoneQuery.prepare("SELECT phone FROM contacts_phones WHERE contact_id = :id");
                phoneQuery.bindValue(":id", contactId);
                if (phoneQuery.exec()) {
                    while (phoneQuery.next()) {
                        phones << phoneQuery.value(0).toString();
                    }
                }

                QStringList emails;
                QSqlQuery emailQuery(db);
                emailQuery.prepare("SELECT email FROM contacts_emails WHERE contact_id = :id");
                emailQuery.bindValue(":id", contactId);
                if (emailQuery.exec()) {
                    while (emailQuery.next()) {
                        emails << emailQuery.value(0).toString();
                    }
                }

                QTableWidgetItem* idItem = new QTableWidgetItem(QString::number(contactId));
                idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
                tableWidget->setItem(row, 0, idItem);

                tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
                tableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
                tableWidget->setItem(row, 3, new QTableWidgetItem(phones.join(", ")));
                tableWidget->setItem(row, 4, new QTableWidgetItem(emails.join(", ")));
                tableWidget->setItem(row, 5, new QTableWidgetItem(query.value(3).toString()));

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
            ptrEditContact->resetForm();
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
        msgBox.setIcon(QMessageBox::Question);

        msgBox.setStyleSheet(R"(
            QMessageBox {
                background-color: white;
                border-radius: 8px;
            }
            QPushButton {
                min-width: 80px;
                padding: 5px;
            }
        )");

        int reply = msgBox.exec();

        if (reply == QMessageBox::Yes) {
            Database_Manager dbManager;
            QSqlDatabase db = dbManager.getDatabase();

            if (db.open()) {
                QSqlQuery query(db);

                db.transaction();

                query.prepare("DELETE FROM contacts_phones WHERE contact_id = :contactId");
                query.bindValue(":contactId", contactId);
                if (!query.exec()) {
                    db.rollback();
                    QMessageBox::critical(this, "Błąd", "Błąd przy usuwaniu telefonów: " + query.lastError().text());
                    return;
                }

                query.prepare("DELETE FROM contacts_emails WHERE contact_id = :contactId");
                query.bindValue(":contactId", contactId);
                if (!query.exec()) {
                    db.rollback();
                    QMessageBox::critical(this, "Błąd", "Błąd przy usuwaniu emaili: " + query.lastError().text());
                    return;
                }

                query.prepare("DELETE FROM contacts WHERE id = :id AND user_id = :user_id");
                query.bindValue(":id", contactId);
                query.bindValue(":user_id", currentUser->getId());

                if (query.exec()) {
                    db.commit();
                    refreshContactsTable();
                    QMessageBox msgBox2(this);
                    msgBox2.setWindowTitle("Usunieto");
                    msgBox2.setText("Kontakt usunięty pomyślnie");
                    msgBox2.setStandardButtons(QMessageBox::Yes);

                    msgBox2.setStyleSheet(R"(
                    QMessageBox{
                        background-color: white;
                        border-radius: 8px;
                    }
                    )");

                    msgBox2.exec();
                } else {
                    db.rollback();
                    QMessageBox::critical(this, "Błąd", "Błąd przy usuwaniu kontaktu: " + query.lastError().text());
                }
            } else {
                QMessageBox::critical(this, "Błąd", "Blad bazy danych");
            }
        }
    }
}

void ContactsWidget::on_btnImport_clicked()
{
    QMessageBox formatBox(this);
    formatBox.setWindowTitle("Wybierz format importu");
    formatBox.setText("Wybierz format pliku do importu:");
    formatBox.setIcon(QMessageBox::Question);
    formatBox.setStyleSheet(R"(
            QMessageBox {
                background-color: white;
                border-radius: 8px;
            }
            QPushButton {
                min-width: 80px;
                padding: 5px;
            }
        )");

    QPushButton* csvButton = formatBox.addButton("CSV", QMessageBox::ActionRole);
    QPushButton* jsonButton = formatBox.addButton("JSON", QMessageBox::ActionRole);
    QPushButton* cancelButton = formatBox.addButton("Anuluj", QMessageBox::RejectRole);

    formatBox.setDefaultButton(csvButton);
    formatBox.setEscapeButton(cancelButton);

    formatBox.exec();

    if (formatBox.clickedButton() == cancelButton) {
        return;
    }

    QString filter;
    bool isCSV = (formatBox.clickedButton() == csvButton);

    if (isCSV) {
        filter = "CSV Files (*.csv)";
    } else {
        filter = "JSON Files (*.json)";
    }

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Importuj kontakty",
                                                    QString(),
                                                    filter);

    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox msgBox;
        msgBox.setStyleSheet(R"(
            QMessageBox {
                background-color: white;
                border-radius: 8px;
                color: black;
            }
            QLabel {
                color: black;
            }
            QPushButton {
                min-width: 80px;
                padding: 5px;
            }
        )");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Błąd");
        msgBox.setText("Nie można otworzyć pliku do odczytu");
        msgBox.exec();

        return;
    }

    int importedCount = 0;
    int errorCount = 0;

    if (isCSV) {
        importedCount = importFromCSV(file, errorCount);
    } else {
        importedCount = importFromJSON(file, errorCount);
    }

    file.close();

    QString message = QString("Import zakończony!\nZaimportowano: %1 kontaktów")
                          .arg(importedCount);
    if (errorCount > 0) {
        message += QString("\nBłędy: %1").arg(errorCount);
    }

    QMessageBox msgBox;
    msgBox.setStyleSheet(R"(
            QMessageBox {
                background-color: white;
                border-radius: 8px;
                color: black;
            }
            QLabel {
                color: black;
            }
            QPushButton {
                min-width: 80px;
                padding: 5px;
            }
        )");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle("Import zakończony");
    msgBox.setText(message);
    msgBox.exec();

    refreshContactsTable();
}

void ContactsWidget::on_btnExport_clicked()
{
    QMessageBox formatBox(this);
    formatBox.setWindowTitle("Wybierz format eksportu");
    formatBox.setText("Wybierz format pliku do eksportu:");
    formatBox.setIcon(QMessageBox::Question);
    formatBox.setStyleSheet(R"(
            QMessageBox {
                background-color: white;
                border-radius: 8px;
            }
            QPushButton {
                min-width: 80px;
                padding: 5px;
            }
        )");

    QPushButton* csvButton = formatBox.addButton("CSV", QMessageBox::ActionRole);
    QPushButton* jsonButton = formatBox.addButton("JSON", QMessageBox::ActionRole);
    QPushButton* cancelButton = formatBox.addButton("Anuluj", QMessageBox::RejectRole);

    formatBox.setDefaultButton(csvButton);
    formatBox.setEscapeButton(cancelButton);

    formatBox.exec();

    if (formatBox.clickedButton() == cancelButton) {
        return;
    }

    QString filter;
    QString defaultName;
    bool isCSV = (formatBox.clickedButton() == csvButton);

    if (isCSV) {
        filter = "CSV Files (*.csv)";
        defaultName = "kontakty.csv";
    } else {
        filter = "JSON Files (*.json)";
        defaultName = "kontakty.json";
    }

    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Eksportuj kontakty",
                                                    defaultName,
                                                    filter);

    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox msgBox;
        msgBox.setStyleSheet(R"(
            QMessageBox {
                background-color: white;
                border-radius: 8px;
                color: black;
            }
            QLabel {
                color: black;
            }
            QPushButton {
                min-width: 80px;
                padding: 5px;
            }
        )");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Błąd");
        msgBox.setText("Nie można utworzyć pliku do zapisu");
        msgBox.exec();

        return;
    }

    int exportedCount = 0;

    if (isCSV) {
        exportedCount = exportToCSV(file);
    } else {
        exportedCount = exportToJSON(file);
    }

    file.close();

    if (exportedCount >= 0) {
        QMessageBox msgBox;
        msgBox.setStyleSheet(R"(
            QMessageBox {
                background-color: white;
                border-radius: 8px;
                color: black;
            }
            QLabel {
                color: black;
            }
            QPushButton {
                min-width: 80px;
                padding: 5px;
            }
        )");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("Eksport zakończony");
        msgBox.setText(QString("Wyeksportowano %1 kontaktów do pliku:\n%2").arg(exportedCount).arg(fileName));
        msgBox.exec();

    } else {
        QMessageBox msgBox;
        msgBox.setStyleSheet(R"(
            QMessageBox {
                background-color: white;
                border-radius: 8px;
                color: black;
            }
            QLabel {
                color: black;
            }
            QPushButton {
                min-width: 80px;
                padding: 5px;
            }
        )");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Błąd");
        msgBox.setText("Wystąpił błąd podczas eksportu");
        msgBox.exec();
    }
}

int ContactsWidget::exportToCSV(QFile& file)
{
    QTextStream out(&file);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    out.setCodec("UTF-8");
#else
    out.setEncoding(QStringConverter::Utf8);
#endif

    out << "Imię,Nazwisko,Telefony,Emaile,Miasto,Ulica,Numer,Kod pocztowy\n";

    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();

    if (!db.open()) {
        return -1;
    }

    int userId = currentUser->getId();
    int exportedCount = 0;

    QSqlQuery query(db);
    query.prepare(R"(
        SELECT id, first_name, last_name, address_city, address_street,
               address_number, address_postal_code
        FROM contacts
        WHERE user_id = :user_id
        ORDER BY last_name, first_name
    )");
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        return -1;
    }

    while (query.next()) {
        int contactId = query.value(0).toInt();
        QString firstName = query.value(1).toString();
        QString lastName = query.value(2).toString();
        QString city = query.value(3).toString();
        QString street = query.value(4).toString();
        QString number = query.value(5).toString();
        QString postalCode = query.value(6).toString();

        QStringList phones;
        QSqlQuery phoneQuery(db);
        phoneQuery.prepare("SELECT phone FROM contacts_phones WHERE contact_id = :id");
        phoneQuery.bindValue(":id", contactId);
        if (phoneQuery.exec()) {
            while (phoneQuery.next()) {
                phones << phoneQuery.value(0).toString();
            }
        }

        QStringList emails;
        QSqlQuery emailQuery(db);
        emailQuery.prepare("SELECT email FROM contacts_emails WHERE contact_id = :id");
        emailQuery.bindValue(":id", contactId);
        if (emailQuery.exec()) {
            while (emailQuery.next()) {
                emails << emailQuery.value(0).toString();
            }
        }

        auto escapeCSV = [](const QString& field) -> QString {
            if (field.contains(',') || field.contains('"') || field.contains('\n')) {
                QString escaped = field;
                escaped.replace("\"", "\"\"");
                return "\"" + escaped + "\"";
            }
            return field;
        };

        out << escapeCSV(firstName) << ","
            << escapeCSV(lastName) << ","
            << escapeCSV(phones.join("; ")) << ","
            << escapeCSV(emails.join("; ")) << ","
            << escapeCSV(city) << ","
            << escapeCSV(street) << ","
            << escapeCSV(number) << ","
            << escapeCSV(postalCode) << "\n";

        exportedCount++;
    }

    return exportedCount;
}

int ContactsWidget::exportToJSON(QFile& file)
{
    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();

    if (!db.open()) {
        return -1;
    }

    int userId = currentUser->getId();
    int exportedCount = 0;

    QJsonArray contactsArray;

    QSqlQuery query(db);
    query.prepare(R"(
        SELECT id, first_name, last_name, address_city, address_street,
               address_number, address_postal_code
        FROM contacts
        WHERE user_id = :user_id
        ORDER BY last_name, first_name
    )");
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        return -1;
    }

    while (query.next()) {
        int contactId = query.value(0).toInt();

        QJsonObject contact;
        contact["firstName"] = query.value(1).toString();
        contact["lastName"] = query.value(2).toString();
        contact["address"] = QJsonObject{
            {"city", query.value(3).toString()},
            {"street", query.value(4).toString()},
            {"number", query.value(5).toString()},
            {"postalCode", query.value(6).toString()}
        };

        QJsonArray phonesArray;
        QSqlQuery phoneQuery(db);
        phoneQuery.prepare("SELECT phone FROM contacts_phones WHERE contact_id = :id");
        phoneQuery.bindValue(":id", contactId);
        if (phoneQuery.exec()) {
            while (phoneQuery.next()) {
                phonesArray.append(phoneQuery.value(0).toString());
            }
        }
        contact["phones"] = phonesArray;

        QJsonArray emailsArray;
        QSqlQuery emailQuery(db);
        emailQuery.prepare("SELECT email FROM contacts_emails WHERE contact_id = :id");
        emailQuery.bindValue(":id", contactId);
        if (emailQuery.exec()) {
            while (emailQuery.next()) {
                emailsArray.append(emailQuery.value(0).toString());
            }
        }
        contact["emails"] = emailsArray;

        contactsArray.append(contact);
        exportedCount++;
    }

    QJsonObject root;
    root["contacts"] = contactsArray;
    root["exportDate"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    root["version"] = "1.0";

    QJsonDocument doc(root);
    file.write(doc.toJson());

    return exportedCount;
}

int ContactsWidget::importFromCSV(QFile& file, int& errorCount)
{
    QTextStream in(&file);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    in.setCodec("UTF-8");
#else
    in.setEncoding(QStringConverter::Utf8);
#endif

    QString line = in.readLine();
    if (line.isEmpty()) {
        errorCount++;
        return 0;
    }

    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();

    if (!db.open()) {
        errorCount++;
        return 0;
    }

    int userId = currentUser->getId();
    int importedCount = 0;

    db.transaction();

    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList fields = parseCSVLine(line);
        if (fields.size() < 8) {
            errorCount++;
            continue;
        }

        QString firstName = fields[0].trimmed();
        QString lastName = fields[1].trimmed();
        QString phonesStr = fields[2].trimmed();
        QString emailsStr = fields[3].trimmed();
        QString city = fields[4].trimmed();
        QString street = fields[5].trimmed();
        QString number = fields[6].trimmed();
        QString postalCode = fields[7].trimmed();

        if (firstName.isEmpty() && lastName.isEmpty()) {
            errorCount++;
            continue;
        }

        QSqlQuery contactQuery(db);
        contactQuery.prepare(R"(
            INSERT INTO contacts (user_id, first_name, last_name, address_city,
                                address_street, address_number, address_postal_code)
            VALUES (:user_id, :first_name, :last_name, :city, :street, :number, :postal_code)
        )");
        contactQuery.bindValue(":user_id", userId);
        contactQuery.bindValue(":first_name", firstName);
        contactQuery.bindValue(":last_name", lastName);
        contactQuery.bindValue(":city", city);
        contactQuery.bindValue(":street", street);
        contactQuery.bindValue(":number", number);
        contactQuery.bindValue(":postal_code", postalCode);

        if (!contactQuery.exec()) {
            errorCount++;
            continue;
        }

        int contactId = contactQuery.lastInsertId().toInt();

#if QT_VERSION < QT_VERSION_CHECK(5, 14, 0)
        QStringList phones = phonesStr.split(";", QString::SkipEmptyParts);
#else
        QStringList phones = phonesStr.split(";", Qt::SkipEmptyParts);
#endif
        for (const QString& phone : phones) {
            QString cleanPhone = phone.trimmed();
            if (!cleanPhone.isEmpty()) {
                QSqlQuery phoneQuery(db);
                phoneQuery.prepare("INSERT INTO contacts_phones (contact_id, phone) VALUES (:contact_id, :phone)");
                phoneQuery.bindValue(":contact_id", contactId);
                phoneQuery.bindValue(":phone", cleanPhone);
                phoneQuery.exec();
            }
        }

#if QT_VERSION < QT_VERSION_CHECK(5, 14, 0)
        QStringList emails = emailsStr.split(";", QString::SkipEmptyParts);
#else
        QStringList emails = emailsStr.split(";", Qt::SkipEmptyParts);
#endif
        for (const QString& email : emails) {
            QString cleanEmail = email.trimmed();
            if (!cleanEmail.isEmpty()) {
                QSqlQuery emailQuery(db);
                emailQuery.prepare("INSERT INTO contacts_emails (contact_id, email) VALUES (:contact_id, :email)");
                emailQuery.bindValue(":contact_id", contactId);
                emailQuery.bindValue(":email", cleanEmail);
                emailQuery.exec();
            }
        }

        importedCount++;
    }

    db.commit();
    return importedCount;
}

int ContactsWidget::importFromJSON(QFile& file, int& errorCount)
{
    QByteArray data = file.readAll();
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        errorCount++;
        return 0;
    }

    QJsonObject root = doc.object();
    QJsonArray contactsArray = root["contacts"].toArray();

    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();

    if (!db.open()) {
        errorCount++;
        return 0;
    }

    int userId = currentUser->getId();
    int importedCount = 0;

    db.transaction();

    for (const QJsonValue& contactValue : contactsArray) {
        QJsonObject contact = contactValue.toObject();

        QString firstName = contact["firstName"].toString().trimmed();
        QString lastName = contact["lastName"].toString().trimmed();

        if (firstName.isEmpty() && lastName.isEmpty()) {
            errorCount++;
            continue;
        }

        QJsonObject address = contact["address"].toObject();
        QString city = address["city"].toString().trimmed();
        QString street = address["street"].toString().trimmed();
        QString number = address["number"].toString().trimmed();
        QString postalCode = address["postalCode"].toString().trimmed();

        QSqlQuery contactQuery(db);
        contactQuery.prepare(R"(
            INSERT INTO contacts (user_id, first_name, last_name, address_city,
                                address_street, address_number, address_postal_code)
            VALUES (:user_id, :first_name, :last_name, :city, :street, :number, :postal_code)
        )");
        contactQuery.bindValue(":user_id", userId);
        contactQuery.bindValue(":first_name", firstName);
        contactQuery.bindValue(":last_name", lastName);
        contactQuery.bindValue(":city", city);
        contactQuery.bindValue(":street", street);
        contactQuery.bindValue(":number", number);
        contactQuery.bindValue(":postal_code", postalCode);

        if (!contactQuery.exec()) {
            errorCount++;
            continue;
        }

        int contactId = contactQuery.lastInsertId().toInt();

        QJsonArray phonesArray = contact["phones"].toArray();
        for (const QJsonValue& phoneValue : phonesArray) {
            QString phone = phoneValue.toString().trimmed();
            if (!phone.isEmpty()) {
                QSqlQuery phoneQuery(db);
                phoneQuery.prepare("INSERT INTO contacts_phones (contact_id, phone) VALUES (:contact_id, :phone)");
                phoneQuery.bindValue(":contact_id", contactId);
                phoneQuery.bindValue(":phone", phone);
                phoneQuery.exec();
            }
        }

        QJsonArray emailsArray = contact["emails"].toArray();
        for (const QJsonValue& emailValue : emailsArray) {
            QString email = emailValue.toString().trimmed();
            if (!email.isEmpty()) {
                QSqlQuery emailQuery(db);
                emailQuery.prepare("INSERT INTO contacts_emails (contact_id, email) VALUES (:contact_id, :email)");
                emailQuery.bindValue(":contact_id", contactId);
                emailQuery.bindValue(":email", email);
                emailQuery.exec();
            }
        }

        importedCount++;
    }

    db.commit();
    return importedCount;
}

QStringList ContactsWidget::parseCSVLine(const QString& line)
{
    QStringList result;
    QString current;
    bool inQuotes = false;
    bool nextIsEscaped = false;

    for (int i = 0; i < line.length(); ++i) {
        QChar c = line[i];

        if (nextIsEscaped) {
            current += c;
            nextIsEscaped = false;
        } else if (c == '"') {
            if (inQuotes && i + 1 < line.length() && line[i + 1] == '"') {
                current += '"';
                ++i;
            } else {
                inQuotes = !inQuotes;
            }
        } else if (c == ',' && !inQuotes) {
            result << current;
            current.clear();
        } else {
            current += c;
        }
    }

    result << current;
    return result;
}
