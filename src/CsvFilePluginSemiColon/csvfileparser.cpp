#include "csvfileparser.h"

const QString CsvFileParser::getFileFilter() const
{
    return "CSV File (*.csv  *.CSV)";
}

const QString CsvFileParser::getDisplayName() const
{
    return "Semi-colon separated CSV File";
}

const ParsedData CsvFileParser::fromFileName(QString fileName) const
{
    return fromFile(std::ifstream(fileName.toStdString()));
}

void CsvFileParser::setLocale(std::string locale)
{
    customLocale = locale;
}

const ParsedData CsvFileParser::fromFile(std::ifstream file) const
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

const ParsedData CsvFileParser::fromText(QString fileContent) const
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
