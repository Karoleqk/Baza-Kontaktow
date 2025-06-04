#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include "contactswidget.h"
#include "groupswidget.h"
#include "baza_kontaktow.h"
#include "user.h"

namespace Ui {
class Dashboard;
}

/**
 * @class Dashboard
 *
 * @brief Deklaracja klasy wyświetlającej główne okno po zalogowaniu użytkownika
 */
class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor klasy Dashboard
     * @param parent - wskaźnik na rodzica Wdidgetu, domyślnie ustawiony na NULL
     *
     * Przy wywołaniu, wyświetla okno z kontaktami użytkownika
     */
    explicit Dashboard(QWidget *parent = nullptr);

    /**
     * @brief Destruktor klasy Dashboard
     *
     * Zamyka okno UI
    */
    ~Dashboard();

private slots:
    /**
     * @brief showGroupsPage
     *
     * Metoda wyświetlająca wszystkie grupy aktualnie zalogowanego użytkownika
     */
    void showGroupsPage();

    /**
     * @brief showContactsPage
     *
     * Metoda wyświetlająca wszystkie kontakty aktualnie zalogowanego użytkownika
     */
    void showContactsPage();

    /**
     * @brief on_btnLogout_clicked
     *
     * Metoda wywoływana po wciśnięciu przycisku Wyloguj. Usuwa dane ze zmiennej globalnej currentUser oraz czyści jej miesjce w pamięci komputera, po czym zamyka
     * okno Dashboard i przechodzi do okna logowania Baza_Kontaktow
     */
    void on_btnLogout_clicked();

private:
    Ui::Dashboard *ui;

    /**
     * @brief contactsWidget
     *
     * Widget, zawierający kontaktu użytkownika
     */
    ContactsWidget *contactsWidget;

    /**
     * @brief groupsWidget
     *
     * Widget, zawierający grupy użytkownika
     */
    GroupsWidget *groupsWidget;
};

#endif // DASHBOARD_H
