#ifndef GROUPSWIDGET_H
#define GROUPSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QFont>
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonObject>
#include "creategroup.h"
#include "editgroup.h"
#include "database_manager.h"
#include "user.h"

namespace Ui {
class GroupsWidget;
}


/**
 * @class GroupsWidget
 *
 * @brief Deklaracja klasy, która wyświetla grupy utworzone przez użytkownika
 */
class GroupsWidget : public QWidget
{
    Q_OBJECT

public:

    /**
     * @brief Konstruktor klasy GroupsWidget
     * @param parent - wskaźnik na rodzica Widgetu, domyślnie ustawiony na NULL
     *
     * Przy wywołaniu pobiera dany z bazy danych odnośnie grup, które użytkownik posiada i tworzy dwie tabelki. Jedna do wyświetlania grup, druga do wyświetlania
     * kontaktów, które w danej grupie się znajdują
     */
    explicit GroupsWidget(QWidget *parent = nullptr);

    /**
     * @brief Destruktor klasy GroupsWidget
     *
     * Zamyka okno UI
    */
    ~GroupsWidget();

private slots:
    /**
     * @brief on_addGroupBtn_clicked
     *
     * Otwiera okno do utworzenia grupy, klasy creategroup
     */
    void on_addGroupBtn_clicked();

    /**
     * @brief on_editBtn_clicked
     *
     * Pobiera ID wybranej grupy, oraz wyświetla okno do jej edycji, klasy editGroup
     */
    void on_editBtn_clicked();

    /**
     * @brief on_deleteBtn_clicked
     *
     * Po wciśnięciu przycisku do usunięcia grupy, pobiera ID wybranej grupy do usunięcia, po czym wykonuje zapytanie odnośnie usunięcia jej z bazy danych. Na koniec odświeża
     * tabelę z grupami
     */
    void on_deleteBtn_clicked();

    /**
     * @brief on_showBtn_clicked
     *
     * Wyswietla wszystkie kontakty, jakie znajdują się w grupie, którą chcemy wyświetlić
     */
    void on_showBtn_clicked();


    /**
     * @brief on_btnImport_clicked
     *
     * Importuje plik z grupami, dając do wyboru format CSV, lub JSON
     */
    void on_btnImport_clicked();


    /**
     * @brief on_btnExport_clicked
     *
     * Eksportuje plik z grupami, dając do wyboru format CSV, lub JSON
     */
    void on_btnExport_clicked();

public slots:
    void reloadGroups();

private:
    Ui::GroupsWidget *ui;

    /**
     * @brief grpPtr
     *
     * Zmienna wskaźnikowa prywatna, wskazująca na obiekt klasy creategroup
     */
    creategroup *grpPtr;

    /**
     * @brief editGrpPtr
     *
     * Zmienna wskaźnikowa prywatna, wskazująca na obiekt klasy editGroup
     */
    editGroup *editGrpPtr;

    /**
     * @brief exportToCSV
     * @param plik, do którego eksportujemy grupy
     * @return Zwraca 1, jeśli operacja się powiedzie. W przeciwnym wypadku zwraca -1
     *
     * Deklaracja prywatnej metody typu int, która eksportuje grupy do pliku CSV
     */
    int exportToCSV(QFile& file);

    /**
     * @brief exportToJSON
     * @param plik, do którego eksportujemy grupy
     * @return Zwraca 1, jeśli operacja się powiedzie. W przeciwnym wypadku zwraca -1
     *
     * Deklaracja prywatnej metody typu int, która eksportuje grupy do pliku JSON
     */
    int exportToJSON(QFile& file);

    /**
     * @brief importGroupsFromCSV
     * @param file - plik, z którego importujemy
     * @param errorCount - licznik błędów (pusta linia)
     * @return Zwraca 0, gdy kończy swoje działanie
     */
    int importGroupsFromCSV(QFile& file, int& errorCount);

    /**
     * @brief importGroupsFromJSON
     * @param file - plik, z którego importujemy
     * @param errorCount - licznik błędów (pusta linia)
     * @return Zwraca 0, gdy kończy swoje działanie
     */
    int importGroupsFromJSON(QFile& file, int& errorCount);

    /**
     * @brief parseCSVLine
     * @param line - linia pobrana z pliku CSV
     * @return Zwraca sparsowaną linijkę z pliku CSV
     */
    QStringList parseCSVLine(const QString& line);
};

#endif // GROUPSWIDGET_H
