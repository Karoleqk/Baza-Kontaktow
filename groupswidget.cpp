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
            headers2 << "ID" << "Imię" << "Nazwisko" << "Telefon" << "Email" << "Adres";

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

                ui->groupsTable->insertRow(row);

                QTableWidgetItem *idItem = new QTableWidgetItem(QString::number(groupId));
                idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);

                ui->groupsTable->setItem(row, 0, idItem);
                ui->groupsTable->setItem(row, 1, new QTableWidgetItem(groupName));

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

                connect(showButton, &QPushButton::clicked, this, &GroupsWidget::on_showBtn_clicked);
                connect(editButton, &QPushButton::clicked, this, &GroupsWidget::on_editBtn_clicked);
                connect(deleteButton, &QPushButton::clicked, this, &GroupsWidget::on_deleteBtn_clicked);

                showButton->setStyleSheet("QPushButton {padding: 2px 0; margin: 0; min-width: 1px};");
                deleteButton->setStyleSheet("QPushButton {padding: 2px 0; margin: 0; min-width: 1px;}");
                editButton->setStyleSheet("QPushButton {padding: 2px 0; margin: 0; min-width: 1px;}");

                QHBoxLayout *layout = new QHBoxLayout(cellWidget);
                layout->addWidget(showButton);
                layout->addWidget(editButton);
                layout->addWidget(deleteButton);

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
    grpPtr->resetForm();
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
            editGrpPtr->resetForm();
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

                    QStringList phones;
                    QSqlQuery phoneQuery(db);
                    phoneQuery.prepare("SELECT phone FROM contacts_phones WHERE contact_id = :id");
                    phoneQuery.bindValue(":id", contactId);
                    if (phoneQuery.exec()) {
                        while (phoneQuery.next()) {
                            phones << phoneQuery.value(0).toString();
                        }
                    }

                    QStringList emails;
                    QSqlQuery emailQuery(db);
                    emailQuery.prepare("SELECT email FROM contacts_emails WHERE contact_id = :id");
                    emailQuery.bindValue(":id", contactId);
                    if (emailQuery.exec()) {
                        while (emailQuery.next()) {
                            emails << emailQuery.value(0).toString();
                        }
                    }

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

                            QString fullAddress = city + " ul. " + street + " " + houseNumber + ", " + postalCode;

                            ui->groupsContactsTable->insertRow(row);

                            QTableWidgetItem *idItem = new QTableWidgetItem(QString::number(contactId));
                            idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);

                            ui->groupsContactsTable->setItem(row, 0, idItem);
                            ui->groupsContactsTable->setItem(row, 1, new QTableWidgetItem(firstName));
                            ui->groupsContactsTable->setItem(row, 2, new QTableWidgetItem(lastName));
                            ui->groupsContactsTable->setItem(row, 3, new QTableWidgetItem(phones.join(", ")));
                            ui->groupsContactsTable->setItem(row, 4, new QTableWidgetItem(emails.join(", ")));
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

void GroupsWidget::on_btnExport_clicked()
{
    QMessageBox formatBox(this);
    formatBox.setWindowTitle("Wybierz format eksportu");
    formatBox.setText("Wybierz format pliku do eksportu:");
    formatBox.setIcon(QMessageBox::Question);
    formatBox.setStyleSheet(R"(
        QMessageBox {
            background-color: white;
            border-radius: 8px;
            color: black;
        }
        QLabel { color: black; }
        QPushButton { min-width: 80px; padding: 5px; }
    )");

    QPushButton* csvButton = formatBox.addButton("CSV", QMessageBox::ActionRole);
    QPushButton* jsonButton = formatBox.addButton("JSON", QMessageBox::ActionRole);
    QPushButton* cancelButton = formatBox.addButton("Anuluj", QMessageBox::RejectRole);
    formatBox.setDefaultButton(csvButton);
    formatBox.setEscapeButton(cancelButton);
    formatBox.exec();

    if (formatBox.clickedButton() == cancelButton)
        return;

    bool isCSV = (formatBox.clickedButton() == csvButton);
    QString filter = isCSV ? "CSV Files (*.csv)" : "JSON Files (*.json)";
    QString defaultName = isCSV ? "grupy.csv" : "grupy.json";

    QString fileName = QFileDialog::getSaveFileName(
        this, "Eksportuj grupy", defaultName, filter);
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Błąd",
                              "Nie można utworzyć pliku do zapisu");
        return;
    }

    int exportedCount = isCSV
                            ? exportToCSV(file)
                            : exportToJSON(file);
    file.close();

    if (exportedCount >= 0) {
        QMessageBox msgBox(this);
        msgBox.setStyleSheet(R"(
            QMessageBox {
                background-color: white;
                border-radius: 8px;
                color: black;
            }
            QLabel { color: black; }
            QPushButton { min-width: 80px; padding: 5px; }
        )");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("Eksport zakończony");
        msgBox.setText(
            QString("Wyeksportowano %1 rekordów do pliku:\n%2")
                .arg(exportedCount).arg(fileName));
        msgBox.exec();
    } else {
        QMessageBox msgBox(this);
        msgBox.setStyleSheet(R"(
            QMessageBox {
                background-color: white;
                border-radius: 8px;
                color: black;
            }
            QLabel { color: black; }
            QPushButton { min-width: 80px; padding: 5px; }
        )");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Błąd");
        msgBox.setText("Wystąpił błąd podczas eksportu");
        msgBox.exec();
    }
}

void GroupsWidget::on_btnImport_clicked()
{
    QMessageBox formatBox(this);
    formatBox.setWindowTitle("Wybierz format importu");
    formatBox.setText("Wybierz format pliku do importu:");
    formatBox.setIcon(QMessageBox::Question);
    formatBox.setStyleSheet(R"(
        QMessageBox {
            background-color: white;
            border-radius: 8px;
            color: black;
        }
        QLabel { color: black; }
        QPushButton { min-width: 80px; padding: 5px; }
    )");

    QPushButton* csvButton    = formatBox.addButton("CSV",  QMessageBox::ActionRole);
    QPushButton* jsonButton   = formatBox.addButton("JSON", QMessageBox::ActionRole);
    QPushButton* cancelButton = formatBox.addButton("Anuluj", QMessageBox::RejectRole);
    formatBox.setDefaultButton(csvButton);
    formatBox.setEscapeButton(cancelButton);
    formatBox.exec();

    if (formatBox.clickedButton() == cancelButton)
        return;

    bool isCSV = (formatBox.clickedButton() == csvButton);
    QString filter = isCSV
                         ? "CSV Files (*.csv)"
                         : "JSON Files (*.json)";

    QString fileName = QFileDialog::getOpenFileName(
        this, "Importuj grupy", QString(), filter);
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Błąd",
                              "Nie można otworzyć pliku do odczytu");
        return;
    }

    int errorCount = 0;
    int importedCount = isCSV
                            ? importGroupsFromCSV(file, errorCount)
                            : importGroupsFromJSON(file, errorCount);
    file.close();

    QMessageBox msgBox(this);
    msgBox.setStyleSheet(R"(
        QMessageBox {
            background-color: white;
            border-radius: 8px;
            color: black;
        }
        QLabel { color: black; }
        QPushButton { min-width: 80px; padding: 5px; }
    )");

    if (importedCount >= 0) {
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("Import zakończony");
        QString text = QString("Zaimportowano %1 wpisów").arg(importedCount);
        if (errorCount > 0)
            text += QString("\nBłędy: %1").arg(errorCount);
        msgBox.setText(text);
    } else {
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Błąd");
        msgBox.setText("Wystąpił błąd podczas importu");
    }
    msgBox.exec();

    reloadGroups();
}

int GroupsWidget::exportToCSV(QFile& file)
{
    QTextStream out(&file);
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
    out.setCodec("UTF-8");
#else
    out.setEncoding(QStringConverter::Utf8);
#endif

    out << "Grupa,Imię,Nazwisko,Telefony,Emaile,Miasto,Ulica,Numer,Kod pocztowy\n";

    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();
    if (!db.open()) return -1;

    int userId = currentUser->getId();
    QSqlQuery grpQ(db);
    grpQ.prepare("SELECT group_id, group_name FROM groups WHERE user_id=:uid");
    grpQ.bindValue(":uid", userId);
    if (!grpQ.exec()) return -1;

    int count = 0;
    while (grpQ.next()) {
        int gid = grpQ.value(0).toInt();
        QString gname = grpQ.value(1).toString();

        QSqlQuery cQ(db);
        cQ.prepare(R"(
            SELECT c.id, c.first_name, c.last_name
            FROM contacts c
            JOIN groups_contacts gc ON c.id=gc.contact_id
            WHERE gc.group_id=:gid
        )");
        cQ.bindValue(":gid", gid);
        if (!cQ.exec()) continue;

        while (cQ.next()) {
            int cid = cQ.value(0).toInt();
            QString fn = cQ.value(1).toString();
            QString ln = cQ.value(2).toString();

            QStringList phones;
            QSqlQuery pQ(db);
            pQ.prepare("SELECT phone FROM contacts_phones WHERE contact_id=:cid");
            pQ.bindValue(":cid", cid);
            if (pQ.exec())
                while (pQ.next()) phones << pQ.value(0).toString();

            QStringList emails;
            QSqlQuery eQ(db);
            eQ.prepare("SELECT email FROM contacts_emails WHERE contact_id=:cid");
            eQ.bindValue(":cid", cid);
            if (eQ.exec())
                while (eQ.next()) emails << eQ.value(0).toString();

            auto esc = [](const QString& f)->QString {
                if (f.contains(',')||f.contains('"')||f.contains('\n')) {
                    QString tmp = f; tmp.replace("\"","\"\"");
                    return "\"" + tmp + "\"";
                }
                return f;
            };

            out << esc(gname) << "," << esc(fn) << "," << esc(ln) << ","
                << esc(phones.join("; ")) << "," << esc(emails.join("; "))
                << "\n";
            ++count;
        }
    }
    return count;
}

int GroupsWidget::exportToJSON(QFile& file)
{
    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();
    if (!db.open()) return -1;

    int userId = currentUser->getId();
    QJsonArray groupsArr;
    QSqlQuery grpQ(db);
    grpQ.prepare("SELECT group_id, group_name FROM groups WHERE user_id=:uid");
    grpQ.bindValue(":uid", userId);
    if (!grpQ.exec()) return -1;

    int count = 0;
    while (grpQ.next()) {
        int gid = grpQ.value(0).toInt();
        QString gname = grpQ.value(1).toString();

        QJsonObject grpObj;
        grpObj["name"] = gname;
        QJsonArray contactsArr;

        QSqlQuery cQ(db);
        cQ.prepare(R"(
            SELECT c.id, c.first_name, c.last_name
            FROM contacts c
            JOIN groups_contacts gc ON c.id=gc.contact_id
            WHERE gc.group_id=:gid
        )");
        cQ.bindValue(":gid", gid);
        if (!cQ.exec()) continue;

        while (cQ.next()) {
            int cid = cQ.value(0).toInt();
            QJsonObject cObj;
            cObj["firstName"] = cQ.value(1).toString();
            cObj["lastName"]  = cQ.value(2).toString();

            QJsonArray phones;
            QSqlQuery pQ(db);
            pQ.prepare("SELECT phone FROM contacts_phones WHERE contact_id=:cid");
            pQ.bindValue(":cid", cid);
            if (pQ.exec())
                while (pQ.next()) phones.append(pQ.value(0).toString());

            QJsonArray emails;
            QSqlQuery eQ(db);
            eQ.prepare("SELECT email FROM contacts_emails WHERE contact_id=:cid");
            eQ.bindValue(":cid", cid);
            if (eQ.exec())
                while (eQ.next()) emails.append(eQ.value(0).toString());

            cObj["phones"] = phones;
            cObj["emails"] = emails;
            contactsArr.append(cObj);
            ++count;
        }
        grpObj["contacts"] = contactsArr;
        groupsArr.append(grpObj);
    }

    QJsonObject root;
    root["groups"]     = groupsArr;
    root["exportDate"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    root["version"]    = "1.0";

    QJsonDocument doc(root);
    file.write(doc.toJson());
    return count;
}

QStringList GroupsWidget::parseCSVLine(const QString& line)
{
    QStringList result;
    QString current;
    bool inQuotes = false;
    bool nextIsEscaped = false;

    for (int i = 0; i < line.length(); ++i) {
        QChar c = line[i];
        if (nextIsEscaped) {
            current += c;
            nextIsEscaped = false;
        } else if (c == '"') {
            if (inQuotes && i + 1 < line.length() && line[i + 1] == '"') {
                current += '"';
                ++i;
            } else {
                inQuotes = !inQuotes;
            }
        } else if (c == ',' && !inQuotes) {
            result << current;
            current.clear();
        } else {
            current += c;
        }
    }
    result << current;
    return result;
}

int GroupsWidget::importGroupsFromCSV(QFile& file, int& errorCount)
{
    QTextStream in(&file);
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
    in.setCodec("UTF-8");
#else
    in.setEncoding(QStringConverter::Utf8);
#endif

    if (in.readLine().trimmed().isEmpty()) {
        errorCount++;
        return 0;
    }

    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();
    if (!db.open()) {
        errorCount++;
        return -1;
    }

    int userId = currentUser->getId();
    int count = 0;
    db.transaction();

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = parseCSVLine(line);
        if (parts.size() < 3) { errorCount++; continue; }

        QString grpName   = parts[0].trimmed();
        QString firstName = parts[1].trimmed();
        QString lastName  = parts[2].trimmed();
        if (grpName.isEmpty() || (firstName.isEmpty() && lastName.isEmpty())) {
            errorCount++;
            continue;
        }

        QSqlQuery gQ(db);
        gQ.prepare("SELECT group_id FROM groups WHERE user_id=:uid AND group_name=:gname");
        gQ.bindValue(":uid", userId);
        gQ.bindValue(":gname", grpName);
        int groupId;
        if (gQ.exec() && gQ.next()) {
            groupId = gQ.value(0).toInt();
        } else {
            QSqlQuery igQ(db);
            igQ.prepare("INSERT INTO groups(user_id,group_name) VALUES(:uid,:gname)");
            igQ.bindValue(":uid", userId);
            igQ.bindValue(":gname", grpName);
            if (!igQ.exec()) { errorCount++; continue; }
            groupId = igQ.lastInsertId().toInt();
        }

        QSqlQuery cQ(db);
        cQ.prepare(R"(
            SELECT id FROM contacts
            WHERE user_id=:uid AND first_name=:fn AND last_name=:ln
        )");
        cQ.bindValue(":uid", userId);
        cQ.bindValue(":fn", firstName);
        cQ.bindValue(":ln", lastName);

        if (cQ.exec() && cQ.next()) {
            int contactId = cQ.value(0).toInt();
            QSqlQuery linkQ(db);
            linkQ.prepare(R"(
                INSERT OR IGNORE INTO groups_contacts(group_id,contact_id)
                VALUES(:gid,:cid)
            )");
            linkQ.bindValue(":gid", groupId);
            linkQ.bindValue(":cid", contactId);
            if (linkQ.exec())
                ++count;
            else
                errorCount++;
        } else {
            errorCount++;
        }
    }

    db.commit();
    return count;
}

int GroupsWidget::importGroupsFromJSON(QFile& file, int& errorCount)
{
    QByteArray data = file.readAll();
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    if (err.error != QJsonParseError::NoError) {
        errorCount++;
        return 0;
    }

    QJsonObject root      = doc.object();
    QJsonArray groupsArr  = root["groups"].toArray();

    Database_Manager dbManager;
    QSqlDatabase db = dbManager.getDatabase();
    if (!db.open()) return -1;

    int userId = currentUser->getId();
    int count = 0;
    db.transaction();

    for (auto gVal : groupsArr) {
        QJsonObject gObj = gVal.toObject();
        QString grpName = gObj["name"].toString().trimmed();
        if (grpName.isEmpty()) { errorCount++; continue; }

        QSqlQuery gQ(db);
        gQ.prepare("SELECT group_id FROM groups WHERE user_id=:uid AND group_name=:gname");
        gQ.bindValue(":uid", userId);
        gQ.bindValue(":gname", grpName);

        int groupId;
        if (gQ.exec() && gQ.next()) {
            groupId = gQ.value(0).toInt();
        } else {
            QSqlQuery igQ(db);
            igQ.prepare("INSERT INTO groups(user_id,group_name) VALUES(:uid,:gname)");
            igQ.bindValue(":uid", userId);
            igQ.bindValue(":gname", grpName);
            if (!igQ.exec()) { errorCount++; continue; }
            groupId = igQ.lastInsertId().toInt();
        }

        QJsonArray contactsArr = gObj["contacts"].toArray();
        for (auto cVal : contactsArr) {
            QJsonObject cObj = cVal.toObject();
            QString fn = cObj["firstName"].toString().trimmed();
            QString ln = cObj["lastName"].toString().trimmed();
            if (fn.isEmpty() && ln.isEmpty()) { errorCount++; continue; }

            QSqlQuery cQ(db);
            cQ.prepare(R"(
                SELECT id FROM contacts
                WHERE user_id=:uid AND first_name=:fn AND last_name=:ln
            )");
            cQ.bindValue(":uid", userId);
            cQ.bindValue(":fn", fn);
            cQ.bindValue(":ln", ln);

            if (cQ.exec() && cQ.next()) {
                int contactId = cQ.value(0).toInt();
                QSqlQuery lQ(db);
                lQ.prepare(R"(
                    INSERT OR IGNORE INTO groups_contacts(group_id,contact_id)
                    VALUES(:gid,:cid)
                )");
                lQ.bindValue(":gid", groupId);
                lQ.bindValue(":cid", contactId);
                if (lQ.exec())
                    ++count;
                else
                    errorCount++;
            } else {
                errorCount++;
            }
        }
    }

    db.commit();
    return count;
}
