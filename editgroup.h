#ifndef EDITGROUP_H
#define EDITGROUP_H

#include <QWidget>
#include <QMessageBox>
#include "database_manager.h"
#include "user.h"


namespace Ui {
class editGroup;
}

/**
 * @class editGroup
 *
 * @brief Deklaracja klasy pozwalającej na zedytowanie istniejących grup
 */
class editGroup : public QWidget
{
    Q_OBJECT

signals:
    /**
     * @brief groupEdited
     *
     * Sygnał, dzięki któremu sprawdzamy czy grupa została zedytowana
     */
    void groupEdited();

public:
    /**
     * @brief Konstruktor klasy editGroup
     * @param parent - wskaźnik na rodzica Widgetu, domyślnie ustawiony na NULL
     *
     * Otwiera okno do edycji grupy, pobiera z bazy danych wartości, którę należą do grupy, którą chcemy zedytować po czym oknie do edycji, wyświetla nazwę grupy oraz listę
     * kontaktów, które do niej należą
     */
    explicit editGroup(QWidget *parent = nullptr);

    /**
     * @brief Destruktor klasy editGroup
     *
     * Zamyka okno UI
    */
    ~editGroup();

    /**
     * @brief currentGroupId
     *
     * Zmienna publiczna przechowująca ID grupy, którą chcemy zedytować
     */
    int currentGroupId;

    /**
     * @brief loadGroupData
     * @param groupId - ID grupy, której dane chcemy zedytować
     * @return Zwraca true, jeśli operacja się powiedzie, w przeciwnym wypadku zwraca false
     *
     * Metoda pobiera dane o grupie o wskazanym ID i wyświetla je w oknie do edycji
     */
    bool loadGroupData(int groupId);

    /**
     * @brief resetForm
     *
     * Resetuje formularz edycji grupy
     */
    void resetForm();

private slots:
    /**
     * @brief on_saveBtn_clicked
     *
     * Zapisuje zmienione dane w grupie i aktualizuje je w bazie danych
     */
    void on_saveBtn_clicked();

    /**
     * @brief on_closeBtn_clicked
     *
     * Zamyka okno do edycji grupy
     */
    void on_closeBtn_clicked();

private:
    Ui::editGroup *ui;

    /**
     * @brief refreshContactsList
     *
     * Metoda odświeżająca kontakty w liście do wyboru, posortowana w ten sposób, że na górze najpierw pojawiają się kontakty znajdujące się już w grupie
     */
    void refreshContactsList();

    /**
     * @brief checkedContactIds
     *
     * Zmienna przechowująca ID kontaktów, które należą do grupy
     */
    QSet<int> checkedContactIds;
};

#endif // EDITGROUP_H
