/********************************************************************************
** Form generated from reading UI file 'aboutbox.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTBOX_H
#define UI_ABOUTBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_AboutBox
{
public:
    QTextEdit *textEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QDialog *AboutBox)
    {
        if (AboutBox->objectName().isEmpty())
            AboutBox->setObjectName(QStringLiteral("AboutBox"));
        AboutBox->resize(500, 300);
        AboutBox->setMinimumSize(QSize(500, 300));
        AboutBox->setMaximumSize(QSize(500, 300));
        textEdit = new QTextEdit(AboutBox);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(10, 10, 481, 211));
        textEdit->setReadOnly(true);
        pushButton = new QPushButton(AboutBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(400, 250, 91, 31));
        pushButton_2 = new QPushButton(AboutBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(10, 230, 131, 51));
        pushButton_2->setMinimumSize(QSize(100, 35));
        pushButton_2->setIconSize(QSize(88, 31));
        pushButton_3 = new QPushButton(AboutBox);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(150, 230, 181, 51));
        pushButton_3->setMinimumSize(QSize(100, 35));
        pushButton_3->setIconSize(QSize(88, 31));

        retranslateUi(AboutBox);

        QMetaObject::connectSlotsByName(AboutBox);
    } // setupUi

    void retranslateUi(QDialog *AboutBox)
    {
        AboutBox->setWindowTitle(QApplication::translate("AboutBox", "Info", Q_NULLPTR));
        textEdit->setHtml(QApplication::translate("AboutBox", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8.25pt;\">This software has been created by Paolo Infante for educational purposes.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8.25pt;\">You're free to use it as you will, for commercial/personal/education purposes, you're free to contribute to the project and to use the source code for a derivative work as long as you comply with GNU GPLv3 license.</span></p></body></html>", Q_NULLPTR));
        pushButton->setText(QApplication::translate("AboutBox", "OK", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("AboutBox", "License", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("AboutBox", "Project page", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AboutBox: public Ui_AboutBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTBOX_H
