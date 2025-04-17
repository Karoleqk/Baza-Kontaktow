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
    QString firstName = ui->inputFirstName->text();
    QString lastName = ui->inputLastName->text();
    QString phone = ui->inputPhone->text();
    QString email = ui->inputEmail->text();
    QString address = ui->inputAddress->toPlainText();

    qDebug() << firstName << lastName << phone << email << address;

    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();

    QSqlQuery query(db);

    query.prepare("INSERT INTO contacts (firstName, phone, lastName, email, address) "
                  "VALUES (:firstName, :lastName, :phone, :email, :address)");

    query.bindValue(":firstName", firstName);
    query.bindValue(":lastName", lastName);
    query.bindValue(":phone", phone);
    query.bindValue(":email", email);
    query.bindValue(":address", address);

    if (query.exec()) {
        QMessageBox::information(this, "Wiadomosc", "Dodano kontakt", QMessageBox::Yes);
    } else {
        qDebug() << "SQL Error: " << query.lastError().text();
        QMessageBox::critical(this, "Blad", "Wystąpił błąd przy dodawaniu kontaktu", QMessageBox::No);
    }

}

