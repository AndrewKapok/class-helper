/********************************************************************************
** Form generated from reading UI file 'algorithmconfigdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALGORITHMCONFIGDIALOG_H
#define UI_ALGORITHMCONFIGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AlgorithmConfigDialog
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *algorithmComboBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *rowsSpinBox;
    QLabel *label_3;
    QSpinBox *colsSpinBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AlgorithmConfigDialog)
    {
        if (AlgorithmConfigDialog->objectName().isEmpty())
            AlgorithmConfigDialog->setObjectName("AlgorithmConfigDialog");
        AlgorithmConfigDialog->resize(400, 200);
        verticalLayoutWidget = new QWidget(AlgorithmConfigDialog);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 10, 380, 180));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        algorithmComboBox = new QComboBox(verticalLayoutWidget);
        algorithmComboBox->addItem(QString());
        algorithmComboBox->addItem(QString());
        algorithmComboBox->setObjectName("algorithmComboBox");

        horizontalLayout->addWidget(algorithmComboBox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        rowsSpinBox = new QSpinBox(verticalLayoutWidget);
        rowsSpinBox->setObjectName("rowsSpinBox");
        rowsSpinBox->setMinimum(1);
        rowsSpinBox->setMaximum(20);
        rowsSpinBox->setValue(6);

        horizontalLayout_2->addWidget(rowsSpinBox);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName("label_3");

        horizontalLayout_2->addWidget(label_3);

        colsSpinBox = new QSpinBox(verticalLayoutWidget);
        colsSpinBox->setObjectName("colsSpinBox");
        colsSpinBox->setMinimum(1);
        colsSpinBox->setMaximum(20);
        colsSpinBox->setValue(8);

        horizontalLayout_2->addWidget(colsSpinBox);


        verticalLayout->addLayout(horizontalLayout_2);

        buttonBox = new QDialogButtonBox(verticalLayoutWidget);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(AlgorithmConfigDialog);

        QMetaObject::connectSlotsByName(AlgorithmConfigDialog);
    } // setupUi

    void retranslateUi(QDialog *AlgorithmConfigDialog)
    {
        AlgorithmConfigDialog->setWindowTitle(QCoreApplication::translate("AlgorithmConfigDialog", "\347\256\227\346\263\225\351\205\215\347\275\256", nullptr));
        label->setText(QCoreApplication::translate("AlgorithmConfigDialog", "\345\210\206\351\205\215\347\256\227\346\263\225\357\274\232", nullptr));
        algorithmComboBox->setItemText(0, QCoreApplication::translate("AlgorithmConfigDialog", "\345\210\206\346\225\260\345\210\206\345\261\202", nullptr));
        algorithmComboBox->setItemText(1, QCoreApplication::translate("AlgorithmConfigDialog", "\345\235\207\345\214\200\345\210\206\347\273\204", nullptr));

        label_2->setText(QCoreApplication::translate("AlgorithmConfigDialog", "\350\241\214\346\225\260\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("AlgorithmConfigDialog", "\345\210\227\346\225\260\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AlgorithmConfigDialog: public Ui_AlgorithmConfigDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALGORITHMCONFIGDIALOG_H
