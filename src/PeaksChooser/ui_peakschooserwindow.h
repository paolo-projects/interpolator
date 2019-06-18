/********************************************************************************
** Form generated from reading UI file 'peakschooserwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PEAKSCHOOSERWINDOW_H
#define UI_PEAKSCHOOSERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "paintablechartview.h"

QT_BEGIN_NAMESPACE

class Ui_PeaksChooserWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *spinBox;
    QSplitter *splitter;
    PaintableChartView *peaksChart;
    QTableWidget *peaksTable;
    QMenuBar *menubar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *PeaksChooserWindow)
    {
        if (PeaksChooserWindow->objectName().isEmpty())
            PeaksChooserWindow->setObjectName(QStringLiteral("PeaksChooserWindow"));
        PeaksChooserWindow->resize(800, 600);
        centralwidget = new QWidget(PeaksChooserWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        spinBox = new QSpinBox(widget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMinimum(1);
        spinBox->setMaximum(20);

        gridLayout->addWidget(spinBox, 0, 1, 1, 1);


        verticalLayout->addWidget(widget);

        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        peaksChart = new PaintableChartView(splitter);
        peaksChart->setObjectName(QStringLiteral("peaksChart"));
        peaksChart->setMinimumSize(QSize(788, 290));
        splitter->addWidget(peaksChart);
        peaksTable = new QTableWidget(splitter);
        peaksTable->setObjectName(QStringLiteral("peaksTable"));
        peaksTable->setContextMenuPolicy(Qt::CustomContextMenu);
        peaksTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        splitter->addWidget(peaksTable);

        verticalLayout->addWidget(splitter);

        PeaksChooserWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PeaksChooserWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 17));
        PeaksChooserWindow->setMenuBar(menubar);
        toolBar = new QToolBar(PeaksChooserWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        PeaksChooserWindow->addToolBar(Qt::BottomToolBarArea, toolBar);

        retranslateUi(PeaksChooserWindow);

        QMetaObject::connectSlotsByName(PeaksChooserWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PeaksChooserWindow)
    {
        PeaksChooserWindow->setWindowTitle(QApplication::translate("PeaksChooserWindow", "Peaks Chooser", Q_NULLPTR));
        label->setText(QApplication::translate("PeaksChooserWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Sensitivity</span>: 1 (high sensitivity) to 20 (low sensitivity)</p></body></html>", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("PeaksChooserWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PeaksChooserWindow: public Ui_PeaksChooserWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PEAKSCHOOSERWINDOW_H
