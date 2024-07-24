/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *label;
    QLineEdit *ipLineEdit;
    QLineEdit *portLineEdit;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *dataLineEdit;
    QLabel *label_4;
    QPushButton *saveButton;
    QPushButton *connectButton;
    QLabel *wifi;
    QPushButton *photoButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1444, 801);
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(740, 20, 251, 71));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(20);
        font.setBold(false);
        font.setWeight(50);
        label->setFont(font);
        ipLineEdit = new QLineEdit(Widget);
        ipLineEdit->setObjectName(QString::fromUtf8("ipLineEdit"));
        ipLineEdit->setGeometry(QRect(570, 110, 113, 21));
        portLineEdit = new QLineEdit(Widget);
        portLineEdit->setObjectName(QString::fromUtf8("portLineEdit"));
        portLineEdit->setGeometry(QRect(380, 110, 61, 21));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(470, 110, 81, 16));
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(290, 110, 81, 16));
        dataLineEdit = new QLineEdit(Widget);
        dataLineEdit->setObjectName(QString::fromUtf8("dataLineEdit"));
        dataLineEdit->setGeometry(QRect(820, 110, 181, 21));
        label_4 = new QLabel(Widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(730, 110, 71, 16));
        saveButton = new QPushButton(Widget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(1020, 110, 93, 28));
        connectButton = new QPushButton(Widget);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));
        connectButton->setGeometry(QRect(1020, 70, 93, 28));
        wifi = new QLabel(Widget);
        wifi->setObjectName(QString::fromUtf8("wifi"));
        wifi->setGeometry(QRect(90, 70, 50, 50));
        wifi->setMinimumSize(QSize(50, 50));
        wifi->setMaximumSize(QSize(50, 50));
        photoButton = new QPushButton(Widget);
        photoButton->setObjectName(QString::fromUtf8("photoButton"));
        photoButton->setGeometry(QRect(1020, 30, 93, 28));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\346\225\260\346\215\256\346\216\245\346\224\266\346\234\215\345\212\241\345\231\250", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\345\256\242\346\210\267\347\253\257\345\234\260\345\235\200", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "\345\256\242\346\210\267\347\253\257\347\253\257\345\217\243", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "\345\205\211\350\260\261\346\225\260\346\215\256", nullptr));
        saveButton->setText(QCoreApplication::translate("Widget", "\344\277\235\345\255\230\346\225\260\346\215\256", nullptr));
        connectButton->setText(QCoreApplication::translate("Widget", "\345\201\234\346\255\242\346\221\204\345\203\217", nullptr));
        wifi->setText(QCoreApplication::translate("Widget", "TextLabel", nullptr));
        photoButton->setText(QCoreApplication::translate("Widget", "\345\274\200\345\247\213\346\221\204\345\203\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
