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

        query.prepare("SELECT group_name FROM groups WHERE user_id = :currentId");
        query.bindValue(":currentId", userId);

        if(!query.exec()) qDebug() << "Blad zapytania";

        else {
            int index = 0;
            qDebug() << "Poprawne zapytanie";
            while(query.next()){
                qDebug() << "Udalo sie";
                QString groupName = query.value(0).toString();

                QWidget* groupWidget = new QWidget(this);
                QVBoxLayout* vLayout = new QVBoxLayout(groupWidget);

                QLabel* nameLabel = new QLabel(groupName, groupWidget);
                nameLabel->setAlignment(Qt::AlignCenter);
                vLayout->addWidget(nameLabel);

                QPushButton* editButton = new QPushButton("Edytuj", groupWidget);
                QPushButton* deleteButton = new QPushButton("Usuń", groupWidget);
                vLayout->addWidget(editButton);
                vLayout->addWidget(deleteButton);

                int row = index / 2;
                int col = index % 2;

                ui->groupsContainer->addWidget(groupWidget, row, col);
                groupWidget->setStyleSheet("border: 1px solid gray; border-radius: 10px; padding: 10px;");
                groupWidget->setMaximumSize(250, 150);
                index++;
            }
        }
    }
}

void GroupsWidget::on_addGroupBtn_clicked()
{
    creategroup *grp = new creategroup();
    connect(grp, &creategroup::groupCreated, this, &GroupsWidget::reloadGroups);
    grp->show();
}

