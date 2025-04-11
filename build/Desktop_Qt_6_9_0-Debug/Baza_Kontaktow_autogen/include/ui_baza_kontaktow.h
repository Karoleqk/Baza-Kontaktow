/********************************************************************************
** Form generated from reading UI file 'baza_kontaktow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BAZA_KONTAKTOW_H
#define UI_BAZA_KONTAKTOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Baza_Kontaktow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *loginLabel;
    QLineEdit *loginInput;
    QHBoxLayout *horizontalLayout_3;
    QLabel *passwordLabel;
    QLineEdit *passwordInput;
    QVBoxLayout *verticalLayout_3;
    QPushButton *loginBtn;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_4;
    QPushButton *registerBtn;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *Baza_Kontaktow)
    {
        if (Baza_Kontaktow->objectName().isEmpty())
            Baza_Kontaktow->setObjectName("Baza_Kontaktow");
        Baza_Kontaktow->resize(343, 448);
        Baza_Kontaktow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(Baza_Kontaktow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8(".QWidget{\n"
"	background-color: #181C14;\n"
"}\n"
"\n"
".QLabel{\n"
"	color: #ECDFCC;\n"
"}\n"
"\n"
".QLineEdit{\n"
"	color: #ECDFCC;\n"
"	background-color: #3C3D37;\n"
"	border-radius: 6px;\n"
"}\n"
"\n"
".QPushButton{\n"
"	background-color: #3C3D37;\n"
"	color: #ECDFCC;\n"
"	border: 2px solid #ECDFCC;\n"
"	border-radius: 8px;\n"
"}\n"
"\n"
".QPushButton:hover{\n"
"	background-color: #ECDFCC;\n"
"	color: #3C3D37;\n"
"	border: 2px solid #3C3D37;\n"
"}"));
        verticalLayout_6 = new QVBoxLayout(centralwidget);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(28);
        label->setFont(font);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label);


        verticalLayout_5->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(12);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(10, -1, 10, -1);
        loginLabel = new QLabel(centralwidget);
        loginLabel->setObjectName("loginLabel");

        horizontalLayout_2->addWidget(loginLabel);

        loginInput = new QLineEdit(centralwidget);
        loginInput->setObjectName("loginInput");
        QSizePolicy sizePolicy(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(loginInput->sizePolicy().hasHeightForWidth());
        loginInput->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(loginInput);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 6);

        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(12);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(10, -1, 10, -1);
        passwordLabel = new QLabel(centralwidget);
        passwordLabel->setObjectName("passwordLabel");

        horizontalLayout_3->addWidget(passwordLabel);

        passwordInput = new QLineEdit(centralwidget);
        passwordInput->setObjectName("passwordInput");
        sizePolicy.setHeightForWidth(passwordInput->sizePolicy().hasHeightForWidth());
        passwordInput->setSizePolicy(sizePolicy);
        passwordInput->setEchoMode(QLineEdit::EchoMode::Password);

        horizontalLayout_3->addWidget(passwordInput);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 6);

        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout_5->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(-1, 10, -1, -1);
        loginBtn = new QPushButton(centralwidget);
        loginBtn->setObjectName("loginBtn");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(loginBtn->sizePolicy().hasHeightForWidth());
        loginBtn->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setBold(true);
        loginBtn->setFont(font1);
        loginBtn->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_3->addWidget(loginBtn);


        verticalLayout_5->addLayout(verticalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(label_4);

        registerBtn = new QPushButton(centralwidget);
        registerBtn->setObjectName("registerBtn");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(registerBtn->sizePolicy().hasHeightForWidth());
        registerBtn->setSizePolicy(sizePolicy2);
        registerBtn->setFont(font1);

        verticalLayout_4->addWidget(registerBtn);

        verticalLayout_4->setStretch(0, 4);
        verticalLayout_4->setStretch(1, 3);

        verticalLayout_5->addLayout(verticalLayout_4);

        verticalLayout_5->setStretch(0, 3);
        verticalLayout_5->setStretch(1, 4);
        verticalLayout_5->setStretch(2, 1);
        verticalLayout_5->setStretch(4, 2);

        verticalLayout_6->addLayout(verticalLayout_5);

        Baza_Kontaktow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(Baza_Kontaktow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 343, 23));
        Baza_Kontaktow->setMenuBar(menuBar);

        retranslateUi(Baza_Kontaktow);

        QMetaObject::connectSlotsByName(Baza_Kontaktow);
    } // setupUi

    void retranslateUi(QMainWindow *Baza_Kontaktow)
    {
        Baza_Kontaktow->setWindowTitle(QCoreApplication::translate("Baza_Kontaktow", "Baza_Kontaktow", nullptr));
        label->setText(QCoreApplication::translate("Baza_Kontaktow", "Zaloguj sie", nullptr));
        loginLabel->setText(QCoreApplication::translate("Baza_Kontaktow", "Login: ", nullptr));
        passwordLabel->setText(QCoreApplication::translate("Baza_Kontaktow", "Haslo:", nullptr));
        loginBtn->setText(QCoreApplication::translate("Baza_Kontaktow", "Zaloguj", nullptr));
        label_4->setText(QCoreApplication::translate("Baza_Kontaktow", "Nie masz jeszcze konta?", nullptr));
        registerBtn->setText(QCoreApplication::translate("Baza_Kontaktow", "Zarejestruj sie", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Baza_Kontaktow: public Ui_Baza_Kontaktow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BAZA_KONTAKTOW_H
