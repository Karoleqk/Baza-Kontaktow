#include "editcontact.h"
#include "ui_editcontact.h"

EditContact::EditContact(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditContact)
    , m_contactId(-1)
{
    ui->setupUi(this);

    this->setFixedSize(400, 500);
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

    if(db.open()){
        QSqlQuery query(db);

        query.prepare(R"(
            SELECT first_name, last_name, phone, email,
                   address_street, address_number, address_city, address_postal_code
            FROM contacts
            WHERE id = :id AND user_id = :user_id
        )");

        query.bindValue(":id", contactId);
        query.bindValue(":user_id", currentUser->getId());

        if (query.exec() && query.next()) {
            ui->inputFirstName_2->setText(query.value(0).toString());
            ui->inputLastName_2->setText(query.value(1).toString());
            ui->inputPhone_2->setText(query.value(2).toString());
            ui->inputEmail_2->setText(query.value(3).toString());
            ui->inputAddressStreet_2->setText(query.value(4).toString());
            ui->inputAddressNumber_2->setText(query.value(5).toString());
            ui->inputAddressCity_2->setText(query.value(6).toString());
            ui->inputAddressPostalCode_2->setText(query.value(7).toString());

            return true;
        } else {
            qDebug() << "Failed to load contact data:" << query.lastError().text();
        }
    }

    return false;
}

void EditContact::on_btnCancel_2_clicked()
{
    this->hide();
}


void EditContact::on_btnSave_clicked()
{
    QString firstName = ui->inputFirstName_2->text();
    QString lastName = ui->inputLastName_2->text();
    QString phone = ui->inputPhone_2->text();
    QString email = ui->inputEmail_2->text();
    QString addressStreet = ui->inputAddressStreet_2->text();
    QString addressNumber = ui->inputAddressNumber_2->text();
    QString addressCity = ui->inputAddressCity_2->text();
    QString addressPostalCode = ui->inputAddressPostalCode_2->text();

    if (firstName.isEmpty() || lastName.isEmpty() || phone.isEmpty() ||
        email.isEmpty() || addressStreet.isEmpty() || addressNumber.isEmpty() ||
        addressCity.isEmpty() || addressPostalCode.isEmpty()) {

        QMessageBox::critical(this, "Błąd", "Wszystkie pola muszą być uzupełnione", QMessageBox::No);
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
                phone = :phone,
                email = :email,
                address_city = :address_city,
                address_street = :address_street,
                address_number = :address_number,
                address_postal_code = :address_postal_code
            WHERE id = :id AND user_id = :user_id
        )");

        query.bindValue(":first_name", firstName);
        query.bindValue(":last_name", lastName);
        query.bindValue(":phone", phone);
        query.bindValue(":email", email);
        query.bindValue(":address_city", addressCity);
        query.bindValue(":address_street", addressStreet);
        query.bindValue(":address_number", addressNumber);
        query.bindValue(":address_postal_code", addressPostalCode);
        query.bindValue(":id", m_contactId);
        query.bindValue(":user_id", currentUser->getId());

        if (query.exec()) {
            emit contactUpdated();
            QMessageBox::information(this, "Sukces", "Kontakt zaktualizowany pomyślnie", QMessageBox::Yes);
            this->hide();
        } else {
            qDebug() << "SQL Error: " << query.lastError().text();
            QMessageBox::critical(this, "Błąd", "Wystąpił błąd przy aktualizacji kontaktu", QMessageBox::No);
        }
    } else {
        QMessageBox::critical(this, "Błąd", "Błąd bazy danych", QMessageBox::No);
    }
}

