/********************************************************************************
** Form generated from reading UI file 'logged.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGGED_H
#define UI_LOGGED_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Logged
{
public:
    QWidget *centralwidget;
    QLabel *helloMsg;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Logged)
    {
        if (Logged->objectName().isEmpty())
            Logged->setObjectName("Logged");
        Logged->resize(805, 608);
        centralwidget = new QWidget(Logged);
        centralwidget->setObjectName("centralwidget");
        helloMsg = new QLabel(centralwidget);
        helloMsg->setObjectName("helloMsg");
        helloMsg->setGeometry(QRect(150, 80, 501, 161));
        QFont font;
        font.setPointSize(32);
        font.setBold(true);
        helloMsg->setFont(font);
        helloMsg->setStyleSheet(QString::fromUtf8(".QLabel{\n"
"	background-color: lightblue;\n"
"	color:  #000;\n"
"	border-radius: 30px;\n"
"}"));
        helloMsg->setAlignment(Qt::AlignmentFlag::AlignCenter);
        Logged->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Logged);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 805, 21));
        Logged->setMenuBar(menubar);
        statusbar = new QStatusBar(Logged);
        statusbar->setObjectName("statusbar");
        Logged->setStatusBar(statusbar);

        retranslateUi(Logged);

        QMetaObject::connectSlotsByName(Logged);
    } // setupUi

    void retranslateUi(QMainWindow *Logged)
    {
        Logged->setWindowTitle(QCoreApplication::translate("Logged", "MainWindow", nullptr));
        helloMsg->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Logged: public Ui_Logged {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGGED_H
