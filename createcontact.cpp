#include "createcontact.h"
#include "ui_createcontact.h"
#include <QMessageBox>
#include <QSqlError>


CreateContact::CreateContact(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateContact)
{
    ui->setupUi(this);

    this->setFixedSize(600, 500);
    this->setWindowTitle("Dodaj kontakt");
}

CreateContact::~CreateContact()
{
    delete ui;
}

void CreateContact::on_btnCancel_clicked()
{
    this->close();
}

void CreateContact::on_btnCreate_clicked()
{
    QString firstName = ui->inputFirstName->text();
    QString lastName = ui->inputLastName->text();
    QString addressStreet = ui->inputAddressStreet->text();
    QString addressNumber = ui->inputAddressNumber->text();
    QString addressCity = ui->inputAddressCity->text();
    QString addressPostalCode = ui->inputAddressPostalCode->text();
    int userId = currentUser->getId();

    if(
        firstName.isEmpty() || lastName.isEmpty() ||
        addressStreet.isEmpty() || addressNumber.isEmpty() ||
        addressCity.isEmpty() || addressPostalCode.isEmpty()
    ){
        QMessageBox::critical(this, "Blad", "Wszystkie pola muszą być uzupełnione", QMessageBox::No);
        return;
    }

    qDebug() << firstName << lastName;

    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();

    QSqlQuery query(db);

    query.prepare(R"(
        INSERT INTO contacts (user_id, first_name, last_name, address_city, address_street, address_number, address_postal_code)
        VALUES (:user_id, :first_name, :last_name, :address_city, :address_street, :address_number, :address_postal_code)
    )");

    query.bindValue(":user_id", userId);
    query.bindValue(":first_name", firstName);
    query.bindValue(":last_name", lastName);
    query.bindValue(":address_city", addressCity);
    query.bindValue(":address_street", addressStreet);
    query.bindValue(":address_number", addressNumber);
    query.bindValue(":address_postal_code", addressPostalCode);

    if (!query.exec()) {
        QMessageBox::critical(this, "Błąd", "Wystąpił błąd przy dodawaniu kontaktu", QMessageBox::No);
        return;
    }

    qint64 newContactId = query.lastInsertId().toLongLong();

    QSqlQuery phonesQuery(db);
    phonesQuery.prepare("INSERT INTO contacts_phones (contact_id, phone) VALUES (:contactId, :phone)");

    for (int i = 0; i < ui->phonesList->count(); ++i) {
        QWidget* w = ui->phonesList->itemWidget(ui->phonesList->item(i));
        QString phone;
        if (w) {
            if (auto label = w->findChild<QLabel*>()) {
                phone = label->text().trimmed();
            }
        }
        if (!phone.isEmpty()) {
            phonesQuery.bindValue(":contactId", newContactId);
            phonesQuery.bindValue(":phone", phone);
            if (!phonesQuery.exec()) {
                qDebug() << "Failed to insert phone:" << phonesQuery.lastError().text();
            }
        }
    }

    QSqlQuery emailsQuery(db);
    emailsQuery.prepare("INSERT INTO contacts_emails (contact_id, email) VALUES (:contactId, :email)");

    for (int i = 0; i < ui->emailsList->count(); ++i) {
        QWidget* w = ui->emailsList->itemWidget(ui->emailsList->item(i));
        QString email;
        if (w) {
            if (auto label = w->findChild<QLabel*>()) {
                email = label->text().trimmed();
            }
        }
        if (!email.isEmpty()) {
            emailsQuery.bindValue(":contactId", newContactId);
            emailsQuery.bindValue(":email", email);
            if (!emailsQuery.exec()) {
                qDebug() << "Failed to insert email:" << emailsQuery.lastError().text();
            }
        }
    }

    emit contactAdded();
    QMessageBox::information(this, "Wiadomość", "Dodano kontakt", QMessageBox::Yes);
    resetForm();
    this->close();
}


void CreateContact::on_btnAddEmail_clicked()
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

void CreateContact::addEmailItem(const QString &email)
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

void CreateContact::on_btnAddPhone_clicked()
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

void CreateContact::addPhoneItem(const QString &phone)
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

void CreateContact::resetForm()
{
    ui->inputFirstName->clear();
    ui->inputLastName->clear();
    ui->inputAddressStreet->clear();
    ui->inputAddressNumber->clear();
    ui->inputAddressCity->clear();
    ui->inputAddressPostalCode->clear();

    ui->emailsList->clear();
    ui->phonesList->clear();

    ui->inputEmail->clear();
    ui->inputPhone->clear();
}
