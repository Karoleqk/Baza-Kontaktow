#include "editgroup.h"
#include "ui_editgroup.h"

editGroup::editGroup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::editGroup)
{
    ui->setupUi(this);
    this->setFixedSize(400, 500);
    setWindowTitle("Edytuj grupe");

    connect(ui->inputSearch, &QLineEdit::textChanged, this, &editGroup::refreshContactsList);

    connect(ui->groupList, &QListWidget::itemChanged, this, [this](QListWidgetItem* item){
        int id = item->data(Qt::UserRole).toInt();
        if (item->checkState() == Qt::Checked)
            checkedContactIds.insert(id);
        else
            checkedContactIds.remove(id);
    });
}

bool editGroup::loadGroupData(int groupId){
    currentGroupId = groupId;
    checkedContactIds.clear();

    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();

    if(db.open()){
        QSqlQuery getGroupName(db);
        getGroupName.prepare("SELECT group_name FROM groups WHERE group_id = :groupId");
        getGroupName.bindValue(":groupId", groupId);

        if(getGroupName.exec()){
            if(getGroupName.next()) {
                QString groupName = getGroupName.value(0).toString();
                ui->groupNameInput->setText(groupName);
            }
        } else {
            qDebug() << "Blad zapytania (getGroupName):" << getGroupName.lastError().text();
        }

        QSqlQuery groupContactsQuery(db);
        groupContactsQuery.prepare("SELECT contact_id FROM groups_contacts WHERE group_id = :groupId");
        groupContactsQuery.bindValue(":groupId", groupId);

        if (groupContactsQuery.exec()) {
            while (groupContactsQuery.next()) {
                checkedContactIds.insert(groupContactsQuery.value(0).toInt());
            }
        } else {
            qDebug() << "Blad zapytania (groupContacts):" << groupContactsQuery.lastError().text();
        }

        db.close();

        refreshContactsList();

        return true;
    } else {
        qDebug() << "Nie mozna otworzyc bazy danych";
        return false;
    }
}


editGroup::~editGroup()
{
    delete ui;
}

void editGroup::refreshContactsList()
{
    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();

    ui->groupList->clear();

    if(db.open()){
        QSqlQuery query(db);
        int userId = currentUser->getId();

        QString searchText = ui->inputSearch->text().trimmed();
        bool isSearching = !searchText.isEmpty();

        QString sql = "SELECT ID, first_name, last_name FROM contacts WHERE user_id = :currentId";

        if (isSearching) {
            searchText = "%" + searchText + "%";
            sql += " AND (first_name LIKE :search OR last_name LIKE :search)";
        }

        sql += " ORDER BY first_name, last_name";

        query.prepare(sql);
        query.bindValue(":currentId", userId);

        if (isSearching) {
            query.bindValue(":search", searchText);
        }

        QList<QListWidgetItem*> checkedItems;
        QList<QListWidgetItem*> uncheckedItems;

        if(query.exec()){
            while(query.next()){
                int contactId = query.value(0).toInt();
                QString firstName = query.value(1).toString();
                QString lastName = query.value(2).toString();

                QString fullName = firstName + " " + lastName;

                QListWidgetItem *item = new QListWidgetItem(fullName);

                if(checkedContactIds.contains(contactId)){
                    item->setCheckState(Qt::Checked);
                    checkedItems.append(item);
                } else {
                    item->setCheckState(Qt::Unchecked);
                    uncheckedItems.append(item);
                }

                item->setData(Qt::UserRole, contactId);
            }

            for(QListWidgetItem* item : checkedItems){
                ui->groupList->addItem(item);
            }
            for(QListWidgetItem* item : uncheckedItems){
                ui->groupList->addItem(item);
            }
        } else {
            qDebug() << "Blad wykonania zapytania" << query.lastError().text();
        }

        db.close();
    } else {
        qDebug() << "Nie mozna otworzyc bazy danych";
    }
}

void editGroup::on_saveBtn_clicked()
{
    int currId = currentUser->getId();
    int groupId = this->currentGroupId;
    qDebug() << groupId;

    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();

    QString groupName = ui->groupNameInput->text();

    if(groupName == "") QMessageBox::warning(this, "Blad", "Nazwa grupy nie moze byc pusta", QMessageBox::Yes);
    else{
        if(db.open()){
            QSqlQuery checkGroupName(db);

            checkGroupName.prepare("SELECT group_id FROM groups WHERE group_name = :groupName AND user_id = :currId AND group_id != :groupId");
            checkGroupName.bindValue(":groupName", groupName);
            checkGroupName.bindValue(":currId", currId);
            checkGroupName.bindValue(":groupId", groupId);

            if(checkGroupName.exec()){
                if(!checkGroupName.next()){
                    QSqlQuery updateGroupName(db);

                    updateGroupName.prepare("UPDATE groups SET group_name = :groupName WHERE group_id = :groupId");
                    updateGroupName.bindValue(":groupName", groupName);
                    updateGroupName.bindValue(":groupId", groupId);

                    if(!updateGroupName.exec()) qDebug() << "Blad akutalizacji nazwy grupy";

                    bool isChecked = false;

                    for(int i = 0; i < ui->groupList->count(); i++){
                        QListWidgetItem *item = ui->groupList->item(i);
                        if(item->checkState() == Qt::Checked) isChecked = true;
                    }

                    if(!isChecked) QMessageBox::warning(this, "Blad", "Nie mozesz stworzyc pustej grupy", QMessageBox::Yes);
                    else {
                        QSqlQuery clearContacts(db);

                        clearContacts.prepare("DELETE FROM groups_contacts WHERE group_id = :groupId");
                        clearContacts.bindValue(":groupId", groupId);
                        if(!clearContacts.exec()) qDebug() << "Blad usuwania starych danych";
                        else {
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
                            emit groupEdited();
                        }

                        db.close();
                        this->hide();
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
    this->hide();
}


void editGroup::on_closeBtn_clicked()
{
    this->hide();
}

void editGroup::resetForm()
{
    ui->inputSearch->clear();
}
