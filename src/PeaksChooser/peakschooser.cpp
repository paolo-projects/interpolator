#include "peakschooser.h"

const QString PeaksChooser::getName() const
{
    return "Peaks Chooser";
}

const QString PeaksChooser::getDescription() const
{
    return "Provides a graphical interface to find peaks based upon a treshold line, or by manually selecting them.";
}

void PeaksChooser::invoke(std::vector<double> xData, std::vector<double> yData)
{
    PeaksChooserWindow::build(xData, yData);
}
