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
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Logged
{
public:
    QAction *actionWyloguj;
    QWidget *centralwidget;
    QLabel *helloMsg;
    QMenuBar *menubar;
    QMenu *menuMenu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Logged)
    {
        if (Logged->objectName().isEmpty())
            Logged->setObjectName("Logged");
        Logged->resize(800, 600);
        Logged->setStyleSheet(QString::fromUtf8(""));
        actionWyloguj = new QAction(Logged);
        actionWyloguj->setObjectName("actionWyloguj");
        centralwidget = new QWidget(Logged);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8(".QWidget{\n"
"	background-color: #181C14;\n"
"}\n"
"\n"
".QLabel{\n"
"	color: #ECDFCC;\n"
"}"));
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
        menubar->setGeometry(QRect(0, 0, 800, 23));
        menuMenu = new QMenu(menubar);
        menuMenu->setObjectName("menuMenu");
        Logged->setMenuBar(menubar);
        statusbar = new QStatusBar(Logged);
        statusbar->setObjectName("statusbar");
        Logged->setStatusBar(statusbar);

        menubar->addAction(menuMenu->menuAction());
        menuMenu->addAction(actionWyloguj);

        retranslateUi(Logged);

        QMetaObject::connectSlotsByName(Logged);
    } // setupUi

    void retranslateUi(QMainWindow *Logged)
    {
        Logged->setWindowTitle(QCoreApplication::translate("Logged", "MainWindow", nullptr));
        actionWyloguj->setText(QCoreApplication::translate("Logged", "Wyloguj", nullptr));
        helloMsg->setText(QString());
        menuMenu->setTitle(QCoreApplication::translate("Logged", "Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Logged: public Ui_Logged {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGGED_H
