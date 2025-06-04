#ifndef CREATEGROUP_H
#define CREATEGROUP_H

#include <QWidget>
#include <QMessageBox>
#include "database_manager.h"
#include "user.h"

namespace Ui {
class creategroup;
}

/**
 * @class creategroup
 *
 * @brief Deklaracja klasy, pozwalającej na utworzenie grupy kontaktów
 */
class creategroup : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor klasy creategroup
     * @param parent - wskaźnik na rodzica Widgetu, domyślnie ustawiony na NULL
     *
     * Przy wywołaniu, wyświetlane jest okno utworzenia grupy, oraz pobierane są dane wszystkich kontaktów należących do aktualnie zalogowanego użytkownika, oraz
     * wyświetlenie ich w formie listy do wyboru za pomocą metody loadData().
     */
    explicit creategroup(QWidget *parent = nullptr);

    /**
     * @brief Destruktor klasy creategroup
     *
     * Zamyka okno UI
    */
    ~creategroup();

    /**
     * @brief loadData
     *
     * Metoda, która wyświetla wszystkie kontakty użytkownika w formie listy do wyboru.
     */
    void loadData();

    /**
     * @brief resetForm
     *
     * Metoda resetująca formularz tworzenia grupy
     */
    void resetForm();

signals:
    void groupCreated();

private slots:

    /**
     * @brief on_closeBtn_clicked
     *
     * Zamyka okno tworzenia grupy
     */
    void on_closeBtn_clicked();

    /**
     * @brief on_addBtn_clicked
     *
     * Metoda wywoływana po wciśnięciu przycisku Dodaj. Sprawdza poprawność nazwy grupy, następnie sprawdza, które kontakty zaznaczył użytkownik, wybiera te kontakty i wykonuje
     * zapytanie do bazy danych, dodając wszystkie zaznaczone elementy.
     */
    void on_addBtn_clicked();

private:
    Ui::creategroup *ui;

    QSet<int> checkedContactIds;
};

#endif // CREATEGROUP_H
