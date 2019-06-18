/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QtCharts"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad;
    QAction *actionClear_Interpolation_Data;
    QAction *actionSelect_All;
    QAction *actionDelete_selected_from_interpolator;
    QAction *actionAbout;
    QAction *actionLoaded_Data_Plot_Image;
    QAction *actionInterpolated_Curve_Plot_Image;
    QAction *actionReverse_X_axis;
    QAction *actionReverse_X_axis_Interpolated_Curve;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_3;
    QTabWidget *tabWidget;
    QWidget *tab1;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLabel *label_6;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_4;
    QTableWidget *tableWidget;
    QPushButton *moveSelection;
    QTableWidget *tableWidget_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QComboBox *regOrderBox;
    QPushButton *calculateReg;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *equationEdit;
    QLabel *label_4;
    QLabel *rSquaredEdit;
    QSpacerItem *verticalSpacer_2;
    QTableWidget *interpolationTable;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QChartView *loadedDataPlot;
    QWidget *tab_2;
    QGridLayout *gridLayout_2;
    QChartView *dataChart;
    QWidget *tab_3;
    QGridLayout *gridLayout_4;
    QSplitter *splitter_2;
    QTableWidget *residualsTable;
    QChartView *residualsPlot;
    QWidget *tab_4;
    QGridLayout *gridLayout_5;
    QLabel *label_7;
    QSplitter *splitter_3;
    QTableWidget *dataTableWidget;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *addDataBtn;
    QPushButton *removeDataBtn;
    QPushButton *clearDataBtn;
    QPushButton *helpBtn;
    QPushButton *evaluateBtn;
    QLabel *label_8;
    QLineEdit *expressionEditText;
    QLabel *label_9;
    QLineEdit *resultEditText;
    QMenuBar *menuBar;
    QMenu *menuData_Parsers;
    QMenu *menuExport;
    QMenu *menuChart;
    QMenu *menu_Tools;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 800);
        MainWindow->setMinimumSize(QSize(800, 800));
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/Papirus/24x24/actions/document-open.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoad->setIcon(icon);
        actionClear_Interpolation_Data = new QAction(MainWindow);
        actionClear_Interpolation_Data->setObjectName(QStringLiteral("actionClear_Interpolation_Data"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/Papirus/24x24/actions/edit-clear-list.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionClear_Interpolation_Data->setIcon(icon1);
        actionSelect_All = new QAction(MainWindow);
        actionSelect_All->setObjectName(QStringLiteral("actionSelect_All"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/Papirus/24x24/actions/edit-select-all.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelect_All->setIcon(icon2);
        actionDelete_selected_from_interpolator = new QAction(MainWindow);
        actionDelete_selected_from_interpolator->setObjectName(QStringLiteral("actionDelete_selected_from_interpolator"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/Papirus/24x24/actions/edit-delete.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete_selected_from_interpolator->setIcon(icon3);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icons/Papirus/24x24/actions/help-about.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon4);
        actionLoaded_Data_Plot_Image = new QAction(MainWindow);
        actionLoaded_Data_Plot_Image->setObjectName(QStringLiteral("actionLoaded_Data_Plot_Image"));
        actionInterpolated_Curve_Plot_Image = new QAction(MainWindow);
        actionInterpolated_Curve_Plot_Image->setObjectName(QStringLiteral("actionInterpolated_Curve_Plot_Image"));
        actionReverse_X_axis = new QAction(MainWindow);
        actionReverse_X_axis->setObjectName(QStringLiteral("actionReverse_X_axis"));
        actionReverse_X_axis_Interpolated_Curve = new QAction(MainWindow);
        actionReverse_X_axis_Interpolated_Curve->setObjectName(QStringLiteral("actionReverse_X_axis_Interpolated_Curve"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_3 = new QHBoxLayout(centralWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabShape(QTabWidget::Rounded);
        tab1 = new QWidget();
        tab1->setObjectName(QStringLiteral("tab1"));
        gridLayout = new QGridLayout(tab1);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter = new QSplitter(tab1);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        widget = new QWidget(splitter);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_5);

        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_6);


        verticalLayout_2->addLayout(horizontalLayout_5);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        horizontalLayout_4 = new QHBoxLayout(widget_3);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        tableWidget = new QTableWidget(widget_3);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);

        horizontalLayout_4->addWidget(tableWidget);

        moveSelection = new QPushButton(widget_3);
        moveSelection->setObjectName(QStringLiteral("moveSelection"));
        moveSelection->setMinimumSize(QSize(36, 36));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icons/Papirus/24x24/actions/calendar-go-today.svg"), QSize(), QIcon::Normal, QIcon::Off);
        moveSelection->setIcon(icon5);
        moveSelection->setIconSize(QSize(36, 36));

        horizontalLayout_4->addWidget(moveSelection);

        tableWidget_2 = new QTableWidget(widget_3);
        tableWidget_2->setObjectName(QStringLiteral("tableWidget_2"));
        tableWidget_2->setContextMenuPolicy(Qt::CustomContextMenu);

        horizontalLayout_4->addWidget(tableWidget_2);


        verticalLayout_2->addWidget(widget_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(100, 20));

        horizontalLayout->addWidget(label);

        regOrderBox = new QComboBox(widget);
        regOrderBox->setObjectName(QStringLiteral("regOrderBox"));

        horizontalLayout->addWidget(regOrderBox);

        calculateReg = new QPushButton(widget);
        calculateReg->setObjectName(QStringLiteral("calculateReg"));

        horizontalLayout->addWidget(calculateReg);


        verticalLayout_2->addLayout(horizontalLayout);

        splitter->addWidget(widget);
        widget_2 = new QWidget(splitter);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMaximumSize(QSize(16777215, 250));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        equationEdit = new QLabel(widget_2);
        equationEdit->setObjectName(QStringLiteral("equationEdit"));
        equationEdit->setMinimumSize(QSize(0, 25));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        equationEdit->setFont(font1);
        equationEdit->setTextFormat(Qt::RichText);

        verticalLayout->addWidget(equationEdit);

        label_4 = new QLabel(widget_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        rSquaredEdit = new QLabel(widget_2);
        rSquaredEdit->setObjectName(QStringLiteral("rSquaredEdit"));
        rSquaredEdit->setMinimumSize(QSize(450, 25));
        rSquaredEdit->setFont(font1);
        rSquaredEdit->setTextFormat(Qt::RichText);

        verticalLayout->addWidget(rSquaredEdit);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout_2->addLayout(verticalLayout);

        interpolationTable = new QTableWidget(widget_2);
        interpolationTable->setObjectName(QStringLiteral("interpolationTable"));
        interpolationTable->setMinimumSize(QSize(300, 0));
        interpolationTable->setMaximumSize(QSize(500, 16777215));

        horizontalLayout_2->addWidget(interpolationTable);

        splitter->addWidget(widget_2);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        tabWidget->addTab(tab1, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        loadedDataPlot = new QChartView(tab);
        loadedDataPlot->setObjectName(QStringLiteral("loadedDataPlot"));
        loadedDataPlot->setContextMenuPolicy(Qt::DefaultContextMenu);

        gridLayout_3->addWidget(loadedDataPlot, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_2 = new QGridLayout(tab_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        dataChart = new QChartView(tab_2);
        dataChart->setObjectName(QStringLiteral("dataChart"));
        dataChart->setContextMenuPolicy(Qt::DefaultContextMenu);

        gridLayout_2->addWidget(dataChart, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayout_4 = new QGridLayout(tab_3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        splitter_2 = new QSplitter(tab_3);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        residualsTable = new QTableWidget(splitter_2);
        residualsTable->setObjectName(QStringLiteral("residualsTable"));
        splitter_2->addWidget(residualsTable);
        residualsPlot = new QChartView(splitter_2);
        residualsPlot->setObjectName(QStringLiteral("residualsPlot"));
        splitter_2->addWidget(residualsPlot);

        gridLayout_4->addWidget(splitter_2, 0, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        gridLayout_5 = new QGridLayout(tab_4);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        label_7 = new QLabel(tab_4);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_5->addWidget(label_7, 0, 0, 1, 1);

        splitter_3 = new QSplitter(tab_4);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setOrientation(Qt::Vertical);
        dataTableWidget = new QTableWidget(splitter_3);
        dataTableWidget->setObjectName(QStringLiteral("dataTableWidget"));
        dataTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        dataTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        splitter_3->addWidget(dataTableWidget);
        widget_4 = new QWidget(splitter_3);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_4->sizePolicy().hasHeightForWidth());
        widget_4->setSizePolicy(sizePolicy);
        widget_4->setMinimumSize(QSize(772, 200));
        verticalLayout_3 = new QVBoxLayout(widget_4);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox = new QGroupBox(widget_4);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        horizontalLayout_6 = new QHBoxLayout(groupBox);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        addDataBtn = new QPushButton(groupBox);
        addDataBtn->setObjectName(QStringLiteral("addDataBtn"));

        horizontalLayout_6->addWidget(addDataBtn);

        removeDataBtn = new QPushButton(groupBox);
        removeDataBtn->setObjectName(QStringLiteral("removeDataBtn"));

        horizontalLayout_6->addWidget(removeDataBtn);

        clearDataBtn = new QPushButton(groupBox);
        clearDataBtn->setObjectName(QStringLiteral("clearDataBtn"));

        horizontalLayout_6->addWidget(clearDataBtn);

        helpBtn = new QPushButton(groupBox);
        helpBtn->setObjectName(QStringLiteral("helpBtn"));

        horizontalLayout_6->addWidget(helpBtn);

        evaluateBtn = new QPushButton(groupBox);
        evaluateBtn->setObjectName(QStringLiteral("evaluateBtn"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(evaluateBtn->sizePolicy().hasHeightForWidth());
        evaluateBtn->setSizePolicy(sizePolicy2);

        horizontalLayout_6->addWidget(evaluateBtn);


        verticalLayout_3->addWidget(groupBox);

        label_8 = new QLabel(widget_4);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout_3->addWidget(label_8);

        expressionEditText = new QLineEdit(widget_4);
        expressionEditText->setObjectName(QStringLiteral("expressionEditText"));

        verticalLayout_3->addWidget(expressionEditText);

        label_9 = new QLabel(widget_4);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout_3->addWidget(label_9);

        resultEditText = new QLineEdit(widget_4);
        resultEditText->setObjectName(QStringLiteral("resultEditText"));
        resultEditText->setReadOnly(true);

        verticalLayout_3->addWidget(resultEditText);

        splitter_3->addWidget(widget_4);

        gridLayout_5->addWidget(splitter_3, 1, 0, 1, 1);

        tabWidget->addTab(tab_4, QString());

        horizontalLayout_3->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 17));
        menuData_Parsers = new QMenu(menuBar);
        menuData_Parsers->setObjectName(QStringLiteral("menuData_Parsers"));
        menuExport = new QMenu(menuBar);
        menuExport->setObjectName(QStringLiteral("menuExport"));
        menuChart = new QMenu(menuBar);
        menuChart->setObjectName(QStringLiteral("menuChart"));
        menu_Tools = new QMenu(menuBar);
        menu_Tools->setObjectName(QStringLiteral("menu_Tools"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::BottomToolBarArea, toolBar);

        menuBar->addAction(menuData_Parsers->menuAction());
        menuBar->addAction(menuExport->menuAction());
        menuBar->addAction(menuChart->menuAction());
        menuBar->addAction(menu_Tools->menuAction());
        menuExport->addAction(actionLoaded_Data_Plot_Image);
        menuExport->addAction(actionInterpolated_Curve_Plot_Image);
        menuChart->addAction(actionReverse_X_axis);
        menuChart->addAction(actionReverse_X_axis_Interpolated_Curve);
        mainToolBar->addAction(actionLoad);
        mainToolBar->addAction(actionAbout);
        toolBar->addAction(actionSelect_All);
        toolBar->addSeparator();
        toolBar->addAction(actionClear_Interpolation_Data);
        toolBar->addAction(actionDelete_selected_from_interpolator);
        toolBar->addSeparator();

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Interpolator", Q_NULLPTR));
        actionLoad->setText(QApplication::translate("MainWindow", "Load", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionLoad->setToolTip(QApplication::translate("MainWindow", "Load data from file", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionClear_Interpolation_Data->setText(QApplication::translate("MainWindow", "Clear Interpolation Data", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionClear_Interpolation_Data->setToolTip(QApplication::translate("MainWindow", "Clear interpolation table data", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionSelect_All->setText(QApplication::translate("MainWindow", "Select All", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSelect_All->setToolTip(QApplication::translate("MainWindow", "Select all rows in loaded data table", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionDelete_selected_from_interpolator->setText(QApplication::translate("MainWindow", "Delete selected from interpolator", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionDelete_selected_from_interpolator->setToolTip(QApplication::translate("MainWindow", "Delete selected rows from interpolator table", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionAbout->setText(QApplication::translate("MainWindow", "About", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionAbout->setToolTip(QApplication::translate("MainWindow", "About", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionLoaded_Data_Plot_Image->setText(QApplication::translate("MainWindow", "Loaded Data Plot Image", Q_NULLPTR));
        actionInterpolated_Curve_Plot_Image->setText(QApplication::translate("MainWindow", "Interpolated Curve Plot Image", Q_NULLPTR));
        actionReverse_X_axis->setText(QApplication::translate("MainWindow", "Reverse X axis (Loaded Data)", Q_NULLPTR));
        actionReverse_X_axis->setIconText(QApplication::translate("MainWindow", "Reverse X axis (Loaded Data)", Q_NULLPTR));
        actionReverse_X_axis_Interpolated_Curve->setText(QApplication::translate("MainWindow", "Reverse X axis (Interpolated Curve)", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Loaded Data", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "Data to fit", Q_NULLPTR));
        moveSelection->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Order", Q_NULLPTR));
        calculateReg->setText(QApplication::translate("MainWindow", "Calculate", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Fit results", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Equation", Q_NULLPTR));
        equationEdit->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "R<sup>2</sup>", Q_NULLPTR));
        rSquaredEdit->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab1), QApplication::translate("MainWindow", "Data", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Loaded Data Plot", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Interpolated Curve Plot", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Statistical analysis", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Data", Q_NULLPTR));
        groupBox->setTitle(QString());
        addDataBtn->setText(QApplication::translate("MainWindow", "+", Q_NULLPTR));
        removeDataBtn->setText(QApplication::translate("MainWindow", "-", Q_NULLPTR));
        clearDataBtn->setText(QApplication::translate("MainWindow", "x", Q_NULLPTR));
        helpBtn->setText(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
        evaluateBtn->setText(QApplication::translate("MainWindow", "Calculate", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Expression", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "Result", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "Evaluation", Q_NULLPTR));
        menuData_Parsers->setTitle(QApplication::translate("MainWindow", "Data &Parsers", Q_NULLPTR));
        menuExport->setTitle(QApplication::translate("MainWindow", "&Export", Q_NULLPTR));
        menuChart->setTitle(QApplication::translate("MainWindow", "&Chart", Q_NULLPTR));
        menu_Tools->setTitle(QApplication::translate("MainWindow", "&Tools", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
