/********************************************************************************
** Form generated from reading UI file 'seatingconfigdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEATINGCONFIGDIALOG_H
#define UI_SEATINGCONFIGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SeatingConfigDialog
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QListWidget *togetherList;
    QHBoxLayout *horizontalLayout;
    QPushButton *addTogetherBtn;
    QPushButton *removeTogetherBtn;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QListWidget *cannotList;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *addCannotBtn;
    QPushButton *removeCannotBtn;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SeatingConfigDialog)
    {
        if (SeatingConfigDialog->objectName().isEmpty())
            SeatingConfigDialog->setObjectName("SeatingConfigDialog");
        SeatingConfigDialog->resize(600, 400);
        verticalLayoutWidget = new QWidget(SeatingConfigDialog);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 10, 580, 380));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(verticalLayoutWidget);
        tabWidget->setObjectName("tabWidget");
        tab = new QWidget();
        tab->setObjectName("tab");
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        togetherList = new QListWidget(tab);
        togetherList->setObjectName("togetherList");

        verticalLayout_2->addWidget(togetherList);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        addTogetherBtn = new QPushButton(tab);
        addTogetherBtn->setObjectName("addTogetherBtn");

        horizontalLayout->addWidget(addTogetherBtn);

        removeTogetherBtn = new QPushButton(tab);
        removeTogetherBtn->setObjectName("removeTogetherBtn");

        horizontalLayout->addWidget(removeTogetherBtn);


        verticalLayout_2->addLayout(horizontalLayout);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        cannotList = new QListWidget(tab_2);
        cannotList->setObjectName("cannotList");

        verticalLayout_3->addWidget(cannotList);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        addCannotBtn = new QPushButton(tab_2);
        addCannotBtn->setObjectName("addCannotBtn");

        horizontalLayout_2->addWidget(addCannotBtn);

        removeCannotBtn = new QPushButton(tab_2);
        removeCannotBtn->setObjectName("removeCannotBtn");

        horizontalLayout_2->addWidget(removeCannotBtn);


        verticalLayout_3->addLayout(horizontalLayout_2);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        buttonBox = new QDialogButtonBox(verticalLayoutWidget);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SeatingConfigDialog);

        QMetaObject::connectSlotsByName(SeatingConfigDialog);
    } // setupUi

    void retranslateUi(QDialog *SeatingConfigDialog)
    {
        SeatingConfigDialog->setWindowTitle(QCoreApplication::translate("SeatingConfigDialog", "\345\272\247\344\275\215\345\205\263\347\263\273\351\205\215\347\275\256", nullptr));
        addTogetherBtn->setText(QCoreApplication::translate("SeatingConfigDialog", "\346\267\273\345\212\240", nullptr));
        removeTogetherBtn->setText(QCoreApplication::translate("SeatingConfigDialog", "\347\247\273\351\231\244", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("SeatingConfigDialog", "\345\277\205\351\241\273\345\235\220\345\234\250\344\270\200\350\265\267", nullptr));
        addCannotBtn->setText(QCoreApplication::translate("SeatingConfigDialog", "\346\267\273\345\212\240", nullptr));
        removeCannotBtn->setText(QCoreApplication::translate("SeatingConfigDialog", "\347\247\273\351\231\244", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("SeatingConfigDialog", "\344\270\215\350\203\275\345\235\220\345\234\250\344\270\200\350\265\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SeatingConfigDialog: public Ui_SeatingConfigDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEATINGCONFIGDIALOG_H
