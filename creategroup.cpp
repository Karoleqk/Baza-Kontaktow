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

        query.prepare("SELECT ID, first_name, last_name, phone FROM contacts WHERE user_id = :currentId");
        query.bindValue(":currentId", userId);

        if(query.exec()){
            while(query.next()){
                QString firstName = query.value(1).toString();
                QString lastName = query.value(2).toString();
                QString phoneNumber = query.value(3).toString();
                QString fullName = firstName + " " + lastName + " " + phoneNumber;

                QListWidgetItem *item = new QListWidgetItem(fullName);
                item->setCheckState(Qt::Unchecked);
                item->setData(Qt::UserRole, query.value(0).toInt());
                ui->groupList->addItem(item);
            }
            db.close();
        } else {
            qDebug() << "Blad wykonania zapytania" << query.lastError().text();
        }
        db.close();
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
    int groupId;

    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();

    QString groupName = ui->groupNameInput->text();

    if(groupName == "") QMessageBox::warning(this, "Blad", "Nazwa grupy nie moze byc pusta", QMessageBox::Yes);
    else{
        if(db.open()){
            QSqlQuery checkGroupName(db);

            checkGroupName.prepare("SELECT group_name FROM groups WHERE group_name = :groupName AND user_id = :currId");
            checkGroupName.bindValue(":groupName", groupName);
            checkGroupName.bindValue(":currId", currId);

            if(checkGroupName.exec()){
                if(!checkGroupName.next()){
                    bool isChecked = false;

                    for(int i = 0; i < ui->groupList->count(); i++){
                        QListWidgetItem *item = ui->groupList->item(i);
                        if(item->checkState() == Qt::Checked) isChecked = true;
                    }

                    if(!isChecked) QMessageBox::warning(this, "Blad", "Nie mozesz stworzyc pustej grupy", QMessageBox::Yes);
                    else {
                        QSqlQuery insertQuery(db);

                        insertQuery.prepare("INSERT INTO groups (user_id, group_name) VALUES (:currId, :groupName)");
                        insertQuery.bindValue(":currId", currId);
                        insertQuery.bindValue(":groupName", groupName);

                        if(insertQuery.exec()){

                            QSqlQuery query(db);
                            query.exec("CREATE TABLE IF NOT EXISTS groups_contacts ("
                                       "groupContacts_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                       "group_id INTEGER,"
                                       "contact_id INTEGER)");


                            query.prepare("SELECT group_id FROM groups WHERE user_id = :currId AND group_name = :groupName");
                            query.bindValue(":currId", currId);
                            query.bindValue(":groupName", groupName);

                            if(query.exec() && query.next()) groupId = query.value(0).toInt();

                            for(int i = 0; i < ui->groupList->count(); i++){
                                QListWidgetItem *item = ui->groupList->item(i);
                                if(item->checkState() == Qt::Checked){
                                    int contactId = item->data(Qt::UserRole).toInt();

                                    QSqlQuery insertContact(db);

                                    insertContact.prepare("INSERT INTO groups_contacts (group_id, contact_id) VALUES (:groupId, :contactId)");
                                    insertContact.bindValue(":groupId", groupId);
                                    insertContact.bindValue(":contactId", contactId);

                                    if(!insertContact.exec()) qDebug() << "Blad zapytania";
                                }
                            }

                            emit groupCreated();
                        } else {
                            qDebug() << "Blad zapytania" << insertQuery.lastError().text();
                        }

                        this->close();
                        db.close();
                    }
                } else {
                    QMessageBox::warning(this, "Blad", "Istnieje juz grupa o takiej nazwie", QMessageBox::Yes);
                }
            } else {
                qDebug() << "Blad zapytania";
            }


        } else {
            qDebug() << "Problem z otwarciem bazy danych";
        }
    }

}
