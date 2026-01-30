/********************************************************************************
** Form generated from reading UI file 'importdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMPORTDIALOG_H
#define UI_IMPORTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImportDialog
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *filePathEdit;
    QPushButton *browseBtn;
    QLabel *label_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ImportDialog)
    {
        if (ImportDialog->objectName().isEmpty())
            ImportDialog->setObjectName("ImportDialog");
        ImportDialog->resize(600, 150);
        verticalLayoutWidget = new QWidget(ImportDialog);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 10, 580, 130));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        filePathEdit = new QLineEdit(verticalLayoutWidget);
        filePathEdit->setObjectName("filePathEdit");
        filePathEdit->setReadOnly(true);

        horizontalLayout->addWidget(filePathEdit);

        browseBtn = new QPushButton(verticalLayoutWidget);
        browseBtn->setObjectName("browseBtn");

        horizontalLayout->addWidget(browseBtn);


        verticalLayout->addLayout(horizontalLayout);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        buttonBox = new QDialogButtonBox(verticalLayoutWidget);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ImportDialog);

        QMetaObject::connectSlotsByName(ImportDialog);
    } // setupUi

    void retranslateUi(QDialog *ImportDialog)
    {
        ImportDialog->setWindowTitle(QCoreApplication::translate("ImportDialog", "\345\257\274\345\205\245\346\210\220\347\273\251\346\226\207\344\273\266", nullptr));
        label->setText(QCoreApplication::translate("ImportDialog", "\346\226\207\344\273\266\350\267\257\345\276\204\357\274\232", nullptr));
        browseBtn->setText(QCoreApplication::translate("ImportDialog", "\346\265\217\350\247\210", nullptr));
        label_2->setText(QCoreApplication::translate("ImportDialog", "\350\257\267\351\200\211\346\213\251\345\214\205\345\220\253\345\255\246\347\224\237\346\210\220\347\273\251\344\277\241\346\201\257\347\232\204Excel\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImportDialog: public Ui_ImportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMPORTDIALOG_H
