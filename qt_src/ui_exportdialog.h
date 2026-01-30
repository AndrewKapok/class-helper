/********************************************************************************
** Form generated from reading UI file 'exportdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPORTDIALOG_H
#define UI_EXPORTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExportDialog
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *exportTypeComboBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *filePathEdit;
    QPushButton *browseBtn;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ExportDialog)
    {
        if (ExportDialog->objectName().isEmpty())
            ExportDialog->setObjectName("ExportDialog");
        ExportDialog->resize(600, 180);
        verticalLayoutWidget = new QWidget(ExportDialog);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 10, 580, 160));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        exportTypeComboBox = new QComboBox(verticalLayoutWidget);
        exportTypeComboBox->addItem(QString());
        exportTypeComboBox->addItem(QString());
        exportTypeComboBox->setObjectName("exportTypeComboBox");

        horizontalLayout->addWidget(exportTypeComboBox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        filePathEdit = new QLineEdit(verticalLayoutWidget);
        filePathEdit->setObjectName("filePathEdit");
        filePathEdit->setReadOnly(true);

        horizontalLayout_2->addWidget(filePathEdit);

        browseBtn = new QPushButton(verticalLayoutWidget);
        browseBtn->setObjectName("browseBtn");

        horizontalLayout_2->addWidget(browseBtn);


        verticalLayout->addLayout(horizontalLayout_2);

        buttonBox = new QDialogButtonBox(verticalLayoutWidget);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ExportDialog);

        QMetaObject::connectSlotsByName(ExportDialog);
    } // setupUi

    void retranslateUi(QDialog *ExportDialog)
    {
        ExportDialog->setWindowTitle(QCoreApplication::translate("ExportDialog", "\345\257\274\345\207\272\347\273\223\346\236\234", nullptr));
        label->setText(QCoreApplication::translate("ExportDialog", "\345\257\274\345\207\272\347\261\273\345\236\213\357\274\232", nullptr));
        exportTypeComboBox->setItemText(0, QCoreApplication::translate("ExportDialog", "Excel\346\226\207\344\273\266", nullptr));
        exportTypeComboBox->setItemText(1, QCoreApplication::translate("ExportDialog", "\345\233\276\347\211\207\346\226\207\344\273\266", nullptr));

        label_2->setText(QCoreApplication::translate("ExportDialog", "\344\277\235\345\255\230\350\267\257\345\276\204\357\274\232", nullptr));
        browseBtn->setText(QCoreApplication::translate("ExportDialog", "\346\265\217\350\247\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExportDialog: public Ui_ExportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPORTDIALOG_H
