#include "peakschooserwindow.h"
#include "ui_peakschooserwindow.h"

PeaksChooserWindow::PeaksChooserWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PeaksChooserWindow),
    pksAlg(std::vector<double>(), std::vector<double>())
{
    ui->setupUi(this);
    contextMenuPeaksTable = new QMenu(ui->peaksTable);
    contextMenuPeaksTable->addAction("&Copy", this, SLOT(peaksTableMenuCopy()));
    connect(ui->peaksTable, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(customMenuRequestedPeaksTable(const QPoint&)));
}

PeaksChooserWindow::~PeaksChooserWindow()
{
    delete ui;
}

PeaksChooserWindow* PeaksChooserWindow::build(std::vector<double>& xData, std::vector<double>& yData)
{
    PeaksChooserWindow* wnd = new PeaksChooserWindow();
    wnd->xData = xData;
    wnd->yData = yData;
    wnd->show();
    wnd->populate();
    return wnd;
}

void PeaksChooserWindow::populate()
{
    ui->peaksChart->setRenderHint(QPainter::Antialiasing);
    QChart* chart = ui->peaksChart->chart();
    QLineSeries* lineSeries = new QLineSeries();
    lineSeries->setUseOpenGL(true);

    double yMin = 0.0, yMax = 0.0;

    for(int i = 0; i < std::min(xData.size(), yData.size()); i++)
    {
        lineSeries->append(xData.at(i), yData.at(i));
        yMin = std::min(yMin, yData.at(i));
        yMax = std::max(yMax, yData.at(i));
    }

    chart->legend()->hide();
    chart->addSeries(lineSeries);
    chart->createDefaultAxes();

    ui->peaksChart->setYMin(yMin);
    ui->peaksChart->setYMax(yMax);

    addPeaksToTable();
}

void PeaksChooserWindow::addPeaksToTable()
{
    QTableWidget* table = ui->peaksTable;
    table->setColumnCount(2);

    pksAlg = PeaksAlgorithm(xData, yData);
    peaks = pksAlg.findAll();

    table->setRowCount(peaks.size());

    int row = 0;

    for(PeaksAlgorithm::Peak peak : peaks)
    {
        QTableWidgetItem* itemX = new QTableWidgetItem(QString::number(peak.getX()));
        QTableWidgetItem* itemY = new QTableWidgetItem(QString::number(peak.getY()));

        table->setItem(row, 0, itemX);
        table->setItem(row, 1, itemY);

        ui->peaksChart->addVerticalBar(peak.getX());

        row++;
    }

    ui->peaksChart->repaint();
}

void PeaksChooserWindow::on_spinBox_valueChanged(int arg1)
{
    QTableWidget* table = ui->peaksTable;

    table->clear();
    ui->peaksChart->clearVerticalBars();

    table->setColumnCount(2);

    pksAlg.setSensitivity(arg1);
    peaks = pksAlg.findAll();

    table->setRowCount(peaks.size());

    int row = 0;

    for(PeaksAlgorithm::Peak peak : peaks)
    {
        QTableWidgetItem* itemX = new QTableWidgetItem(QString::number(peak.getX()));
        QTableWidgetItem* itemY = new QTableWidgetItem(QString::number(peak.getY()));

        table->setItem(row, 0, itemX);
        table->setItem(row, 1, itemY);

        ui->peaksChart->addVerticalBar(peak.getX());

        row++;
    }

    ui->peaksChart->repaint();
}

void PeaksChooserWindow::customMenuRequestedPeaksTable(const QPoint& point)
{
    contextMenuPeaksTable->exec(ui->peaksTable->mapToGlobal(point));
}

void PeaksChooserWindow::peaksTableMenuCopy()
{
    if(ui->peaksTable->selectedItems().size()>0) {
            QString clipboardText = "";
            int colIndex = 0;
            for(auto item : ui->peaksTable->selectedItems()) {
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
