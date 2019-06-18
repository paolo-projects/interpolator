#ifndef DATAPLUGININTERFACE_H
#define DATAPLUGININTERFACE_H

#include <fstream>
#include <vector>
#include <QString>
#include <QtPlugin>

class DataPluginInterface
{
public:
    virtual ~DataPluginInterface() {};
    virtual const QString getName() const = 0;
    virtual const QString getDescription() const = 0;
    virtual void invoke(std::vector<double> xData, std::vector<double> yData) = 0;
};

#define DataPluginInterface_iid "chem.res.interpolator.Qt.DataPluginInterface"

Q_DECLARE_INTERFACE(DataPluginInterface, DataPluginInterface_iid)

#endif // DATAPLUGININTERFACE_H
