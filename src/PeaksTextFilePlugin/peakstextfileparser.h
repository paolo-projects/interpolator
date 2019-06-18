#ifndef PEAKSTEXTFILEPARSERINTERFACE_H
#define PEAKSTEXTFILEPARSERINTERFACE_H

#include <QGenericPlugin>
#include <QString>
#include <QException>

#include <regex>
#include <vector>
#include <fstream>
#include <sstream>

#include "datafileparserinterface.h"

#define ParserInterface_iid "chem.res.interpolator.Qt.ParserInterface"

class PeaksTextFileParser : public QObject, ParserInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID ParserInterface_iid FILE "PeaksTextFilePlugin.json")
    Q_INTERFACES(ParserInterface)
public:
    const ParsedData fromFileName(QString fileName) const override;
    const ParsedData fromFile(std::ifstream file) const override;
    const ParsedData fromText(QString fileContent) const override;
    const QString getFileFilter() const override;
    const QString getDisplayName() const override;
	void setLocale(std::string locale) override;
private:
    const std::regex peaksRegex = std::regex("Position:\\D*([\\d\\.]+)\\D*Intensity:\\D*([\\d\\.]+)", std::regex::icase);
	
	std::string customLocale = "C";
};

#endif // PEAKSTEXTFILEPARSERINTERFACE_H
