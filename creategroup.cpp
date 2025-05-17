#include "creategroup.h"
#include "ui_creategroup.h"

creategroup::creategroup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::creategroup)
{
    ui->setupUi(this);
    this->setFixedSize(400, 500);
    setWindowTitle("Utworz grupe");

    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();

    if(db.open()){
        QSqlQuery query(db);
        int userId = currentUser->getId();

        query.prepare("SELECT first_name, last_name, phone FROM contacts WHERE user_id = :currentId");
        query.bindValue(":currentId", userId);

        if(query.exec()){
            while(query.next()){
                QString firstName = query.value(0).toString();
                QString lastName = query.value(1).toString();
                QString phoneNumber = query.value(2).toString();
                QString fullName = firstName + " " + lastName + " " + phoneNumber;

                QListWidgetItem *item = new QListWidgetItem(fullName);
                item->setCheckState(Qt::Unchecked);
                ui->groupList->addItem(item);
            }
        } else {
            qDebug() << "Blad wykonania zapytania" << query.lastError().text();
        }
    } else {
        qDebug() << "Nie mozna otworzyc bazy danych";
    }
}

creategroup::~creategroup()
{
    delete ui;
}


void creategroup::on_closeBtn_clicked()
{
    this->hide();
}


void creategroup::on_addBtn_clicked()
{
    int currId = currentUser->getId();
    QString groupName = ui->groupNameInput->text();

    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();

    QSqlQuery insertQuery(db);

    insertQuery.prepare("INSERT INTO groups (user_id, group_name) VALUES (:currId, :groupName)");
    insertQuery.bindValue(":currId", currId);
    insertQuery.bindValue(":groupName", groupName);

    if(insertQuery.exec()){
        qDebug() << "Poprawno dodano dane";
        emit groupCreated();
    } else {
        qDebug() << "Blad zapytania" << insertQuery.lastError().text();
    }

    this->close();
}
