/********************************************************************************
** Form generated from reading UI file 'resultviewer.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULTVIEWER_H
#define UI_RESULTVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ResultViewer
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;

    void setupUi(QWidget *ResultViewer)
    {
        if (ResultViewer->objectName().isEmpty())
            ResultViewer->setObjectName("ResultViewer");
        ResultViewer->resize(800, 500);
        verticalLayoutWidget = new QWidget(ResultViewer);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 10, 780, 480));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);


        retranslateUi(ResultViewer);

        QMetaObject::connectSlotsByName(ResultViewer);
    } // setupUi

    void retranslateUi(QWidget *ResultViewer)
    {
        ResultViewer->setWindowTitle(QCoreApplication::translate("ResultViewer", "\347\273\223\346\236\234\346\237\245\347\234\213", nullptr));
        label->setText(QCoreApplication::translate("ResultViewer", "\345\272\247\344\275\215\345\210\206\351\205\215\347\273\223\346\236\234\345\260\206\346\230\276\347\244\272\345\234\250\350\277\231\351\207\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ResultViewer: public Ui_ResultViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTVIEWER_H
