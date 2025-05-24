#include "baza_kontaktow.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStyleFactory>

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
