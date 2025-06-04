#include "baza_kontaktow.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStyleFactory>

/**
 * @mainpage Projekt: Baza kontaktów
 *
 * @section opis Opis projektu
 * Ten projekt implementuje interfejs graficzny z możliwością zalogowania się, zarejestrowania nowego użytkownika oraz zarządzanie kontaktami, dodawanie nowych rekordów, tworzenie
 * grup kontaktów, sortowania po dowolnej wartości oraz import/export z plików CSV/JSON. Projekt ten został stworzony z wykorzystaniem języka C++ oraz z użyciem biblioteki QtCreator
 *
 *
 * @section autor Autor
 * Projekt stworzony przez Karol Kaczmarczyk oraz Gabriel Kałczuga
 *
 */

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QApplication::setStyle(QStyleFactory::create("Fusion"));

    QPalette darkPalette;

    darkPalette.setColor(QPalette::Text, Qt::white);

    app.setPalette(darkPalette);

    Baza_Kontaktow w;
    w.show();

    return app.exec();
}
