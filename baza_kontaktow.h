/**
 * @file baza_kontaktow.h
 * @brief Definicja klasy Baza_Kontaktow, głównego okna aplikacji, które pojawia się po uruchomieniu programu
 *
 * Plik ten zawiera deklarację głównej klasy Baza_Kontaktow, która jest wyświetlana po uruchomieniu programu. Zawiera w sobie również metody (sloty), która pozwalają
 * użytkownikowi na zalogowanie się, lub zarejestrowanie w przypadku nowego użytkownika
 *
*/

#ifndef BAZA_KONTAKTOW_H
#define BAZA_KONTAKTOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "registration.h"
#include "dashboard.h"
#include "user.h"
#include "database_manager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Baza_Kontaktow;
}
QT_END_NAMESPACE

/**
 * @class Baza_Kontaktow
 * @brief Deklaracja głównej klasy programu, Baza_Kontaktow
 */


class Baza_Kontaktow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor klasy Baza_Kontaktow
     * @param parent - wskaźnik na rodzica Widgetu domyślnie ustawiony na NULL
     */
    Baza_Kontaktow(QWidget *parent = nullptr);

    /**
     * @brief Destruktor klasy Baza_Kontaktow, zamyka okno UI
    */

    ~Baza_Kontaktow();

private slots:
    /**
     * @brief Metoda wywołana, po kliknięciu przycisku Zarejestruj
     *
     * Otwiera okno do rejestracji użytkownika, sprawdza poprawność danych (czy podane hasło zgadza się z powtórzonych hasłem), oraz czy w bazie danych, nie występuje
     * już użytkownik o podanym loginie
     */
    void on_registerBtn_clicked();


    /**
     * @brief Metoda wywołana, po kliknięciu przycisku Zaloguj
     *
     * Wyszukuje w bazie danych użytkownika o podanych przez użytkownika danych, jeśli znajdzie pasujące wartości, to wyświetla okno zarządzania
     * kontaktami. Jeśli nie znajdze pasujących danych, to wypisuje odpowiedni komunikat
     */
    void on_loginBtn_clicked();

private:
    Ui::Baza_Kontaktow *ui;
};
#endif // BAZA_KONTAKTOW_H
