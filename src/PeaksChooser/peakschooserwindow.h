#ifndef PEAKSCHOOSERWINDOW_H
#define PEAKSCHOOSERWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <vector>

#include <peaksalgorithm.h>

namespace Ui {
class PeaksChooserWindow;
}

class PeaksChooserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PeaksChooserWindow(QWidget *parent = nullptr);
    ~PeaksChooserWindow();
    static PeaksChooserWindow* build(std::vector<double>& xData, std::vector<double>& yData);
private slots:
    void on_spinBox_valueChanged(int arg1);
    void customMenuRequestedPeaksTable(const QPoint& point);
    void peaksTableMenuCopy();
private:
    Ui::PeaksChooserWindow *ui;
    std::vector<double> xData;
    std::vector<double> yData;
    std::vector<PeaksAlgorithm::Peak> peaks;
    void populate();
    void addPeaksToTable();
    PeaksAlgorithm pksAlg;
    QMenu* contextMenuPeaksTable;
};

#endif // PEAKSCHOOSERWINDOW_H
