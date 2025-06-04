#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QMainWindow>

#include "baza_kontaktow.h"
#include "database_manager.h"
#include "hash.h"

namespace Ui {
class Registration;
}


/**
 * @class Registration
 *
 * @brief Deklaracja klasy, dzięki której użytkownik może się zarejestrować
 */
class Registration : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor klasy Registration
     * @param parent - wskaźnik na rodzica Widgetu, domyślnie ustawiony na NULL
     *
     * Otwiera okno z możliwościa zarejestrowania się
     */
    explicit Registration(QWidget *parent = nullptr);

    /**
     * @brief Destruktor klasy Registration
     *
     * Zamyka okno UI
    */
    ~Registration();

private slots:
    /**
     * @brief on_loginBtn_clicked
     *
     * Zamyka okno rejestracji i otwiera okno do zalogowania się
     */
    void on_loginBtn_clicked();


    /**
     * @brief on_registerBtn_clicked
     *
     * Po wciśnięciu przycisku zarejestruj, sprawdza poprawność danych. Jeśli dane są poprawne (hasła się zgadzają oraz wybrana nazwa nie jest zajęta), to wykonuje
     * zapytanie do bazy danych dodające nowego użytkownika
     */
    void on_registerBtn_clicked();

private:
    Ui::Registration *ui;
};

#endif // REGISTRATION_H
