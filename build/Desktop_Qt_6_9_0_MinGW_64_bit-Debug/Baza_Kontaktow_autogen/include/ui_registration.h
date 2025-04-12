/********************************************************************************
** Form generated from reading UI file 'registration.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATION_H
#define UI_REGISTRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Registration
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *loginLabel;
    QLineEdit *loginInput;
    QHBoxLayout *horizontalLayout_3;
    QLabel *passwordLabel;
    QLineEdit *passwordInput;
    QHBoxLayout *horizontalLayout;
    QLabel *repeatPasswordLabel;
    QLineEdit *repeatPasswordInput;
    QVBoxLayout *verticalLayout_4;
    QPushButton *registerBtn;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_4;
    QPushButton *loginBtn;

    void setupUi(QMainWindow *Registration)
    {
        if (Registration->objectName().isEmpty())
            Registration->setObjectName("Registration");
        Registration->resize(358, 420);
        centralwidget = new QWidget(Registration);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        QFont font;
        font.setPointSize(28);
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label_2);


        verticalLayout_5->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(12);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(10, -1, 10, -1);
        loginLabel = new QLabel(centralwidget);
        loginLabel->setObjectName("loginLabel");

        horizontalLayout_2->addWidget(loginLabel);

        loginInput = new QLineEdit(centralwidget);
        loginInput->setObjectName("loginInput");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(loginInput->sizePolicy().hasHeightForWidth());
        loginInput->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(loginInput);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 6);

        verticalLayout_3->addLayout(horizontalLayout_2);

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

        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(12);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(10, -1, 10, -1);
        repeatPasswordLabel = new QLabel(centralwidget);
        repeatPasswordLabel->setObjectName("repeatPasswordLabel");

        horizontalLayout->addWidget(repeatPasswordLabel);

        repeatPasswordInput = new QLineEdit(centralwidget);
        repeatPasswordInput->setObjectName("repeatPasswordInput");
        sizePolicy.setHeightForWidth(repeatPasswordInput->sizePolicy().hasHeightForWidth());
        repeatPasswordInput->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(repeatPasswordInput);


        verticalLayout_3->addLayout(horizontalLayout);


        verticalLayout_5->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(-1, 10, -1, -1);
        registerBtn = new QPushButton(centralwidget);
        registerBtn->setObjectName("registerBtn");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(registerBtn->sizePolicy().hasHeightForWidth());
        registerBtn->setSizePolicy(sizePolicy1);

        verticalLayout_4->addWidget(registerBtn);


        verticalLayout_5->addLayout(verticalLayout_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_6->addWidget(label_4);

        loginBtn = new QPushButton(centralwidget);
        loginBtn->setObjectName("loginBtn");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(loginBtn->sizePolicy().hasHeightForWidth());
        loginBtn->setSizePolicy(sizePolicy2);

        verticalLayout_6->addWidget(loginBtn);

        verticalLayout_6->setStretch(0, 4);
        verticalLayout_6->setStretch(1, 3);

        verticalLayout_5->addLayout(verticalLayout_6);

        verticalLayout_5->setStretch(0, 3);
        verticalLayout_5->setStretch(1, 4);
        verticalLayout_5->setStretch(2, 1);
        verticalLayout_5->setStretch(4, 2);

        verticalLayout->addLayout(verticalLayout_5);

        Registration->setCentralWidget(centralwidget);

        retranslateUi(Registration);

        QMetaObject::connectSlotsByName(Registration);
    } // setupUi

    void retranslateUi(QMainWindow *Registration)
    {
        Registration->setWindowTitle(QCoreApplication::translate("Registration", "MainWindow", nullptr));
        label_2->setText(QCoreApplication::translate("Registration", "Zarejestruj sie", nullptr));
        loginLabel->setText(QCoreApplication::translate("Registration", "Login: ", nullptr));
        passwordLabel->setText(QCoreApplication::translate("Registration", "Haslo:", nullptr));
        repeatPasswordLabel->setText(QCoreApplication::translate("Registration", "Powtorz haslo:", nullptr));
        registerBtn->setText(QCoreApplication::translate("Registration", "Zarejestruj", nullptr));
        label_4->setText(QCoreApplication::translate("Registration", "Masz juz konto?", nullptr));
        loginBtn->setText(QCoreApplication::translate("Registration", "Zaloguj sie", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Registration: public Ui_Registration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATION_H
