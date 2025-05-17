#include "dashboard.h"
#include "ui_dashboard.h"

Dashboard::Dashboard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);

    this->resize(1024, 640);

    contactsWidget = new ContactsWidget(this);
    groupsWidget = new GroupsWidget(this);

    ui->stackedWidget->addWidget(contactsWidget);
    ui->stackedWidget->addWidget(groupsWidget);

    ui->stackedWidget->setCurrentWidget(contactsWidget);

    connect(ui->btnGroups, &QPushButton::clicked, this, &Dashboard::showGroupsPage);
    connect(ui->btnContacts, &QPushButton::clicked, this, &Dashboard::showContactsPage);

    ui->btnContacts->setStyleSheet("font-weight: bold;");
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::on_btnLogout_clicked()
{
    if(currentUser){
        delete currentUser;
        currentUser = nullptr;
    }

    Baza_Kontaktow *baza = new Baza_Kontaktow;
    this->hide();
    baza->show();
}

void Dashboard::showGroupsPage()
{
    ui->stackedWidget->setCurrentWidget(groupsWidget);

    ui->btnGroups->setStyleSheet("font-weight: bold;");
    ui->btnContacts->setStyleSheet("font-weight: normal;");
}

void Dashboard::showContactsPage()
{
    ui->stackedWidget->setCurrentWidget(contactsWidget);

    ui->btnGroups->setStyleSheet("font-weight: normal;");
    ui->btnContacts->setStyleSheet("font-weight: bold;");
}
