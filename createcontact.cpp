#include "createcontact.h"
#include "ui_createcontact.h"
#include <QMessageBox>
#include <QSqlError>


CreateContact::CreateContact(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateContact)
{
    ui->setupUi(this);
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
    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();

    if(db.open()){
        QString firstName = ui->inputFirstName->text();
        QString lastName = ui->inputLastName->text();
        QString phone = ui->inputPhone->text();
        QString email = ui->inputEmail->text();
        QString address = ui->inputAddress->toPlainText();

        QSqlQuery query;
        query.prepare("INSERT INTO Contacts (ID, firstName, lastName, address, phone, email) "
                      "VALUES (NULL, :firstName, :lastName, :phone, :email, :address)");

        query.bindValue(":firstName", firstName);
        query.bindValue(":lastName", lastName);
        query.bindValue(":address", address);
        query.bindValue(":phone", phone);
        query.bindValue(":email", email);

        if (query.exec()) {
            QMessageBox::information(this, "Wiadomosc", "Dodano kontakt", QMessageBox::Yes);
        } else {
            qDebug() << "SQL Error: " << query.lastError().text();
            QMessageBox::critical(this, "Blad", "Wystąpił błąd przy dodawaniu kontaktu", QMessageBox::No);
        }
    } else {
        QMessageBox::critical(this, "Blad", "Błąd otwarcia bazy danych", QMessageBox::No);
    }
}

