#ifndef PEAKSCHOOSER_H
#define PEAKSCHOOSER_H

#include "dataplugininterface.h"
#include "peakschooserwindow.h"

#define DataPluginInterface_iid "chem.res.interpolator.Qt.DataPluginInterface"

class PeaksChooser : public QObject, DataPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID DataPluginInterface_iid FILE "PeaksChooser.json")
    Q_INTERFACES(DataPluginInterface)
public:
    PeaksChooser() = default;
    const QString getName() const;
    const QString getDescription() const;
    void invoke(std::vector<double> xData, std::vector<double> yData);
};

#endif // PEAKSCHOOSER_H
