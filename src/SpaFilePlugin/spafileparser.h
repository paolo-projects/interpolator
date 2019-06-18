#ifndef PEAKSTEXTFILEPARSERINTERFACE_H
#define PEAKSTEXTFILEPARSERINTERFACE_H

#include <QGenericPlugin>
#include <QString>
#include <QException>

#include <regex>
#include <vector>
#include <fstream>

#include "datafileparserinterface.h"

#define ParserInterface_iid "chem.res.interpolator.Qt.ParserInterface"

// Define a bunch of offset values
#define COMMENTS_LOC 0x1E
#define POINTSCOUNT_LOC 0x234
#define WAVENUMS_LOC 0x240
#define ADDR_SEARCHAREA_LOC 0x120

class SpaFileParser : public QObject, ParserInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID ParserInterface_iid FILE "SpaFilePlugin.json")
    Q_INTERFACES(ParserInterface)
public:
    const ParsedData fromFileName(QString fileName) const override;
    const ParsedData fromFile(std::ifstream file) const override;
    const ParsedData fromText(QString fileContent) const override;
    const QString getFileFilter() const override;
    const QString getDisplayName() const override;
	void setLocale(std::string locale) override;
private:
    static bool is_bigEndian();
    static uint32_t readUInt32(unsigned char* data, bool bigEndian);
    static uint16_t readUInt16(unsigned char* data, bool bigEndian);
    static float readFloat(unsigned char* data, bool bigEndian);
    class UnsupportedActionException : public QException
    {
    public:
        UnsupportedActionException(const QString& msg) : message(msg) {}
        void raise() const override { throw *this; }
        UnsupportedActionException *clone() const override { return new UnsupportedActionException(*this); }
        const QString& getMessage() {return message;}
    private:
        QString message;
    };
	
	std::string customLocale = "C";
};

#endif // PEAKSTEXTFILEPARSERINTERFACE_H
