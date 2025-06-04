#include "baza_kontaktow.h"
#include "./ui_baza_kontaktow.h"


Baza_Kontaktow::Baza_Kontaktow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Baza_Kontaktow)
{
    ui->setupUi(this);
    this->setFixedSize(width(), height());
    setWindowTitle("Logowanie");
}

Baza_Kontaktow::~Baza_Kontaktow()
{
    delete ui;
}

void Baza_Kontaktow::on_registerBtn_clicked()
{
    this->hide();
    Registration *reg = new Registration();
    reg->show();
}

void Baza_Kontaktow::on_loginBtn_clicked()
{
    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();

    QString login = ui->loginInput->text();
    QString password = ui->passwordInput->text();
    QString hashedPassword = hashPassword(password);

    if(db.open()){ // jesli baza sie otworzyla, to stworz zapytanie
        QSqlQuery query(db);

        if(currentUser){
            delete currentUser;
            currentUser = nullptr;
        }

        // Przypisanie do zmiennej globalnej danych aktualnie zalogowanego uzytkownika
        currentUser = new User;
        currentUser->setName(login);
        currentUser->setPassword(hashedPassword);

        query.prepare("SELECT id FROM users WHERE name = :login AND password = :password");
        query.bindValue(":login", login);
        query.bindValue(":password", hashedPassword);

        if(query.exec()){
            if(query.next()){
                int currId = query.value("id").toInt();
                currentUser->setId(currId);
            }
        }

        query.prepare("SELECT * FROM users WHERE name = :login AND password = :password");
        query.bindValue(":login", login);
        query.bindValue(":password", hashedPassword);

        if(query.exec()){
            if(query.next()){ // Sprawdza czy znalazlo pasujacy login i haslo
                QMessageBox::information(this, "Logged in", "Zalogowano pomyslnie", QMessageBox::Yes);
                this->hide();
                Dashboard *dashboard = new Dashboard(nullptr);
                dashboard->setWindowFlags(Qt::Window);
                dashboard->show();
            } else {
                QMessageBox::critical(this, "Blad", "Bledny login lub haslo", QMessageBox::No);
            }
        } else {
            QMessageBox::critical(this, "Blad", "Blad bazy danych");
        }
    }
}

