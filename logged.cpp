#include "logged.h"
#include "ui_logged.h"

Logged::Logged(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Logged)
{
    ui->setupUi(this);
    setWindowTitle(currentUser->getName());
    ui->helloMsg->setText("Witaj " + currentUser->getName());
}

Logged::~Logged()
{
    delete ui;
}

void Logged::on_actionWyloguj_triggered()
{
    if(currentUser){
        delete currentUser;
        currentUser = nullptr;
    }

    Baza_Kontaktow *baza = new Baza_Kontaktow;
    this->hide();
    baza->show();
}

