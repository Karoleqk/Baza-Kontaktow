/********************************************************************************
** Form generated from reading UI file 'createcontact.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATECONTACT_H
#define UI_CREATECONTACT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_CreateContact
{
public:

    void setupUi(QDialog *CreateContact)
    {
        if (CreateContact->objectName().isEmpty())
            CreateContact->setObjectName("CreateContact");
        CreateContact->resize(400, 300);

        retranslateUi(CreateContact);

        QMetaObject::connectSlotsByName(CreateContact);
    } // setupUi

    void retranslateUi(QDialog *CreateContact)
    {
        CreateContact->setWindowTitle(QCoreApplication::translate("CreateContact", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateContact: public Ui_CreateContact {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATECONTACT_H
