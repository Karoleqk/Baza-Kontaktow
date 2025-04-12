/********************************************************************************
** Form generated from reading UI file 'dashboard.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DASHBOARD_H
#define UI_DASHBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dashboard
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *header;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *labelTotal;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *lineEdit_2;
    QPushButton *btnSearch;
    QWidget *mainBody;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *tableContacts;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *btnCreateContact;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QMainWindow *Dashboard)
    {
        if (Dashboard->objectName().isEmpty())
            Dashboard->setObjectName("Dashboard");
        Dashboard->resize(1127, 695);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Dashboard->sizePolicy().hasHeightForWidth());
        Dashboard->setSizePolicy(sizePolicy);
        Dashboard->setStyleSheet(QString::fromUtf8("* {\n"
"	border: none;\n"
"	background-color: transparent;\n"
"	background: transparent;\n"
"	padding: 0;\n"
"	margin: 0;\n"
"	color: black;\n"
"}\n"
"\n"
"#centralwidget {\n"
"	background-color: white;\n"
"}\n"
"\n"
"#header, #mainBody, #sidebar {\n"
"	background-color: #F9F9F9;\n"
"}\n"
"\n"
"QPushButton {\n"
"	background-color: #007BFF; \n"
"	color: white;\n"
"	padding: 10px;\n"
"	border-radius: 4px;\n"
"	text-align: center;\n"
"	text-decoration: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background-color: #42A5F5;\n"
"}\n"
"\n"
"#labelTotal {\n"
"	font-weight: 700;\n"
"}\n"
"\n"
"QLineEdit {\n"
"	background-color: white;\n"
"        border: 1px solid gray;\n"
"        border-radius: 4px;\n"
"        padding: 8px;\n"
"        transition: all 0.3s ease-in-out;\n"
"}\n"
"    \n"
"QLineEdit:focus {\n"
"        border-color: black;\n"
"}\n"
"\n"
"QTableWidget {\n"
"    border: 1px solid #ddd; /* Light border around the table */\n"
"}\n"
"\n"
"QTableWidget::item {\n"
"    padding: 8px;\n"
"    border-bottom: "
                        "1px solid #ddd;\n"
"}\n"
"\n"
"QTableWidget::item:selected {\n"
"    background-color: #4caf50; /* Green selection for each item */\n"
"    color: white; /* White text when selected */\n"
"}\n"
"\n"
"QTableWidget QHeaderView::section {\n"
"    background-color: #f5f5f5; /* Light gray background for the header */\n"
"    color: #333; /* Dark text for headers */\n"
"    padding: 8px;\n"
"    border: 1px solid #ddd; /* Border around headers */\n"
"    font-weight: bold; /* Bold text in header */\n"
"}\n"
"\n"
"QTableWidget QHeaderView::section:horizontal {\n"
"    border-right: 1px solid #ddd; /* Horizontal border between columns */\n"
"}\n"
"\n"
"QTableWidget QScrollBar:horizontal, QTableWidget QScrollBar:vertical {\n"
"    border: none;\n"
"    background-color: #f5f5f5;\n"
"    height: 10px;\n"
"    width: 10px;\n"
"}\n"
"\n"
"QTableWidget QScrollBar::handle:horizontal, QTableWidget QScrollBar::handle:vertical {\n"
"    background-color: #bbb;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QTableWidget QScrollBar:"
                        ":handle:horizontal:hover, QTableWidget QScrollBar::handle:vertical:hover {\n"
"    background-color: #888; /* Darker handle color on hover */\n"
"}\n"
""));
        centralwidget = new QWidget(Dashboard);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        header = new QWidget(centralwidget);
        header->setObjectName("header");
        header->setStyleSheet(QString::fromUtf8("#header {\n"
"	-webkit-box-shadow: 8px 8px 24px 0px rgba(66, 68, 90, 1);\n"
"	-moz-box-shadow: 8px 8px 24px 0px rgba(66, 68, 90, 1);\n"
"	box-shadow: 8px 8px 24px 0px rgba(66, 68, 90, 1);\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(header);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(header);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        labelTotal = new QLabel(header);
        labelTotal->setObjectName("labelTotal");

        horizontalLayout_2->addWidget(labelTotal);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        lineEdit_2 = new QLineEdit(header);
        lineEdit_2->setObjectName("lineEdit_2");

        horizontalLayout_2->addWidget(lineEdit_2);

        btnSearch = new QPushButton(header);
        btnSearch->setObjectName("btnSearch");

        horizontalLayout_2->addWidget(btnSearch);


        verticalLayout_2->addWidget(header, 0, Qt::AlignmentFlag::AlignTop);

        mainBody = new QWidget(centralwidget);
        mainBody->setObjectName("mainBody");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(mainBody->sizePolicy().hasHeightForWidth());
        mainBody->setSizePolicy(sizePolicy1);
        verticalLayout_3 = new QVBoxLayout(mainBody);
        verticalLayout_3->setObjectName("verticalLayout_3");
        tableContacts = new QTableWidget(mainBody);
        if (tableContacts->columnCount() < 7)
            tableContacts->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableContacts->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableContacts->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableContacts->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableContacts->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableContacts->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableContacts->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableContacts->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tableContacts->setObjectName("tableContacts");
        tableContacts->setEnabled(true);
        tableContacts->setSortingEnabled(true);
        tableContacts->horizontalHeader()->setCascadingSectionResizes(false);
        tableContacts->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_3->addWidget(tableContacts);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        verticalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_2->addWidget(mainBody);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        btnCreateContact = new QPushButton(centralwidget);
        btnCreateContact->setObjectName("btnCreateContact");

        horizontalLayout_6->addWidget(btnCreateContact);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_6);

        Dashboard->setCentralWidget(centralwidget);

        retranslateUi(Dashboard);

        QMetaObject::connectSlotsByName(Dashboard);
    } // setupUi

    void retranslateUi(QMainWindow *Dashboard)
    {
        Dashboard->setWindowTitle(QCoreApplication::translate("Dashboard", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("Dashboard", "Wszystkich kontakt\303\263w:", nullptr));
        labelTotal->setText(QCoreApplication::translate("Dashboard", "12", nullptr));
        lineEdit_2->setPlaceholderText(QCoreApplication::translate("Dashboard", "Wyszukaj", nullptr));
        btnSearch->setText(QCoreApplication::translate("Dashboard", "Szukaj", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableContacts->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Dashboard", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableContacts->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Dashboard", "Imi\304\231", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableContacts->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Dashboard", "Nazwisko", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableContacts->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("Dashboard", "Adres", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableContacts->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("Dashboard", "Telefon", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableContacts->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("Dashboard", "E-mail", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableContacts->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("Dashboard", "Akcje", nullptr));
        btnCreateContact->setText(QCoreApplication::translate("Dashboard", "Dodaj kontakt", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dashboard: public Ui_Dashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBOARD_H
