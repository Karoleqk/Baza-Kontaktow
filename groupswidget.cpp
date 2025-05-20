#include "groupswidget.h"
#include "ui_groupswidget.h"

GroupsWidget::GroupsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GroupsWidget)
{
    ui->setupUi(this);

    editGrpPtr = new editGroup(nullptr);
    grpPtr = new creategroup(nullptr);

    connect(grpPtr, &creategroup::groupCreated, this, &GroupsWidget::reloadGroups);
    connect(editGrpPtr, &editGroup::groupEdited, this, &GroupsWidget::reloadGroups);

    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();

    if(!db.open()){
        qDebug() << "Error: Unable to open database..";
    }
    else{
        qDebug() << "Database open successfully..";
        int userId = currentUser->getId();

        QSqlQuery query(db);
        query.exec("CREATE TABLE IF NOT EXISTS groups ("
                   "group_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "user_id INTEGER, "
                   "group_name TEXT)");

        query.prepare("SELECT group_name, group_id FROM groups WHERE user_id = :currentId");
        query.bindValue(":currentId", userId);

        if(!query.exec()) qDebug() << "Blad zapytania";

        else {
            QStringList headers, headers2;
            headers << "ID" << "Nazwa grupy" << "Akcje";
            headers2 << "ID" << "Imie" << "Nazwisko" << "Numer telefonu" << "Email" << "Adres";

            ui->groupsTable->setColumnCount(headers.size());
            ui->groupsTable->setHorizontalHeaderLabels(headers);
            ui->groupsContactsTable->setColumnCount(headers2.size());
            ui->groupsContactsTable->setHorizontalHeaderLabels(headers2);

            ui->groupsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->groupsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->groupsTable->verticalHeader()->setVisible(false);
            ui->groupsContactsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->groupsContactsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->groupsContactsTable->verticalHeader()->setVisible(false);

            reloadGroups();
        }
    }

}

GroupsWidget::~GroupsWidget()
{
    delete ui;
}

void GroupsWidget::reloadGroups(){
    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();

    if(!db.open()){
        qDebug() << "Error: Unable to open database..";
    }
    else{
        qDebug() << "Database open successfully..";
        int userId = currentUser->getId();

        QSqlQuery countGroups(db);

        countGroups.prepare("SELECT COUNT(*) FROM groups WHERE user_id = :userId");
        countGroups.bindValue(":userId", userId);

        int totalGroups = 0;
        if(countGroups.exec() && countGroups.next()){
            totalGroups = countGroups.value(0).toInt();
            ui->labelTotal->setText(QString::number(totalGroups));
        } else {
            ui->labelTotal->setText("0");
        }


        QSqlQuery query(db);

        query.prepare("SELECT group_name, group_id FROM groups WHERE user_id = :currentId");
        query.bindValue(":currentId", userId);

        if(!query.exec()) qDebug() << "Blad zapytania";

        else {
            qDebug() << "Poprawne zapytanie";

            ui->groupsTable->setRowCount(0);
            int row = 0;

            while(query.next()){
                qDebug() << "Udalo sie";

                QString groupName = query.value(0).toString();
                int groupId = query.value(1).toInt();

                if(!groupName.isEmpty()) groupName[0] = groupName[0].toUpper();


                // Create table

                ui->groupsTable->insertRow(row);

                QTableWidgetItem *idItem = new QTableWidgetItem(QString::number(groupId));
                idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);

                ui->groupsTable->setItem(row, 0, idItem);
                ui->groupsTable->setItem(row, 1, new QTableWidgetItem(groupName));


                // create buttons and add properties to them, and combine them into one widget

                QWidget *cellWidget = new QWidget();
                QPushButton *showButton = new QPushButton("Wyswietl");
                QPushButton *deleteButton = new QPushButton("Usun");
                QPushButton *editButton = new QPushButton("Edytuj");

                showButton->setProperty("groupId", groupId);
                showButton->setProperty("class", "showBtn");

                deleteButton->setProperty("groupId", groupId);
                deleteButton->setProperty("class", "deleteBtn");

                editButton->setProperty("groupId", groupId);
                editButton->setProperty("class", "editBtn");

                // Buttons connections

                connect(showButton, &QPushButton::clicked, this, &GroupsWidget::on_showBtn_clicked);
                connect(deleteButton, &QPushButton::clicked, this, &GroupsWidget::on_deleteBtn_clicked);
                connect(editButton, &QPushButton::clicked, this, &GroupsWidget::on_editBtn_clicked);


                // Buttons styling
                showButton->setStyleSheet("QPushButton {padding: 2px 0; margin: 0; min-width: 1px};");
                deleteButton->setStyleSheet("QPushButton {padding: 2px 0; margin: 0; min-width: 1px;}");
                editButton->setStyleSheet("QPushButton {padding: 2px 0; margin: 0; min-width: 1px;}");


                // Combine table cell with widget containing our buttons

                QHBoxLayout *layout = new QHBoxLayout(cellWidget);
                layout->addWidget(showButton);
                layout->addWidget(deleteButton);
                layout->addWidget(editButton);

                layout->setContentsMargins(2,2,2,2);
                layout->setSpacing(5);


                ui->groupsTable->setCellWidget(row, 2, cellWidget);

                row++;
            }
            db.close();
        }
    }
}

void GroupsWidget::on_addGroupBtn_clicked()
{
    grpPtr->loadData();
    grpPtr->show();
}


void GroupsWidget::on_deleteBtn_clicked(){
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    if(button){
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Usuń Grupę");
        msgBox.setText("Jesteś pewny, że chcesz usunąć grupę?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.button(QMessageBox::Yes)->setText("Usuń");
        msgBox.button(QMessageBox::No)->setText("Anuluj");

        msgBox.setDefaultButton(QMessageBox::No);
        msgBox.setEscapeButton(QMessageBox::No);
        msgBox.setIcon(QMessageBox::Question);

        msgBox.setStyleSheet(R"(
        QMessageBox {
            background-color: white;
            border-radius: 8px;
        }
        QPushButton {
            min-width: 80px;
            padding: 5px;
        }
    )");

        int reply = msgBox.exec();

        if(reply == QMessageBox::Yes){
            qDebug() << "Usunieto";

            int groupId = button->property("groupId").toInt();

            Database_Manager dbManager;
            QSqlDatabase db = dbManager.getDatabase();

            if(db.open()){
                QSqlQuery deleteGroup(db);
                QSqlQuery deleteContacts(db);

                deleteGroup.prepare("DELETE FROM groups WHERE group_id = :groupId");
                deleteGroup.bindValue(":groupId", groupId);

                deleteContacts.prepare("DELETE FROM groups_contacts WHERE group_id = :groupId");
                deleteContacts.bindValue(":groupId", groupId);

                if(deleteGroup.exec() && deleteContacts.exec()){
                    QMessageBox msgBox2(this);
                    msgBox2.setWindowTitle("Usunieto");
                    msgBox2.setText("Pomyslnie usunieto grupe");
                    msgBox2.setStandardButtons(QMessageBox::Yes);

                    msgBox2.setStyleSheet(R"(
                    QMessageBox{
                        background-color: white;
                        border-radius: 8px;
                    }
                    )");

                    msgBox2.exec();
                    ui->groupsContactsTable->setRowCount(0);
                    reloadGroups();
                }
            } else {
                qDebug() << "Problem z otwarciem bazy danych";
            }
            db.close();
        }

    }
}


void GroupsWidget::on_editBtn_clicked(){
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    if(button){
        int groupId = button->property("groupId").toInt();

        if(editGrpPtr->loadGroupData(groupId)){
            editGrpPtr->show();
        } else {
            QMessageBox::critical(this, "Blad", "Nie mozna zaladowac grupy", QMessageBox::No);
        }
    }
}



void GroupsWidget::on_showBtn_clicked(){
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();

    if(button){
        int groupId = button->property("groupId").toInt();
        int contactId;

        if(db.open()){
            QSqlQuery query(db);

            query.prepare("SELECT contact_id FROM groups_contacts WHERE group_id = :groupId");
            query.bindValue(":groupId", groupId);

            if(query.exec()){

                ui->groupsContactsTable->setRowCount(0);
                int row = 0;
                while(query.next()){
                    contactId = query.value(0).toInt();

                    QSqlQuery getUserData(db);

                    getUserData.prepare("SELECT * FROM contacts WHERE contacts.ID = :contactId");
                    getUserData.bindValue(":contactId", contactId);

                    if(getUserData.exec()){
                        if(getUserData.next()){
                            qDebug() << "Contact ID: " << contactId;
                            QString firstName = getUserData.value(2).toString();
                            QString lastName = getUserData.value(3).toString();
                            QString city = getUserData.value(4).toString();
                            QString street = getUserData.value(5).toString();
                            QString houseNumber = getUserData.value(6).toString();
                            QString postalCode = getUserData.value(7).toString();
                            QString phoneNumber = getUserData.value(8).toString();
                            QString email = getUserData.value(9).toString();

                            QString fullAddress = city + " ul. " + street + " " + houseNumber + ", " + postalCode;

                            ui->groupsContactsTable->insertRow(row);

                            QTableWidgetItem *idItem = new QTableWidgetItem(QString::number(contactId));
                            idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);

                            ui->groupsContactsTable->setItem(row, 0, idItem);
                            ui->groupsContactsTable->setItem(row, 1, new QTableWidgetItem(firstName));
                            ui->groupsContactsTable->setItem(row, 2, new QTableWidgetItem(lastName));
                            ui->groupsContactsTable->setItem(row, 3, new QTableWidgetItem(phoneNumber));
                            ui->groupsContactsTable->setItem(row, 4, new QTableWidgetItem(email));
                            ui->groupsContactsTable->setItem(row, 5, new QTableWidgetItem(fullAddress));

                            row++;
                        }
                    } else {
                        qDebug() << "Blad zapytania";
                    }
                }
            } else {
                qDebug() << "Blad zapytania";
            }
        } else {
            qDebug() << "Blad otwarcia bazy danych";
        }


    }
}
