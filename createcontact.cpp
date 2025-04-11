#include "createcontact.h"
#include "ui_createcontact.h"

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
