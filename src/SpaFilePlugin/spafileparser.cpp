#include "spafileparser.h"

const QString SpaFileParser::getFileFilter() const
{
    return "SPA File (*.spa *.SPA)";
}

const QString SpaFileParser::getDisplayName() const
{
    return "SPA File";
}

const ParsedData SpaFileParser::fromFileName(QString fileName) const
{
    return fromFile(std::ifstream(fileName.toStdString(), std::ios::binary));
}

void SpaFileParser::setLocale(std::string locale)
{
    customLocale = locale;
}

typedef unsigned char byte;

const ParsedData SpaFileParser::fromFile(std::ifstream file) const
{
    using namespace std;

    setlocale(LC_ALL, customLocale.c_str());

    ParsedData returnData;
    returnData.success = true;

    char fComment[255];

    // read file comment (name, description)
    file.seekg(COMMENTS_LOC, ios::beg);
    file.read(fComment, 255);

    byte buf[4], shortbuf[2];

    // read number of points
    file.seekg(POINTSCOUNT_LOC, ios::beg);
    file.read((char*)buf, 4);

    uint32_t pointsCount;
    memcpy(&pointsCount, &buf, 4);

    float wavenum1, wavenum2;

    // read start and end wavenumbers
    file.seekg(WAVENUMS_LOC, ios::beg);
    file.read((char*)buf, 4);
    memcpy(&wavenum1, &buf, 4);
    file.read((char*)buf, 4);
    memcpy(&wavenum2, &buf, 4);

    // just to be sure, wavenum1 has to be bigger than wavenum2
    if(wavenum1 < wavenum2)
    {
        float temp = wavenum1;
        wavenum1 = wavenum2;
        wavenum2 = temp;
    }

    uint16_t flag = 0, offset;

    // read until the flag value = 3 is reached, then read the start address of data floats
    file.seekg(ADDR_SEARCHAREA_LOC, ios::beg);
    while(flag != 3)
    {
        file.read((char*)shortbuf, 2);
        memcpy(&flag, &shortbuf, 2);
    }

    file.read((char*)shortbuf, 2);
    memcpy(&offset, &shortbuf, 2);

    file.seekg(offset, ios::beg);

    returnData.xData.reserve(pointsCount);
    returnData.yData.reserve(pointsCount);

    // read intensity values in memory

    float* intensities = (float*)calloc(pointsCount, sizeof(float));

    file.read((char*)intensities, pointsCount*4);

    for(size_t c = 0; c < pointsCount; c++)
    {
        returnData.yData.emplace_back(intensities[c]);        
        returnData.xData.emplace_back(wavenum1 - (wavenum1-wavenum2)*c / pointsCount);
    }

    free(intensities);

    return returnData;
}

const ParsedData SpaFileParser::fromText(QString fileContent) const
{
    throw UnsupportedActionException("Unsupported method. Can't parse from string, only from binary data.");
}
