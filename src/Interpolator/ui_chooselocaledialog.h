/********************************************************************************
** Form generated from reading UI file 'chooselocaledialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSELOCALEDIALOG_H
#define UI_CHOOSELOCALEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChooseLocaleDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *localeComboBox;
    QLineEdit *customLocaleEditText;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ChooseLocaleDialog)
    {
        if (ChooseLocaleDialog->objectName().isEmpty())
            ChooseLocaleDialog->setObjectName(QStringLiteral("ChooseLocaleDialog"));
        ChooseLocaleDialog->resize(464, 170);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ChooseLocaleDialog->sizePolicy().hasHeightForWidth());
        ChooseLocaleDialog->setSizePolicy(sizePolicy);
        ChooseLocaleDialog->setMinimumSize(QSize(464, 170));
        ChooseLocaleDialog->setMaximumSize(QSize(16777215, 16777215));
        ChooseLocaleDialog->setModal(true);
        verticalLayout_2 = new QVBoxLayout(ChooseLocaleDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        widget = new QWidget(ChooseLocaleDialog);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(16777215, 30));

        verticalLayout->addWidget(label);

        localeComboBox = new QComboBox(widget);
        localeComboBox->setObjectName(QStringLiteral("localeComboBox"));

        verticalLayout->addWidget(localeComboBox);

        customLocaleEditText = new QLineEdit(widget);
        customLocaleEditText->setObjectName(QStringLiteral("customLocaleEditText"));
        customLocaleEditText->setReadOnly(true);

        verticalLayout->addWidget(customLocaleEditText);


        verticalLayout_2->addWidget(widget);

        buttonBox = new QDialogButtonBox(ChooseLocaleDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(ChooseLocaleDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ChooseLocaleDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ChooseLocaleDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ChooseLocaleDialog);
    } // setupUi

    void retranslateUi(QDialog *ChooseLocaleDialog)
    {
        ChooseLocaleDialog->setWindowTitle(QApplication::translate("ChooseLocaleDialog", "Locale", Q_NULLPTR));
        label->setText(QApplication::translate("ChooseLocaleDialog", "Select the imported file locale:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ChooseLocaleDialog: public Ui_ChooseLocaleDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSELOCALEDIALOG_H
