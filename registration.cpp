#include "registration.h"
#include "ui_registration.h"

Registration::Registration(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Registration)
{
    ui->setupUi(this);
    this->setFixedSize(width(), height());
    setWindowTitle("Rejestracja");
}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_loginBtn_clicked()
{
    this->hide();
    Baza_Kontaktow *baza = new Baza_Kontaktow();
    baza->show();
}


void Registration::on_registerBtn_clicked()
{
    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();

    QString login = ui->loginInput->text();
    QString password = ui->passwordInput->text();
    QString repeatPassword = ui->repeatPasswordInput->text();

    if(login == "" || password == ""){
        QMessageBox::critical(this, "Blad", "Uzupelnij puste pola!", QMessageBox::Yes);
    } else if(password != repeatPassword){
        QMessageBox::critical(this, "Blad", "Hasla nie sa takie same!", QMessageBox::Cancel);
    } else {
        if(db.open()){
            QSqlQuery query(db);
            QString hashedPassword = hashPassword(password);

            query.prepare("INSERT INTO users (name, password) VALUES (:login, :password)");
            query.bindValue(":login", login);
            query.bindValue(":password", hashedPassword);

            if(query.exec()) QMessageBox::information(this, "Zarejestrowano", "Pomyslnie zarejestrowano", QMessageBox::Yes);
            else QMessageBox::critical(this, "Blad", "Wybrana nazwa jest zajeta!", QMessageBox::No);
        } else {
            QMessageBox::critical(this, "blad", "Blad otwarcia bazy danych", QMessageBox::No);
        }
    }
}

