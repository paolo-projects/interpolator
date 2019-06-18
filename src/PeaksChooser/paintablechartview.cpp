#include "paintablechartview.h"

PaintableChartView::PaintableChartView(QWidget *parent) : QChartView(parent)
{

}

void PaintableChartView::paintEvent(QPaintEvent* event)
{
    QChartView::paintEvent(event);

    if(verLines.size()>0)
    {
        QPainter painter(viewport());
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(Qt::red);

        for(double line : verLines)
        {
            QPointF beginPos = chart()->mapToPosition(QPointF(line, yMin));
            QPointF endPos = chart()->mapToPosition(QPointF(line, yMax));

            painter.drawLine(beginPos.toPoint(), endPos.toPoint());
        }
    }
}

void PaintableChartView::addVerticalBar(double xPos)
{
    verLines.emplace_back(xPos);
}

void PaintableChartView::addVerticalBar(std::initializer_list<double> xPos_l)
{
    for(double d : xPos_l)
        verLines.emplace_back(d);
}

void PaintableChartView::removeVerticalBar(int index)
{
    if(index < verLines.size())
        verLines.erase(verLines.begin()+index);
}

void PaintableChartView::removeVerticalBar(double xPos)
{
    for(auto iter = verLines.begin(); iter != verLines.end(); iter++)
    {
        if(*iter == xPos)
            verLines.erase(iter);
    }
}

void PaintableChartView::clearVerticalBars()
{
    verLines.clear();
}
