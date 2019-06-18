#include "peakstextfileparser.h"

const QString PeaksTextFileParser::getFileFilter() const
{
    return "Text File (*.txt)";
}

const QString PeaksTextFileParser::getDisplayName() const
{
    return "Peaks Text File";
}

const ParsedData PeaksTextFileParser::fromFileName(QString fileName) const
{
    return fromFile(std::ifstream(fileName.toStdString()));
}

void PeaksTextFileParser::setLocale(std::string locale)
{
    customLocale = locale;
}

const ParsedData PeaksTextFileParser::fromFile(std::ifstream file) const
{
    using namespace std;

    setlocale(LC_ALL, customLocale.c_str());

    ParsedData returnData;
    returnData.success = true;

    string line;

    while(!file.eof()) {
        getline(file, line);
        smatch regRes;
        if(regex_search(line, regRes, peaksRegex) && regRes.size() > 2) {
            try {
                double xRes = stod(regRes[1].str());
                double yRes = stod(regRes[2].str());
                returnData.xData.emplace_back(xRes);
                returnData.yData.emplace_back(yRes);
            } catch (const std::exception& e) {
                returnData.success = false;
            }
        }
    }

    return returnData;
}

const ParsedData PeaksTextFileParser::fromText(QString fileContent) const
{
    using namespace std;

    setlocale(LC_ALL, customLocale.c_str());

    ParsedData returnData;
    returnData.success = true;

    istringstream filelines(fileContent.toStdString());
    string line;

    while(getline(filelines, line)) {
        smatch regRes;
        if(regex_search(line, regRes, peaksRegex) && regRes.size() > 2) {
            try {
                double xRes = stod(regRes[1].str());
                double yRes = stod(regRes[2].str());
                returnData.xData.emplace_back(xRes);
                returnData.yData.emplace_back(yRes);
            } catch (const std::exception& e) {
                returnData.success = false;
            }
        }
    }

    return returnData;
}
