#include "groupswidget.h"
#include "ui_groupswidget.h"

GroupsWidget::GroupsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GroupsWidget)
{
    ui->setupUi(this);

    reloadGroups();
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

        QSqlQuery query(db);
        query.exec("CREATE TABLE IF NOT EXISTS groups ("
                   "group_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "user_id INTEGER, "
                   "group_name TEXT)");

        query.prepare("SELECT group_name, group_id FROM groups WHERE user_id = :currentId");
        query.bindValue(":currentId", userId);

        if(!query.exec()) qDebug() << "Blad zapytania";

        else {
            int index = 0;
            qDebug() << "Poprawne zapytanie";

            QLayoutItem* child;
            while ((child = ui->groupsContainer->takeAt(0)) != nullptr) {
                if (child->widget()) {
                    delete child->widget();
                }
                delete child;
            }

            while(query.next()){
                qDebug() << "Udalo sie";

                int groupId = query.value(1).toInt();
                QString groupName = query.value(0).toString();

                if(!groupName.isEmpty()) groupName[0] = groupName[0].toUpper();

                QWidget* groupWidget = new QWidget(this);
                QVBoxLayout* vLayout = new QVBoxLayout(groupWidget);

                QLabel* nameLabel = new QLabel(groupName, groupWidget);
                nameLabel->setAlignment(Qt::AlignCenter);
                QFont font;
                font.setWeight(QFont::Bold);
                nameLabel->setFont(font);
                vLayout->addWidget(nameLabel);

                QPushButton* editButton = new QPushButton("Edytuj", groupWidget); 
                editButton->setProperty("groupId", groupId);
                editButton->setProperty("class", "editBtn");

                QPushButton* deleteButton = new QPushButton("Usuń", groupWidget);
                deleteButton->setProperty("groupId", groupId);
                deleteButton->setProperty("class", "deleteBtn");

                QPushButton* showButton = new QPushButton("Wyswietl", groupWidget);
                showButton->setProperty("groupId", groupId);
                showButton->setProperty("class", "showBtn");

                connect(deleteButton, &QPushButton::clicked, this, &GroupsWidget::on_deleteBtn_clicked);
                connect(editButton, &QPushButton::clicked, this, &GroupsWidget::on_editBtn_clicked);
                connect(showButton, &QPushButton::clicked, this, &GroupsWidget::on_showBtn_clicked);

                vLayout->addWidget(editButton);
                vLayout->addWidget(deleteButton);
                vLayout->addWidget(showButton);

                int row = index / 4;
                int col = index % 4;

                ui->groupsContainer->addWidget(groupWidget, row, col);
                groupWidget->setStyleSheet("border: 1px solid gray; border-radius: 10px; padding: 10px;");
                groupWidget->setMinimumSize(150, 250);
                groupWidget->setMaximumSize(200,250);
                index++;
            }
            db.close();
        }
    }
}

void GroupsWidget::on_addGroupBtn_clicked()
{
    grpPtr = new creategroup(nullptr);
    connect(grpPtr, &creategroup::groupCreated, this, &GroupsWidget::reloadGroups);
    grpPtr->show();
}


void GroupsWidget::on_deleteBtn_clicked(){
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    if(button){
        QLayoutItem *child;
        while ((child = ui->contacts_list->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }

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

}



void GroupsWidget::on_showBtn_clicked(){
    qDebug() << "on_showBtn_clicked() called";
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();

    if(button){
        int groupId = button->property("groupId").toInt();
        int contactId;

        if(db.open()){
            QSqlQuery query(db);

            QLayoutItem *child;
            while ((child = ui->contacts_list->takeAt(0)) != nullptr) {
                delete child->widget();
                delete child;
            }

            query.prepare("SELECT contact_id FROM groups_contacts WHERE group_id = :groupId");
            query.bindValue(":groupId", groupId);

            if(query.exec()){
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

                            QString userInfo = QString("Imie: %1 | Nazwisko: %2 | Miasto: %3 | Ulica: %4 | Nr domu: %5\nKod Pocztowy: %6 | Nr tel: %7 | Email: %8")
                                                   .arg(firstName).arg(lastName).arg(city).arg(street).arg(houseNumber).arg(postalCode).arg(phoneNumber).arg(email);

                            QLabel *userLabel = new QLabel(userInfo);
                            ui->contacts_list->addWidget(userLabel);
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
