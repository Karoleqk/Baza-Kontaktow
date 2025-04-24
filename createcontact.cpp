#include "createcontact.h"
#include "ui_createcontact.h"
#include <QMessageBox>
#include <QSqlError>


CreateContact::CreateContact(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateContact)
{
    ui->setupUi(this);

    this->setFixedSize(400, 500);
    this->setWindowTitle("Dodaj kontakt");

}

CreateContact::~CreateContact()
{
    delete ui;
}

void CreateContact::on_btnCancel_clicked()
{
    this->hide();
}

void CreateContact::on_btnCreate_clicked()
{
    QString firstName = ui->inputFirstName->text();
    QString lastName = ui->inputLastName->text();
    QString phone = ui->inputPhone->text();
    QString email = ui->inputEmail->text();
    QString addressStreet = ui->inputAddressStreet->text();
    QString addressNumber = ui->inputAddressNumber->text();
    QString addressCity = ui->inputAddressCity->text();
    QString addressPostalCode = ui->inputAddressPostalCode->text();
    int userId = currentUser->getId();

    if(
        firstName.isEmpty() || lastName.isEmpty() || phone.isEmpty() ||
        email.isEmpty() || addressStreet.isEmpty() || addressNumber.isEmpty() ||
        addressCity.isEmpty() || addressPostalCode.isEmpty()
    ){
        QMessageBox::critical(this, "Blad", "Wszystkie pola muszą być uzupełnione", QMessageBox::No);
        return;
    }

    qDebug() << firstName << lastName << phone << email;

    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();

    QSqlQuery query(db);

    query.prepare(R"(
        INSERT INTO contacts (user_id, first_name, last_name, phone, email, address_city, address_street, address_number, address_postal_code)
        VALUES (:user_id, :first_name, :last_name, :phone, :email, :address_city, :address_street, :address_number, :address_postal_code)
    )");

    query.bindValue(":user_id", userId);
    query.bindValue(":first_name", firstName);
    query.bindValue(":last_name", lastName);
    query.bindValue(":phone", phone);
    query.bindValue(":email", email);
    query.bindValue(":address_city", addressCity);
    query.bindValue(":address_street", addressStreet);
    query.bindValue(":address_number", addressNumber);
    query.bindValue(":address_postal_code", addressPostalCode);

    if (query.exec()) {
        emit contactAdded();
        QMessageBox::information(this, "Wiadomosc", "Dodano kontakt", QMessageBox::Yes);
        this->hide();
    } else {
        qDebug() << "SQL Error: " << query.lastError().text();
        QMessageBox::critical(this, "Blad", "Wystąpił błąd przy dodawaniu kontaktu", QMessageBox::No);
    }

}

