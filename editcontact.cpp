#include "editcontact.h"
#include "ui_editcontact.h"

EditContact::EditContact(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditContact)
    , m_contactId(-1)
{
    ui->setupUi(this);

    this->setFixedSize(600, 500);
    this->setWindowTitle("Edytuj kontakt");
}

EditContact::~EditContact()
{
    delete ui;
}

bool EditContact::loadContactData(int contactId)
{
    m_contactId = contactId;

    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();

    if (!db.open()) {
        qDebug() << "Failed to open DB:" << db.lastError().text();
        return false;
    }

    ui->emailsList->clear();
    ui->phonesList->clear();

    {
        QSqlQuery query(db);
        query.prepare(R"(
            SELECT first_name, last_name,
                   address_street, address_number, address_city, address_postal_code
            FROM contacts
            WHERE id = :id AND user_id = :user_id
        )");
        query.bindValue(":id", contactId);
        query.bindValue(":user_id", currentUser->getId());

        if (query.exec() && query.next()) {
            ui->inputFirstName_2->setText(query.value(0).toString());
            ui->inputLastName_2->setText(query.value(1).toString());
            ui->inputAddressStreet_2->setText(query.value(2).toString());
            ui->inputAddressNumber_2->setText(query.value(3).toString());
            ui->inputAddressCity_2->setText(query.value(4).toString());
            ui->inputAddressPostalCode_2->setText(query.value(5).toString());
        } else {
            qDebug() << "Failed to load contact main data:" << query.lastError().text();
            return false;
        }
    }

    {
        QSqlQuery query(db);
        query.prepare(R"(
            SELECT email FROM contacts_emails
            WHERE contact_id = :contact_id
        )");
        query.bindValue(":contact_id", contactId);

        if (query.exec()) {
            while (query.next()) {
                QString email = query.value(0).toString();

                QListWidgetItem *listItem = new QListWidgetItem();
                listItem->setSizeHint(QSize(0, 30));
                ui->emailsList->addItem(listItem);

                QWidget *itemWidget = new QWidget();
                QLabel *emailLabel = new QLabel(email);
                QPushButton* removeButton = new QPushButton();
                removeButton->setIcon(QIcon::fromTheme("list-remove"));
                removeButton->setProperty("class", "deleteButton");
                removeButton->setFixedSize(24, 24);

                QHBoxLayout *layout = new QHBoxLayout(itemWidget);
                layout->addWidget(emailLabel);
                layout->addStretch();
                layout->addWidget(removeButton);
                layout->setContentsMargins(5, 0, 5, 0);

                itemWidget->setLayout(layout);
                ui->emailsList->setItemWidget(listItem, itemWidget);

                connect(removeButton, &QPushButton::clicked, this, [=]() {
                    delete ui->emailsList->takeItem(ui->emailsList->row(listItem));
                });
            }
        } else {
            qDebug() << "Failed to load emails:" << query.lastError().text();
        }
    }

    {
        QSqlQuery query(db);
        query.prepare(R"(
            SELECT phone FROM contacts_phones
            WHERE contact_id = :contact_id
        )");
        query.bindValue(":contact_id", contactId);

        if (query.exec()) {
            while (query.next()) {
                QString phone = query.value(0).toString();

                QListWidgetItem *listItem = new QListWidgetItem();
                listItem->setSizeHint(QSize(0, 30));
                ui->phonesList->addItem(listItem);

                QWidget *itemWidget = new QWidget();
                QLabel *phoneLabel = new QLabel(phone);
                QPushButton* removeButton = new QPushButton();
                removeButton->setIcon(QIcon::fromTheme("list-remove"));
                removeButton->setProperty("class", "deleteButton");
                removeButton->setFixedSize(24, 24);

                QHBoxLayout *layout = new QHBoxLayout(itemWidget);
                layout->addWidget(phoneLabel);
                layout->addStretch();
                layout->addWidget(removeButton);
                layout->setContentsMargins(5, 0, 5, 0);

                itemWidget->setLayout(layout);
                ui->phonesList->setItemWidget(listItem, itemWidget);

                connect(removeButton, &QPushButton::clicked, this, [=]() {
                    delete ui->phonesList->takeItem(ui->phonesList->row(listItem));
                });
            }
        } else {
            qDebug() << "Failed to load phones:" << query.lastError().text();
        }
    }

    return true;
}

void EditContact::on_btnCancel_2_clicked()
{
    this->hide();
}

void EditContact::on_btnSave_clicked()
{
    QString firstName = ui->inputFirstName_2->text();
    QString lastName = ui->inputLastName_2->text();
    QString addressStreet = ui->inputAddressStreet_2->text();
    QString addressNumber = ui->inputAddressNumber_2->text();
    QString addressCity = ui->inputAddressCity_2->text();
    QString addressPostalCode = ui->inputAddressPostalCode_2->text();

    if (firstName.isEmpty() || lastName.isEmpty() ||
        addressStreet.isEmpty() || addressNumber.isEmpty() ||
        addressCity.isEmpty() || addressPostalCode.isEmpty()) {

        QMessageBox::critical(this, "Błąd", "Wszystkie pola muszą być uzupełnione", QMessageBox::No);
        return;
    }

    if (ui->phonesList->count() == 0 || ui->emailsList->count() == 0) {
        QMessageBox::critical(this, "Błąd", "Musisz dodać co najmniej jeden numer telefonu i jeden email", QMessageBox::No);
        return;
    }

    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();

    if (db.open()) {
        QSqlQuery query(db);

        query.prepare(R"(
            UPDATE contacts
            SET first_name = :first_name,
                last_name = :last_name,
                address_city = :address_city,
                address_street = :address_street,
                address_number = :address_number,
                address_postal_code = :address_postal_code
            WHERE id = :id AND user_id = :user_id
        )");

        query.bindValue(":first_name", firstName);
        query.bindValue(":last_name", lastName);
        query.bindValue(":address_city", addressCity);
        query.bindValue(":address_street", addressStreet);
        query.bindValue(":address_number", addressNumber);
        query.bindValue(":address_postal_code", addressPostalCode);
        query.bindValue(":id", m_contactId);
        query.bindValue(":user_id", currentUser->getId());

        if (!query.exec()) {
            qDebug() << "SQL Error: " << query.lastError().text();
            QMessageBox::critical(this, "Błąd", "Wystąpił błąd przy aktualizacji kontaktu", QMessageBox::No);
            return;
        }

        query.prepare("DELETE FROM contacts_phones WHERE contact_id = :contactId");
        query.bindValue(":contactId", m_contactId);
        if (!query.exec()) {
            qDebug() << "Failed to clear phones:" << query.lastError().text();
            QMessageBox::critical(this, "Błąd", "Błąd przy aktualizacji telefonów", QMessageBox::No);
            return;
        }

        query.prepare("INSERT INTO contacts_phones (contact_id, phone) VALUES (:contactId, :phone)");
        for (int i = 0; i < ui->phonesList->count(); ++i) {
            QWidget* w = ui->phonesList->itemWidget(ui->phonesList->item(i));
            QString phone;
            if (w) {
                if (auto label = w->findChild<QLabel*>()) {
                    phone = label->text().trimmed();
                }
            }
            if (!phone.isEmpty()) {
                query.bindValue(":contactId", m_contactId);
                query.bindValue(":phone", phone);
                if (!query.exec()) {
                    qDebug() << "Failed to insert phone:" << query.lastError().text();
                }
            }
        }


        query.prepare("DELETE FROM contacts_emails WHERE contact_id = :contactId");
        query.bindValue(":contactId", m_contactId);
        if (!query.exec()) {
            qDebug() << "Failed to clear emails:" << query.lastError().text();
            QMessageBox::critical(this, "Błąd", "Błąd przy aktualizacji emaili", QMessageBox::No);
            return;
        }

        query.prepare("INSERT INTO contacts_emails (contact_id, email) VALUES (:contactId, :email)");
        for (int i = 0; i < ui->emailsList->count(); ++i) {
            QWidget* w = ui->emailsList->itemWidget(ui->emailsList->item(i));
            QString email;
            if (w) {
                if (auto label = w->findChild<QLabel*>()) {
                    email = label->text().trimmed();
                }
            }
            if (!email.isEmpty()) {
                query.bindValue(":contactId", m_contactId);
                query.bindValue(":email", email);
                if (!query.exec()) {
                    qDebug() << "Failed to insert email:" << query.lastError().text();
                }
            }
        }


        emit contactUpdated();
        QMessageBox::information(this, "Sukces", "Kontakt zaktualizowany pomyślnie", QMessageBox::Yes);
        this->hide();
    } else {
        QMessageBox::critical(this, "Błąd", "Błąd bazy danych", QMessageBox::No);
    }
}

void EditContact::on_btnAddEmail_clicked()
{
    QString email = ui->inputEmail->text().trimmed();
    if (email.isEmpty())
        return;

    for (int i = 0; i < ui->emailsList->count(); ++i) {
        QWidget *w = ui->emailsList->itemWidget(ui->emailsList->item(i));
        if (auto label = w->findChild<QLabel*>()) {
            if (label->text() == email) {
                ui->inputEmail->clear();
                return;
            }
        }
    }

    addEmailItem(email);
    ui->inputEmail->clear();
}

void EditContact::addEmailItem(const QString &email)
{
    QListWidgetItem *listItem = new QListWidgetItem();
    listItem->setSizeHint(QSize(0, 30));
    ui->emailsList->addItem(listItem);

    QWidget *itemWidget = new QWidget();

    QLabel *emailLabel = new QLabel(email);
    QPushButton* removeButton = new QPushButton(this);
    removeButton->setIcon(QIcon::fromTheme("list-remove"));
    removeButton->setProperty("class", "deleteButton");
    removeButton->setFixedSize(24, 24);

    QHBoxLayout *layout = new QHBoxLayout(itemWidget);
    layout->addWidget(emailLabel);
    layout->addStretch();
    layout->addWidget(removeButton);
    layout->setContentsMargins(5, 0, 5, 0);

    itemWidget->setLayout(layout);
    ui->emailsList->setItemWidget(listItem, itemWidget);

    connect(removeButton, &QPushButton::clicked, this, [=]() {
        delete ui->emailsList->takeItem(ui->emailsList->row(listItem));
    });
}

void EditContact::on_btnAddPhone_clicked()
{
    QString phone = ui->inputPhone->text().trimmed();
    if (phone.isEmpty())
        return;

    for (int i = 0; i < ui->phonesList->count(); ++i) {
        QWidget *w = ui->phonesList->itemWidget(ui->phonesList->item(i));
        if (auto label = w->findChild<QLabel*>()) {
            if (label->text() == phone) {
                ui->inputPhone->clear();
                return;
            }
        }
    }

    addPhoneItem(phone);
    ui->inputPhone->clear();
}

void EditContact::addPhoneItem(const QString &phone)
{
    QListWidgetItem *listItem = new QListWidgetItem();
    listItem->setSizeHint(QSize(0, 30));
    ui->phonesList->addItem(listItem);

    QWidget *itemWidget = new QWidget();

    QLabel *phoneLabel = new QLabel(phone);
    QPushButton* removeButton = new QPushButton(this);
    removeButton->setIcon(QIcon::fromTheme("list-remove"));
    removeButton->setProperty("class", "deleteButton");
    removeButton->setFixedSize(24, 24);

    QHBoxLayout *layout = new QHBoxLayout(itemWidget);
    layout->addWidget(phoneLabel);
    layout->addStretch();
    layout->addWidget(removeButton);
    layout->setContentsMargins(5, 0, 5, 0);

    itemWidget->setLayout(layout);
    ui->phonesList->setItemWidget(listItem, itemWidget);

    connect(removeButton, &QPushButton::clicked, this, [=]() {
        delete ui->phonesList->takeItem(ui->phonesList->row(listItem));
    });
}

