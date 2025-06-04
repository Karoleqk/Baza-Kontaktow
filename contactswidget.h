#ifndef CONTACTSWIDGET_H
#define CONTACTSWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include "createcontact.h"
#include "editcontact.h"

namespace Ui {
class ContactsWidget;
}

/**
 * @class ContactsWidget
 * @brief Deklaracja klasy, wyświetlającej kontakty zalogowanego użytkownika
 */

class ContactsWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor klasy ContactsWidget
     * @param Wskaznik na rodzica Widgetu domyślnie ustawiony na NULL
     *
     * W konstruktorze wyświetlane jest okno UI, które pokazuje wszystkie kontaktu aktualnie zalogowanego użytkownika. Tworzy połączenie przycisków dodających kontakt
     * i edytujących kontakt, z funkcją, która odświeża dane w tabeli. Następnie tworzy tabelę z polami "ID", "Imie", "Nazwisko", "Numer telefonu", "Email", "Adres".
     */
    explicit ContactsWidget(QWidget *parent = nullptr);

    /**
     * @brief Destruktor klasy ContactsWidget, zamyka okno UI
    */
    ~ContactsWidget();

    /**
     * @brief refreshContactsTable
     *
     * Odświeża dane w tabeli wyświetlającej kontakty aktualnie zalogowanego użytkownika
     */
    void refreshContactsTable();

private slots:
    /**
     * @brief on_btnCreateContact_clicked
     *
     * Wyświetla okno, pozwalające na dodanie nowego kontaktu
     */
    void on_btnCreateContact_clicked();

    /**
     * @brief onEditButtonClicked
     *
     * Wyświetla okno, pozwalające na edytowanie istniejącego już kontaktu
     */
    void onEditButtonClicked();

    /**
     * @brief onDeleteButtonClicked
     *
     * Usuwa z bazy danych wybrany kontakt, po czym odświeża zawartość tablicy kontaktów
     */
    void onDeleteButtonClicked();


    /**
     * @brief on_btnImport_clicked
     *
     * Importuje plik z kontaktami, dając do wyboru format CSV, lub JSON
     */
    void on_btnImport_clicked();


    /**
     * @brief on_btnExport_clicked
     *
     * Eksportuje plik z kontaktami, dając do wyboru format CSV, lub JSON
     */
    void on_btnExport_clicked();

private:
    Ui::ContactsWidget *ui;
    /**
     * @brief ptrCreateContact
     *
     * Deklaracja zmiennej prywatnej wskaźnikowej klasy ContactsWidget, wskazującej na obiekt klasy CreateContact
     */
    CreateContact *ptrCreateContact;

    /**
     * @brief ptrEditContact
     *
     * Deklaracja zmiennej prywatnej wskaźnikowej klasy ContactsWidget, wskazującej na obiekt klasy EditContact
     */
    EditContact *ptrEditContact;

    /**
     * @brief exportToCSV
     * @param plik, do którego eksportujemy kontakty
     * @return Zwraca 1, jeśli operacja się powiedzie. W przeciwnym wypadku zwraca -1
     *
     * Deklaracja prywatnej metody typu int, która eksportuje kontakty do pliku CSV
     */
    int exportToCSV(QFile& file);

    /**
     * @brief exportToJSON
     * @param plik, do którego eksportujemy kontakty
     * @return Zwraca 1, jeśli operacja się powiedzie. W przeciwnym wypadku zwraca -1
     *
     * Deklaracja prywatnej metody typu int, która eksportuje kontakty do pliku JSON
     */
    int exportToJSON(QFile& file);

    /**
     * @brief importFromCSV
     * @param file - plik, z którego importujemy
     * @param errorCount - licznik błędów (pusta linia)
     * @return Zwraca 0, gdy kończy swoje działanie
     */
    int importFromCSV(QFile& file, int& errorCount);

    /**
     * @brief importFromJSON
     * @param file - plik, z którego importujemy
     * @param errorCount - licznik błędów (pusta linia)
     * @return Zwraca 0, gdy kończy swoje działanie
     */
    int importFromJSON(QFile& file, int& errorCount);

    /**
     * @brief parseCSVLine
     * @param line - linia pobrana z pliku CSV
     * @return Zwraca sparsowaną linijkę z pliku CSV
     */
    QStringList parseCSVLine(const QString& line);
};

#endif // CONTACTSWIDGET_H
