#ifndef DATAFILEPARSERINTERFACE_H
#define DATAFILEPARSERINTERFACE_H

#include <fstream>
#include <vector>
#include <QString>
#include <QtPlugin>

class ParsedData
{
public:
    std::vector<double> xData, yData;
    bool success;
};

class ParserInterface
{
public:
    virtual ~ParserInterface() {};
    virtual const ParsedData fromFileName(QString fileName) const = 0;
    virtual const ParsedData fromFile(std::ifstream file) const = 0;
    virtual const ParsedData fromText(QString fileContent) const = 0;
    virtual const QString getFileFilter() const = 0;
    virtual const QString getDisplayName() const = 0;
    virtual void setLocale(std::string locale) = 0;
};

#define ParserInterface_iid "chem.res.interpolator.Qt.ParserInterface"

Q_DECLARE_INTERFACE(ParserInterface, ParserInterface_iid)

#endif // DATAFILEPARSERINTERFACE_H
