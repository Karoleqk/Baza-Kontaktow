#include "baza_kontaktow.h"
#include "dashboard.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile file("./styles/style.qss");
    if(file.open(QFile::ReadOnly)){
        QTextStream stream(&file);
        QString styleSheet = stream.readAll();
        app.setStyleSheet(styleSheet);
    }

    qDebug() << QSqlDatabase::drivers();

    // Baza_Kontaktow w;
    Dashboard w;

    w.show();
    return app.exec();
}
