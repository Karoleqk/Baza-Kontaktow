#ifndef EDITCONTACT_H
#define EDITCONTACT_H

#include <QDialog>
#include <QMessageBox>
#include "user.h"
#include "database_manager.h"

namespace Ui {
class EditContact;
}

/**
 * @class EditContact
 *
 * @brief Deklaracja klasy, pozwalającej na edytowanie istniejących kontaktów
 */
class EditContact : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor klasy EditContact
     * @param parent - wskaźnik na rodzica Widgetu, domyślnie ustawiony na NULL
     *
     * Otwiera okno do edycji kontaktu
     */
    explicit EditContact(QWidget *parent = nullptr);

    /**
     * @brief Destruktor klasy EditContact
     *
     * Zamyka okno UI
    */
    ~EditContact();

    /**
     * @brief loadContactData
     * @param contactId - id kontaktu, który chcemy zedytować
     * @return Metoda zwraca true, jeśli operacja się powiedzie. W przeciwnym wypadku zwraca false
     *
     * Metoda wyświetla wszystkie dane kontaktu do formularza, w którym możemy je zedytować
     */
    bool loadContactData(int contactId);

    /**
     * @brief resetForm
     *
     * Metoda resetująca formularz edycji
     */
    void resetForm();

signals:

    /**
     * @brief contactUpdated
     *
     * Sygnał, dzięki któremu możemy sprawdzić, czy kontakt został zaktualizowany
     */
    void contactUpdated();

private slots:
    /**
     * @brief on_btnCancel_2_clicked
     *
     * Zamyka okno do edycji kontaktu
     */
    void on_btnCancel_2_clicked();

    /**
     * @brief on_btnSave_clicked
     *
     * Zapisuje zedytowane dane o kontakcie, po czym wykonuje zapytanie do bazy danych z nowymi wartościami
     */
    void on_btnSave_clicked();

    /**
     * @brief on_btnAddEmail_clicked
     *
     * Metoda pozwalająca na dodanie kolejnego adresu mailowego do kontaktu, lub zedytowania już istniejącego
     */
    void on_btnAddEmail_clicked();


    /**
     * @brief on_btnAddPhone_clicked
     *
     * Metoda pozwalająca na dodanie kolejnego numeru telefonu do kontaktu, lub zedytowanie już istniejącego
     */
    void on_btnAddPhone_clicked();

private:
    Ui::EditContact *ui;
    int m_contactId;

    /**
     * @brief addEmailItem
     * @param email - adres mailowy, który chcemy dodać
     *
     * Metoda dodaje do danych kontaktu adres mailowy. Dzięki niej możemy dodać kilka adresów dla pojedynczego kontaktu
     */
    void addEmailItem(const QString &email);

    /**
     * @brief addPhoneItem
     * @param phone - numer telefonu, który chcemy dodać
     *
     * Metoda dodaje do danych kontaktu numer telefonu. Dzięki niej możemy dodać kilka numerów telefonów dla pojedynczego kontaktu
     */
    void addPhoneItem(const QString &phone);
};

#endif // EDITCONTACT_H
