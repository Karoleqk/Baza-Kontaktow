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
