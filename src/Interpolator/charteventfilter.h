#ifndef CHARTEVENTFILTER_H
#define CHARTEVENTFILTER_H

#include <QObject>
#include <QtCharts>

class ChartEventFilter : public QObject
{
    Q_OBJECT
public:
    ChartEventFilter(QObject *parent = nullptr) {};
protected:
    virtual bool eventFilter(QObject *watched, QEvent *event) override {
        if (event->type() == QEvent::MouseButtonPress && dynamic_cast<QMouseEvent*>(event)->button() == Qt::MiddleButton) {
            dynamic_cast<QChartView*>(watched)->chart()->zoomReset();
                return true;
            } else {
                return QObject::eventFilter(watched, event);
            }
    }
};

#endif // CHARTEVENTFILTER_H
