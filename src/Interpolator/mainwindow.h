#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenu>
#include <QClipboard>
#include <QtCharts>
#include <QApplication>

#include <fstream>
#include <vector>
#include <regex>
#include <set>
#include <sstream>
#include <map>
#include <array>
#include <stdexcept>

//#include "glsfit.h"
#include "polyfit.h"
#include "aboutbox.h"
#include "datafileparserinterface.h"
#include "dataplugininterface.h"
#include "charteventfilter.h"
#include "chooselocaledialog.h"

#define PLUGINSEL_PREFERENCE "preference.selectedplugin"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_actionLoad_triggered();
    void table_cell_selection_changed();
    void int_table_cell_selection_changed();

    void on_actionClear_Interpolation_Data_triggered();

    void on_actionSelect_All_triggered();

    void on_actionDelete_selected_from_interpolator_triggered();

    void on_calculateReg_clicked();

    void customMenuRequestedTableLeft(const QPoint& pos);
    void customMenuRequestedTableRight(const QPoint& pos);
    void customMenuRequestedChart(const QPoint& pos);
    void customMenuRequestedDataPlot(const QPoint& pos);
    void customMenuRequestedEvTable(const QPoint& pos);

    void exportChartImage();
    void exportDataPlotImage();

    void menuCopyLeft();
    void menuCopyRight();
    void menuPasteRight();

    void menuEvTableCopy();
    void menuEvTablePaste();
    void menuEvTableExportAsTabDel();
    void menuEvTableImportTabDel();

    void on_moveSelection_clicked();

    void on_actionAbout_triggered();

    void selectParserInterface(int index);
    void startPluginInterface(int index);

    void on_actionLoaded_Data_Plot_Image_triggered();

    void on_actionInterpolated_Curve_Plot_Image_triggered();

    void on_actionReverse_X_axis_triggered();

    void on_actionReverse_X_axis_Interpolated_Curve_triggered();

    void on_addDataBtn_clicked();

    void on_removeDataBtn_clicked();

    void on_clearDataBtn_clicked();

    void on_evaluateBtn_clicked();

    void on_helpBtn_clicked();

private:
    Ui::MainWindow *ui;

    std::regex peaksRegex;
    QMenu* contextMenuLeft;
    QMenu* contextMenuRight;
    QMenu* contextMenuChart;
    QMenu* contextMenuDataPlot;
    QMenu* contextMenuEvaluationTable;

    std::vector<ParserInterface*> parserInterfaces;
    std::vector<DataPluginInterface*> pluginInterfaces;
    ParserInterface* selectedParserInterface = nullptr;
    QSettings settings;

    std::vector<double> loadedXData, loadedYData;

    void loadPlugins();
    void loadDataToolsPlugins();

    QString pythonExe = "";
};

#endif // MAINWINDOW_H
