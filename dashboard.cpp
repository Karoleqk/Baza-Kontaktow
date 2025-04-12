#include "dashboard.h"
#include "ui_dashboard.h"

Dashboard::Dashboard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);

    ptrCreateContact = new CreateContact();
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

