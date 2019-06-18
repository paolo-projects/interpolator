#ifndef PAINTABLECHARTVIEW_H
#define PAINTABLECHARTVIEW_H

#include <QtCharts>
#include <vector>

class PaintableChartView : public QChartView
{
public:
    explicit PaintableChartView(QWidget *parent = nullptr);
    void addVerticalBar(double xPos);
    void addVerticalBar(std::initializer_list<double> xPos_l);
    void removeVerticalBar(int index);
    void removeVerticalBar(double xPos);
    void clearVerticalBars();

    void setYMin(double y) { yMin = y; }
    void setYMax(double y) { yMax = y; }
signals:

public slots:

protected:
    void paintEvent(QPaintEvent* event);

private:
    std::vector<double> verLines;
    double yMin, yMax;
};

#endif // PAINTABLECHARTVIEW_H
