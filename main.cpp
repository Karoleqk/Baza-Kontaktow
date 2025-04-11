#include "baza_kontaktow.h"
#include "dashboard.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Baza_Kontaktow w;
    Dashboard w;

    w.show();
    return a.exec();
}
