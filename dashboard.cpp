#include "dashboard.h"
#include "ui_dashboard.h"

Dashboard::Dashboard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);

    ptrCreateContact = new CreateContact();

    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();

    if(db.open()){
        QSqlQuery query;
        query.prepare("SELECT * FROM contacts");

        if (query.exec()) {
            qDebug() << "Success: " << "wczytano dane";
        } else {
            qDebug() << "SQL Error: " << "blad danych";
        }
    } else {
        qDebug() << "SQL Error: " << "Błąd otwarcia bazy danych";
    }
}

Dashboard::~Dashboard()
{
    delete ui;
    delete ptrCreateContact;
}

void Dashboard::on_btnCreateContact_clicked()
{
    ptrCreateContact->show();
}

