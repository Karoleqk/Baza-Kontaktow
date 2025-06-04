#ifndef CREATECONTACT_H
#define CREATECONTACT_H

#include <QDialog>
#include "database_manager.h"
#include "user.h"

namespace Ui {
class CreateContact;
}

/**
 * @class CreateContact
 *
 * @brief Deklaracja klasy, pozwalającej na utworzenie nowego kontaktu
 */
class CreateContact : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor klasy CreateContact
     * @param parent - wskaźnik na rodzica Widgetu, domyślnie ustawiony na NULL
     *
     * Wyświetla okno, pozwalające na dodanie kontaktu
     */
    explicit CreateContact(QWidget *parent = nullptr);

    /**
     * @brief Destruktor klasy CreateContact
     *
     * Zamyka okno UI
    */
    ~CreateContact();

    /**
     * @brief resetForm
     *
     * Metoda czyszcząca wszystkie dane, jakie wprowadził użytkownika do formularza
     */
    void resetForm();

signals:
    void contactAdded();

private slots:
    /**
     * @brief on_btnCancel_clicked
     *
     * Zamknięcie okna UI
     */
    void on_btnCancel_clicked();

    /**
     * @brief on_btnCreate_clicked
     *
     * Pobiera dane wprowadzone przez użytkownika, sprawdza ich poprawność, jeśli wartości są poprawne, to dodaje nowo utworzony kontakt do bazy danych, w przeciwnym
     * wypadku, wyświetla odpowiedni komunikat. Po wszystkim odświeża tabele wyświetlającą wszystkie kontakty aktualnie zalogowanego użytkownika
     */
    void on_btnCreate_clicked();

    /**
     * @brief on_btnAddEmail_clicked
     *
     * Metoda sprawdzająca poprawność wprowadzonego adresu mailowego. Jeśli jest poprawny, to wywołuje metodę prywatną addEmailItem().
     */
    void on_btnAddEmail_clicked();

    /**
     * @brief on_btnAddPhone_clicked
     *
     * Metoda sprawdzająca poprawność wprowadzonego numeru telefonu. Jeśli jest poprany, to wywołuje metodę prywatną addPhoneItem().
     */
    void on_btnAddPhone_clicked();

private:
    Ui::CreateContact *ui;

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

    QStringList getAllEmails() const;
    QStringList getAllPhones() const;
};

#endif // CREATECONTACT_H
