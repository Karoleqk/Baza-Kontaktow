#include "baza_kontaktow.h"
#include "dashboard.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Baza_Kontaktow w;
    Dashboard w;

    w.show();
    return app.exec();
}
