#include "mainwindow.h"
#include "ui_mainwindow.h"

#define DEBUG true

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    peaksRegex("Position:\\D*([\\d\\.]+)\\D*Intensity:\\D*([\\d\\.]+)", std::regex::icase)
{
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    ui->setupUi(this);

    ui->statusBar->showMessage("by Paolo Infante. Licensed under CC BY-SA 4.0");

    ui->moveSelection->setEnabled(false);

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels({"X","Y"});
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    connect(ui->tableWidget, SIGNAL(itemSelectionChanged()), this, SLOT(table_cell_selection_changed()));
    ui->moveSelection->setEnabled(false);

    ui->tableWidget_2->setColumnCount(2);
    ui->tableWidget_2->setHorizontalHeaderLabels({"X","Y"});
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView::MultiSelection);
    connect(ui->tableWidget_2, SIGNAL(itemSelectionChanged()), this, SLOT(int_table_cell_selection_changed()));
    ui->actionDelete_selected_from_interpolator->setEnabled(false);

    ui->regOrderBox->addItems({"1","2","3","4"});

    connect(ui->tableWidget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(customMenuRequestedTableLeft(const QPoint&)));
    connect(ui->tableWidget_2, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(customMenuRequestedTableRight(const QPoint&)));
    connect(ui->dataChart, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(customMenuRequestedChart(const QPoint&)));
    connect(ui->loadedDataPlot, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(customMenuRequestedDataPlot(const QPoint&)));
    connect(ui->dataTableWidget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(customMenuRequestedEvTable(const QPoint&)));

    contextMenuLeft = new QMenu(ui->tableWidget);
    contextMenuRight = new QMenu(ui->tableWidget_2);
    contextMenuChart = new QMenu(ui->dataChart);
    contextMenuDataPlot = new QMenu(ui->loadedDataPlot);
    contextMenuEvaluationTable = new QMenu(ui->dataTableWidget);

    contextMenuLeft->addAction("Copy", this, SLOT(menuCopyLeft()));
    contextMenuRight->addAction("Copy", this, SLOT(menuCopyRight()));
    contextMenuRight->addAction("Paste", this, SLOT(menuPasteRight()));
    contextMenuChart->addAction("Export image", this, SLOT(exportChartImage()));
    contextMenuDataPlot->addAction("Export image", this, SLOT(exportDataPlotImage()));

    contextMenuEvaluationTable->addAction("&Copy", this, SLOT(menuEvTableCopy()));
    contextMenuEvaluationTable->addAction("&Paste", this, SLOT(menuEvTablePaste()));
    contextMenuEvaluationTable->addAction("&Export as TAB delimited text file", this, SLOT(menuEvTableExportAsTabDel()));
    contextMenuEvaluationTable->addAction("&Import TAB delimited text file", this, SLOT(menuEvTableImportTabDel()));

    ui->equationEdit->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui->rSquaredEdit->setTextInteractionFlags(Qt::TextSelectableByMouse);

    ui->dataChart->setRubberBand(QChartView::RectangleRubberBand);
    auto evFilter1 = new ChartEventFilter(this);
    ui->dataChart->installEventFilter(evFilter1);

    auto evFilter2 = new ChartEventFilter(this);
    ui->loadedDataPlot->installEventFilter(evFilter2);
    ui->loadedDataPlot->setRubberBand(QChartView::RectangleRubberBand);

    auto evFilter3 = new ChartEventFilter(this);
    ui->residualsPlot->installEventFilter(evFilter3);
    ui->residualsPlot->setRubberBand(QChartView::RectangleRubberBand);

    loadPlugins();

    if(parserInterfaces.size()>0)
    {
        QMenu* menu = ui->menuBar->findChildren<QMenu*>("menuData_Parsers").at(0);
        QActionGroup* actionGroup = new QActionGroup(menu);
        bool firstChecked = false;
        int index = 0;
        for(ParserInterface* pInt : parserInterfaces)
        {
            auto action = menu->addAction(pInt->getDisplayName(), this, [this, index](){selectParserInterface(index);});
            actionGroup->addAction(action);
            action->setCheckable(true);
            /*if(!firstChecked)
            {
                action->setChecked(true);
                firstChecked = true;
            }*/
            index++;
        }

        actionGroup->setExclusive(true);

        int selPlugin = settings.value(PLUGINSEL_PREFERENCE, 0).toInt();
        if(selPlugin >= parserInterfaces.size())
            selPlugin = 0;
        selectedParserInterface = parserInterfaces.at(selPlugin);
        menu->actions().at(selPlugin)->setChecked(true);
        //connect(actionGroup, SIGNAL(triggered()), actionGroup, SLOT(onTriggered()));
    } else
    {
        int selPlugin = settings.value(PLUGINSEL_PREFERENCE, 0).toInt();
        if(!DEBUG)
        {
            QMessageBox::critical(this, "Error", "Couldn't find any parser plugin. Quitting");
            exit(-1);
        }
    }

    loadDataToolsPlugins();

    if(pluginInterfaces.size()>0)
    {
        QMenu* menu = ui->menuBar->findChildren<QMenu*>("menu_Tools").at(0);

        int index = 0;
        for(DataPluginInterface* pInt : pluginInterfaces)
        {
            auto action = menu->addAction(pInt->getName(), this, [this, index](){startPluginInterface(index);});

            index++;
        }
    }

    /* Evaluation Tab */
    ui->dataTableWidget->setColumnCount(2);
    ui->dataTableWidget->setHorizontalHeaderLabels(QStringList{"Variable", "Value (error separated by +- signs)"});
    ui->dataTableWidget->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::selectParserInterface(int index)
{
    selectedParserInterface = parserInterfaces.at(index);
    settings.setValue(PLUGINSEL_PREFERENCE, index);
}

void MainWindow::startPluginInterface(int index)
{
    pluginInterfaces.at(index)->invoke(loadedXData, loadedYData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadPlugins()
{
    QDir pluginsDir(qApp->applicationDirPath());
    #if defined(Q_OS_WIN)
        if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
            pluginsDir.cdUp();
    #elif defined(Q_OS_MAC)
        if (pluginsDir.dirName() == "MacOS") {
            pluginsDir.cdUp();
            pluginsDir.cdUp();
            pluginsDir.cdUp();
        }
    #endif
        pluginsDir.cd("plugins");
        foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
            QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
            QObject *plugin = pluginLoader.instance();
            if (plugin) {
                ParserInterface* parserInterface = qobject_cast<ParserInterface *>(plugin);
                if (parserInterface)
                    parserInterfaces.emplace_back(parserInterface);
            }
        }
}

void MainWindow::loadDataToolsPlugins()
{
    QDir pluginsDir(qApp->applicationDirPath());
    #if defined(Q_OS_WIN)
        if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
            pluginsDir.cdUp();
    #elif defined(Q_OS_MAC)
        if (pluginsDir.dirName() == "MacOS") {
            pluginsDir.cdUp();
            pluginsDir.cdUp();
            pluginsDir.cdUp();
        }
    #endif
        pluginsDir.cd("plugins");
        foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
            QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
            QObject *plugin = pluginLoader.instance();
            if (plugin) {
                DataPluginInterface* pluginInterface = qobject_cast<DataPluginInterface *>(plugin);
                if (pluginInterface)
                    pluginInterfaces.emplace_back(pluginInterface);
            }
        }
}

void MainWindow::on_actionLoad_triggered()
{
    using namespace std;

    if(selectedParserInterface!=nullptr)
    {
        ChooseLocaleDialog clDialog(this);
        if(clDialog.exec())
        {
            QString locale = clDialog.getChoosenLocale();
            QString fileName = QFileDialog::getOpenFileName(this, "Load data", "", selectedParserInterface->getFileFilter()+";;All files (*.*)");
            if(fileName.length() > 0) {
                selectedParserInterface->setLocale(locale.toStdString());
                ParsedData data = selectedParserInterface->fromFileName(fileName);

                if(data.xData.size()>0 && data.xData.size() == data.yData.size() ) {
                    loadedXData = data.xData;
                    loadedYData = data.yData;

                    ui->tableWidget->clear();
                    ui->tableWidget->clearSelection();
                    ui->tableWidget->setColumnCount(2);
                    ui->tableWidget->setHorizontalHeaderLabels({"X","Y"});
                    ui->tableWidget->setRowCount(data.xData.size());
                    for(size_t i = 0; i < data.xData.size(); i++)
                    {
                        QTableWidgetItem* xVal = new QTableWidgetItem(QString::number(data.xData.at(i)));
                        QTableWidgetItem* yVal = new QTableWidgetItem(QString::number(data.yData.at(i)));
                        ui->tableWidget->setItem(i, 0, xVal);
                        ui->tableWidget->setItem(i, 1, yVal);
                    }
                }

                // Produce Chart
                ui->loadedDataPlot->chart()->removeAllSeries();

                QLineSeries* experimentalSeries = new QLineSeries();
                for(int i = 0; i < data.xData.size(); i++)
                {
                    experimentalSeries->append(data.xData.at(i), data.yData.at(i));
                }

                experimentalSeries->setColor(QColor(Qt::GlobalColor::blue));
                experimentalSeries->setName("Loaded Data");
                experimentalSeries->setUseOpenGL(true);

                ui->loadedDataPlot->chart()->addSeries(experimentalSeries);
                ui->loadedDataPlot->chart()->createDefaultAxes();
                ui->loadedDataPlot->setRenderHint(QPainter::Antialiasing);
            }
        }
    }
}

void MainWindow::table_cell_selection_changed()
{
    if(ui->tableWidget->selectedItems().size()>0)
        ui->moveSelection->setEnabled(true);
    else {
        ui->moveSelection->setEnabled(false);
    }
}

void MainWindow::on_actionClear_Interpolation_Data_triggered()
{
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setColumnCount(2);
    ui->tableWidget_2->setRowCount(0);
    ui->tableWidget_2->setHorizontalHeaderLabels({"X","Y"});
}

void MainWindow::on_actionSelect_All_triggered()
{
    if(ui->tableWidget->selectedItems().size()>0)
        ui->tableWidget->clearSelection();
    else
        ui->tableWidget->selectAll();
}

void MainWindow::int_table_cell_selection_changed()
{
    if(ui->tableWidget_2->selectedItems().size()>0)
        ui->actionDelete_selected_from_interpolator->setEnabled(true);
    else {
        ui->actionDelete_selected_from_interpolator->setEnabled(false);
    }
}

void MainWindow::on_actionDelete_selected_from_interpolator_triggered()
{
    auto selItems = ui->tableWidget_2->selectedItems();
    std::set<int, std::greater<int>> toRemove;
    for(auto el : selItems) {
        toRemove.insert(el->row());
    }
    for(auto index = toRemove.begin(); index != toRemove.end(); index++) {
        ui->tableWidget_2->removeRow(*index);
    }
}

template<typename T>
double getAbsMaxIn(std::vector<T> values)
{
    double maxval = 0.0;
    for(T val : values)
    {
        T curval = std::abs(val);
        if(curval>maxval)
            maxval = curval;
    }
    return maxval;
}

void MainWindow::on_calculateReg_clicked()
{
    if(ui->tableWidget_2->rowCount()>1) {
        int order = ui->regOrderBox->currentText().toInt();

        std::vector<double> regXData, regYData;
        for(int i = 0; i < ui->tableWidget_2->rowCount(); i++) {
            regXData.emplace_back(std::stod(ui->tableWidget_2->item(i, 0)->text().toStdString()));
            regYData.emplace_back(std::stod(ui->tableWidget_2->item(i, 1)->text().toStdString()));
        }

        PolyFit<double> out(regXData, regYData, order);

        QTableWidget* intTbl = ui->interpolationTable;
        intTbl->clear();
        intTbl->setColumnCount(2);
        intTbl->setRowCount(out.getCoefficients().size());
        intTbl->setHorizontalHeaderLabels({"X Order", "Coefficient"});
        QString equation = "";
        for (int n = 0;n < out.getCoefficients().size(); n++) {
            intTbl->setItem(n, 0, new QTableWidgetItem(QString::number(n)));
            intTbl->setItem(n, 1, new QTableWidgetItem(QString::number(out.getCoefficients().at(n))));
            if(n==0)
                equation += QString::number(out.getCoefficients().at(n))+" ";
            else if(n==1) {
                char sign = (out.getCoefficients().at(n)>=0)?'+':' ';
                equation += sign+QString::number(out.getCoefficients().at(n)) + " x ";
            } else {
                char sign = (out.getCoefficients().at(n)>=0)?'+':' ';
                equation += sign+QString::number(out.getCoefficients().at(n)) + " x<sup>"+QString::number(n)+"</sup> ";
            }
        }

        ui->equationEdit->setText(equation.trimmed());

        ui->rSquaredEdit->setText(QString::number(out.getParameters().RSquared));

        // Produce chart
        ui->dataChart->chart()->removeAllSeries();

        QLineSeries* experimentalSeries = new QLineSeries();
        QLineSeries* fitSeries = new QLineSeries();
        for(int i = 0; i < regXData.size(); i++)
        {
            experimentalSeries->append(regXData.at(i), regYData.at(i));
            fitSeries->append(regXData.at(i), out.estimate(regXData.at(i)));
        }

        experimentalSeries->setColor(QColor(Qt::GlobalColor::blue));
        experimentalSeries->setName("Experimental");
        experimentalSeries->setUseOpenGL(true);

        fitSeries->setColor(QColor(Qt::GlobalColor::red));
        fitSeries->setName("Extimated");
        fitSeries->setUseOpenGL(true);

        ui->dataChart->chart()->addSeries(experimentalSeries);
        ui->dataChart->chart()->addSeries(fitSeries);
        ui->dataChart->chart()->createDefaultAxes();
        ui->dataChart->setRenderHint(QPainter::Antialiasing);

        // Compute and show residuals

        ui->residualsTable->clear();
        ui->residualsTable->setColumnCount(2);
        ui->residualsTable->setRowCount(regXData.size());

        ui->residualsPlot->chart()->removeAllSeries();

        QLineSeries* residualsSeries = new QLineSeries();

        std::vector<double> residuals;
        residuals.reserve(regXData.size());

        for(int c = 0; c < regYData.size(); c++)
        {
            double yVal = regYData.at(c);
            double residual = yVal-out.estimate(regXData.at(c));
            ui->residualsTable->setItem(c, 0, new QTableWidgetItem(QString::number(yVal)));
            ui->residualsTable->setItem(c, 1, new QTableWidgetItem(QString::number(residual)));
            residualsSeries->append(yVal, residual);
            residuals.emplace_back(residual);
        }

        residualsSeries->setColor(QColor(Qt::GlobalColor::blue));
        residualsSeries->setName("Residuals");
        residualsSeries->setUseOpenGL(true);

        ui->residualsPlot->chart()->addSeries(residualsSeries);
        ui->residualsPlot->chart()->createDefaultAxes();
        double yRange = getAbsMaxIn(residuals);
        ui->residualsPlot->chart()->axisY()->setMax(yRange);
        ui->residualsPlot->chart()->axisY()->setMin(-yRange);
        ui->residualsPlot->setRenderHint(QPainter::Antialiasing);
    }
}

void MainWindow::customMenuRequestedTableLeft(const QPoint& pos) {
    contextMenuLeft->exec(ui->tableWidget->mapToGlobal(pos));
}

void MainWindow::customMenuRequestedTableRight(const QPoint& pos) {
    contextMenuRight->exec(ui->tableWidget_2->mapToGlobal(pos));
}

void MainWindow::menuCopyLeft() {
    if(ui->tableWidget->selectedItems().size()>0) {
        QString clipboardText = "";
        int colIndex = 0;
        for(auto item : ui->tableWidget->selectedItems()) {
            clipboardText += item->text();
            if(colIndex == 0) {
                clipboardText += "\t";
                colIndex++;
            } else {
                clipboardText += "\n";
                colIndex = 0;
            }
        }
        QClipboard* clipbrd = QApplication::clipboard();
        clipbrd->setText(clipboardText);
    }
}

void MainWindow::menuCopyRight() {
    if(ui->tableWidget_2->selectedItems().size()>0) {
        QString clipboardText = "";
        int colIndex = 0;
        for(auto item : ui->tableWidget_2->selectedItems()) {
            clipboardText += item->text();
            if(colIndex == 0) {
                clipboardText += "\t";
                colIndex++;
            } else {
                clipboardText += "\n";
                colIndex = 0;
            }
        }
        QClipboard* clipbrd = QApplication::clipboard();
        clipbrd->setText(clipboardText);
    }
}

void MainWindow::menuPasteRight() {
    QClipboard* clipbrd = QApplication::clipboard();
    QString clipBrdText = clipbrd->text();
    if(clipBrdText.length()>0) {
        QStringList rows = clipBrdText.split("\n");
        if(rows.last().length() == 0)
            rows.removeLast();
        if(rows.size()>0) {
            int prevRows = ui->tableWidget_2->rowCount();
            int selRows = rows.size();
            int currRow = prevRows;
            ui->tableWidget_2->setRowCount(prevRows+selRows);
            for(QString elem : rows) {
                QStringList cols = elem.split("\t");
                if(cols.size()>1) {
                    QTableWidgetItem* newItem0 = new QTableWidgetItem(cols.at(0));
                    QTableWidgetItem* newItem1 = new QTableWidgetItem(cols.at(1));
                    ui->tableWidget_2->setItem(currRow, 0, newItem0);
                    ui->tableWidget_2->setItem(currRow, 1, newItem1);
                    currRow++;
                }
            }
        }
    }
}

void MainWindow::on_moveSelection_clicked()
{
    int prevRows = ui->tableWidget_2->rowCount();
    int selRows = ui->tableWidget->selectedItems().size()/2;
/*    int currRow = prevRows;
    //int currCol = 0;
 REPLACE WITH MAP
    for(auto item : ui->tableWidget->selectedItems()) {
        QTableWidgetItem* newItem = new QTableWidgetItem(item->text());
        ui->tableWidget_2->setItem(currRow, currCol, newItem);
        if(currCol == 0)
            currCol++;
        else {
            currCol = 0;
            currRow++;
        }
    }*/
    std::map<float, float> data;
    for(int i = 0; i < ui->tableWidget_2->rowCount(); i++) {
        data[ui->tableWidget_2->item(i, 0)->text().toFloat()] = ui->tableWidget_2->item(i, 1)->text().toFloat();
    }
    QItemSelectionModel *select = ui->tableWidget->selectionModel();

    for(auto index : select->selectedRows()) {
        float xVal = ui->tableWidget->item(index.row(), 0)->text().toFloat();
        float yVal = ui->tableWidget->item(index.row(), 1)->text().toFloat();;
        data[xVal] = yVal;
    }

    ui->tableWidget_2->setRowCount(prevRows+selRows);

    int currRow = 0;
    for(auto element : data)
    {
        ui->tableWidget_2->setItem(currRow, 0, new QTableWidgetItem(QString::number(element.first)));
        ui->tableWidget_2->setItem(currRow, 1, new QTableWidgetItem(QString::number(element.second)));
        currRow++;
    }
}

void MainWindow::on_actionAbout_triggered()
{
    AboutBox* about = new AboutBox(this);
    about->show();
}

void MainWindow::customMenuRequestedChart(const QPoint& pos)
{
    contextMenuChart->exec(ui->dataChart->mapToGlobal(pos));
}

void MainWindow::customMenuRequestedDataPlot(const QPoint& pos)
{
    contextMenuDataPlot->exec(ui->loadedDataPlot->mapToGlobal(pos));
}

void MainWindow::exportChartImage()
{
    QString outFile = QFileDialog::getSaveFileName(this, "Choose the output file", "", "PNG Image(*.png)");
    if(outFile.length()>0)
    {
        /*QPixmap chartImg(ui->dataChart->size());
        QPainter painter(&chartImg);
        ui->dataChart->render(&painter);
        chartImg.save(outFile, "PNG", 100);*/
        QPixmap p = ui->dataChart->grab();
        QPainter painter(&p);

        QLabel renderText;
        renderText.setTextFormat(Qt::TextFormat::RichText);
        renderText.setText(ui->equationEdit->text());
        renderText.setStyleSheet("QLabel { background-color : transparent }");
        renderText.render(&painter, QPoint(20, 20));

        QLabel rsqText;
        rsqText.setTextFormat(Qt::TextFormat::RichText);
        rsqText.setText("R<sup>2</sup>: "+ui->rSquaredEdit->text());
        rsqText.setStyleSheet("QLabel { background-color : transparent }");
        rsqText.render(&painter, QPoint(p.width()-150, 20));

        QLabel authorText;
        authorText.setTextFormat(Qt::TextFormat::RichText);
        authorText.setText("<span style='font-size: 10px'>gitlab.com/infante.paolo/interpolator</span>");
        authorText.setStyleSheet("QLabel { background-color : transparent }");
        authorText.render(&painter, QPoint(p.width()-200, p.height()-20));

        p.save(outFile, "PNG", 100);
    }
}

void MainWindow::exportDataPlotImage()
{
    QString outFile = QFileDialog::getSaveFileName(this, "Choose the output file", "", "PNG Image(*.png)");
    if(outFile.length()>0)
    {
        /*QPixmap chartImg(ui->dataChart->size());
        QPainter painter(&chartImg);
        ui->dataChart->render(&painter);
        chartImg.save(outFile, "PNG", 100);*/
        QPixmap p = ui->loadedDataPlot->grab();
        QPainter painter(&p);

        QLabel authorText;
        authorText.setTextFormat(Qt::TextFormat::RichText);
        authorText.setText("<span style='font-size: 10px'>gitlab.com/infante.paolo/interpolator</span>");
        authorText.setStyleSheet("QLabel { background-color : transparent }");
        authorText.render(&painter, QPoint(p.width()-200, p.height()-20));

        p.save(outFile, "PNG", 100);
    }
}

void MainWindow::on_actionLoaded_Data_Plot_Image_triggered()
{
    exportDataPlotImage();
}

void MainWindow::on_actionInterpolated_Curve_Plot_Image_triggered()
{
    exportChartImage();
}

void MainWindow::on_actionReverse_X_axis_triggered()
{
    if(ui->loadedDataPlot->chart()->axisX() != nullptr)
        ui->loadedDataPlot->chart()->axisX()->setReverse(!ui->loadedDataPlot->chart()->axisX()->isReverse());
}

void MainWindow::on_actionReverse_X_axis_Interpolated_Curve_triggered()
{
    if(ui->dataChart->chart()->axisX() != nullptr)
        ui->dataChart->chart()->axisX()->setReverse(!ui->dataChart->chart()->axisX()->isReverse());
}

void MainWindow::on_addDataBtn_clicked()
{
    QTableWidgetItem* item = new QTableWidgetItem("");
    item->setFlags(item->flags() | Qt::ItemIsEditable);

    QTableWidgetItem* item2 = new QTableWidgetItem("");
    item2->setFlags(item->flags() | Qt::ItemIsEditable);

    int rows = ui->dataTableWidget->rowCount();

    ui->dataTableWidget->setRowCount(rows+1);
    ui->dataTableWidget->setItem(rows, 0, item);
    ui->dataTableWidget->setItem(rows, 1, item2);
}

void MainWindow::on_removeDataBtn_clicked()
{
    auto selItems = ui->dataTableWidget->selectedItems();
    std::set<int, std::greater<int>> toRemove;
    for(auto el : selItems) {
        toRemove.insert(el->row());
    }
    for(auto index = toRemove.begin(); index != toRemove.end(); index++) {
        ui->dataTableWidget->removeRow(*index);
    }
}

void MainWindow::on_clearDataBtn_clicked()
{
    ui->dataTableWidget->clearContents();
    ui->dataTableWidget->setRowCount(0);
    /*
    ui->dataTableWidget->setColumnCount(2);
    ui->dataTableWidget->setHorizontalHeaderLabels(QStringList{"Variable", "Value (error separated by +- signs)"});
    ui->dataTableWidget->horizontalHeader()->setStretchLastSection(true);
    */
}

#ifdef _MSC_VER
    #define pipe _pipe
    #define popen _popen
    #define pclose _pclose
#endif

/*  //C pipe/STD Implementation of exec
std::string exec(std::string cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}*/

// Qt implementation of exec
QString exec(QString executable, QStringList arguments)
{
    QProcess proc;
    proc.setProcessChannelMode(QProcess::MergedChannels);
    proc.start(executable, arguments);
    proc.waitForFinished(10000);

    return proc.readAllStandardOutput();
}

bool checkpython(QString pythonexe = "python") {
    QString res = exec(pythonexe, {"--version"});
    res.truncate(6);
    if(res != "Python")
        return false;
    return true;
}

bool checkgtc(QString pythonexe = "python") {
    std::regex p("[\\d\\.]+");
    QString res = exec(pythonexe, {"-c \"import GTC;print(GTC.version)\""});
    std::smatch s;
    std::string out = res.toStdString();
    if(regex_search(out, s, p))
        return true;
    return false;
}

QString appendPath(const QString& path1, const QString& path2)
{
    return QDir::cleanPath(path1 + QDir::separator() + path2);
}

void MainWindow::on_evaluateBtn_clicked()
{
    // Check if table is empty
    if(ui->dataTableWidget->rowCount()==0)
    {
        QMessageBox::warning(this, "Error", "No values in data table");
    } // Check if expression is empty
    else if (ui->expressionEditText->text().length() == 0)
    {
        QMessageBox::warning(this, "Error", "Expression empty");
    }
    else
    {
        try {
            // Check if python and GTC are installed
            /*if(!checkpython() && !checkgtc())
                throw std::runtime_error("Python and/or GTC are not installed or not in yor PATH");*/

            // Go on
            std::regex namePattern("^[a-zA-Z][\da-zA-Z]*$");
            std::regex dataPattern("^([\\d\\.eE]*) \\+\\- ([\\d\\.eE]*)$");
            std::smatch resmatch;
            std::map<std::string, std::pair<double,double>> data;
            for(int i = 0; i < ui->dataTableWidget->rowCount(); i++)
            {
                QString variable, value;
                variable = ui->dataTableWidget->item(i, 0)->text();
                std::string variableName = variable.toStdString();
                if(!std::regex_search(variableName, resmatch, namePattern))
                    throw std::invalid_argument("Variable name '"+variable.toStdString()+"' is bad");

                if(variableName.find(' ') != std::string::npos)
                    throw std::invalid_argument("No spaces in variable names");

                value = ui->dataTableWidget->item(i, 1)->text();
                std::string valueString = value.toStdString();
                if(std::regex_search(valueString, resmatch, dataPattern) && resmatch.size() > 1)
                {
                    double number = std::stod(resmatch[1].str());
                    double uncert = std::stod(resmatch[2].str());

                    data[variable.toStdString()] = std::pair<double,double>(number, uncert);
                } else {
                    throw std::invalid_argument("Value is badly formatted: "+value.toStdString());
                }
            }

            // create script
            QString scriptName = QDir::temp().absoluteFilePath("uncscript.py");

            // Check if Python and GTC are available

            if(pythonExe == "")
            {
                if(checkpython() && checkgtc()) // First check for a globally installed python
                    pythonExe = "python";
                else if(checkpython("python.exe") && checkgtc("python.exe"))
                    pythonExe = "python.exe";
                else if (checkpython(QDir(QCoreApplication::applicationDirPath()+"/python-3.7.2.amd64").absoluteFilePath("python.exe")) && checkgtc(QDir(QCoreApplication::applicationDirPath()+"/python-3.7.2.amd64").absoluteFilePath("python.exe"))) // Then check for a local distribution (win)
                    pythonExe = QDir(QCoreApplication::applicationDirPath()+"/python-3.7.2.amd64").absoluteFilePath("python.exe");
                else if (checkpython(QDir(QCoreApplication::applicationDirPath()+"/python-3.7.2.amd64").absoluteFilePath("python")) && checkgtc(QDir(QCoreApplication::applicationDirPath()+"/python-3.7.2.amd64").absoluteFilePath("python"))) // Or for a linux local distribution
                    pythonExe = QDir(QCoreApplication::applicationDirPath()+"/python-3.7.2.amd64").absoluteFilePath("python");
                else {  // Otherwise send the user my regards
                    pythonExe = ":(";
                    throw std::runtime_error("No python distribution found or no GTC package installed. Install python and install GTC package, then make sure it is available in your PATH variable.");
                }
            } else if (pythonExe == ":(")
                throw std::runtime_error("No python distribution found or no GTC package installed. Install python and install GTC package, then make sure it is available in your PATH variable.");

            //std::string command = "\""+pythonExe.toStdString()+"\" \""+scriptName.toStdString()+"\"";
            //QMessageBox::information(this, "DBG", QString::fromStdString(command));

            std::ofstream script(scriptName.toStdString());

            script << "import GTC" << std::endl <<
                      "from GTC import *" << std::endl;
            for(auto element : data)
            {
                script << element.first << " = ureal(" << element.second.first << "," << element.second.second << ")" << std::endl;
            }
            script << std::endl;
            script << "RESULT = " << ui->expressionEditText->text().toStdString() << std::endl;
            script << "print(value(RESULT))" << std::endl <<
                      "print(uncertainty(RESULT))" << std::endl;

            script.close();

            QString result = exec(pythonExe, {scriptName});

            QStringList lines = result.split("\n");

            if(lines.size() < 2)
                throw std::invalid_argument("Bad output from python script.\n"+result.toStdString());

            //check output

            bool ok;

            double n_Val = lines[0].toDouble(&ok);

            if(!ok)
                throw std::invalid_argument("First line in output is bad.\n"+lines[0].toStdString());

            double n_Unc = lines[1].toDouble(&ok);

            if(!ok)
                throw std::invalid_argument("Second line in output is bad.\n"+lines[1].toStdString());

            ui->resultEditText->setText(QString::number(n_Val) + " +- " + QString::number(n_Unc));
        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
        }

    }
}

void MainWindow::on_helpBtn_clicked()
{
    QString message = /*"First, make sure Python is installed and added to PATH variable (that is, you are able to run it by typing 'python' in your terminal)\n\n"
            "Second, install GTC package through pip or manually, e.g. install it by executing 'pip install GTC' in your terminal\n\n"*/
            "First, add your data to the table by choosing a variable name and the numerical value has to be in the form of 'VALUE +- UNCERTAINTY'\n\n"
            "Numerical constants can be added by typing 0.0 as the uncertainty.\n\n"
            "Second, build an expression with Python syntax. Operators such as '+', '-', '/', '*', '**' (elevation to the power of), 'log', 'log10', 'exp', etc. can be used.\n\n"
            "Refer to Python and GTC help for a more extensive list.";
    QMessageBox::information(this, "Help", message);
}

void MainWindow::customMenuRequestedEvTable(const QPoint& pos)
{
    contextMenuEvaluationTable->exec(ui->dataTableWidget->mapToGlobal(pos));
}

void MainWindow::menuEvTableCopy()
{
    if(ui->dataTableWidget->selectedItems().size()>0) {
        QString clipboardText = "";
        int colIndex = 0;
        for(auto item : ui->dataTableWidget->selectedItems()) {
            clipboardText += item->text();
            if(colIndex == 0) {
                clipboardText += "\t";
                colIndex++;
            } else {
                clipboardText += "\n";
                colIndex = 0;
            }
        }
        QClipboard* clipbrd = QApplication::clipboard();
        clipbrd->setText(clipboardText);
    }
}

void MainWindow::menuEvTablePaste()
{
    QClipboard* clipbrd = QApplication::clipboard();
    QString clipBrdText = clipbrd->text();
    if(clipBrdText.length()>0) {
        QStringList rows = clipBrdText.split("\n");
        if(rows.last().length() == 0)
            rows.removeLast();
        if(rows.size()>0) {
            int prevRows = ui->dataTableWidget->rowCount();
            int selRows = rows.size();
            int currRow = prevRows;
            ui->dataTableWidget->setRowCount(prevRows+selRows);
            for(QString elem : rows) {
                QStringList cols = elem.split("\t");
                if(cols.size()>1) {
                    QTableWidgetItem* newItem0 = new QTableWidgetItem(cols.at(0));
                    QTableWidgetItem* newItem1 = new QTableWidgetItem(cols.at(1));
                    ui->dataTableWidget->setItem(currRow, 0, newItem0);
                    ui->dataTableWidget->setItem(currRow, 1, newItem1);
                    currRow++;
                }
            }
        }
    }
}

void MainWindow::menuEvTableExportAsTabDel()
{
    if(ui->dataTableWidget->rowCount()>0)
    {
        QString fileName = QFileDialog::getSaveFileName(this, "Export data", "", "Text file (*.txt)");
        if(fileName != "")
        {
            std::ofstream expFile(fileName.toStdString());
            for(int i = 0; i < ui->dataTableWidget->rowCount(); i++)
            {
                expFile << ui->dataTableWidget->item(i, 0)->text().toStdString() << "\t" << ui->dataTableWidget->item(i, 1)->text().toStdString() << std::endl;
            }
        }
    }
}

void MainWindow::menuEvTableImportTabDel()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Import data", "", "Text file (*.txt)");
    if(fileName != "")
    {
        std::ifstream impFile(fileName.toStdString());
        QStringList fileLines;
        std::string line;
        while(std::getline(impFile, line))
            fileLines.append(QString::fromStdString(line));
        if(fileLines.size()>0)
        {
            std::vector<std::pair<QString, QString>> result;
            for(QString fileLine : fileLines)
            {
                QStringList values = fileLine.split('\t');
                if(values.size()>=2)
                {
                    result.emplace_back(std::pair<QString,QString>(values[0], values[1]));
                }
            }

            int prevRows = ui->dataTableWidget->rowCount();
            int selRows = result.size();
            int currRow = prevRows;
            ui->dataTableWidget->setRowCount(prevRows+selRows);

            for(auto elem : result) {
                QTableWidgetItem* newItem0 = new QTableWidgetItem(elem.first);
                QTableWidgetItem* newItem1 = new QTableWidgetItem(elem.second);
                ui->dataTableWidget->setItem(currRow, 0, newItem0);
                ui->dataTableWidget->setItem(currRow, 1, newItem1);
                currRow++;
            }
        }
    }
}
