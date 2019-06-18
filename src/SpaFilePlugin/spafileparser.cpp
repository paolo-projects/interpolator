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

bool SpaFileParser::is_bigEndian()
{
    int i = 1;
    return ( (*(char*)&i) == 0 );
}

uint32_t SpaFileParser::readUInt32(unsigned char* data, bool bigEndian)
{
    if(bigEndian)
    {
        uint32_t result = data[3];
        result = (result << 8) | data[2];
        result = (result << 8) | data[1];
        result = (result << 8) | data[0];
        return result;
    } else {
        uint32_t result = data[0];
        result = (result << 8) | data[1];
        result = (result << 8) | data[2];
        result = (result << 8) | data[3];
        return result;
    }
}

uint16_t SpaFileParser::readUInt16(unsigned char* data, bool bigEndian)
{
    if(bigEndian)
    {
        return static_cast<uint16_t>(
                              (data[1] << 8) |
                              data[0]);

    } else {
        return static_cast<uint16_t>(
                              (data[0] << 8) |
                              data[1]);

    }
}

float SpaFileParser::readFloat(unsigned char* data, bool bigEndian)
{
    if(bigEndian)
    {
        return static_cast<float>((data[3] << 24) |
                              (data[2] << 16) |
                              (data[1] << 8) |
                              data[0]);

    } else {
        return static_cast<float>((data[0] << 24) |
                              (data[1] << 16) |
                              (data[2] << 8) |
                              data[3]);

    }
}

const ParsedData SpaFileParser::fromFile(std::ifstream file) const
{
    using namespace std;

    setlocale(LC_ALL, customLocale.c_str());

    bool bigEndian = is_bigEndian();

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

    uint32_t pointsCount;// = readUInt32(buf, bigEndian);
    memcpy(&pointsCount, &buf, 4);

    float wavenum1, wavenum2;

    // read start and end wavenumbers
    file.seekg(WAVENUMS_LOC, ios::beg);
    // should probably take into account compiler dependent float representation against little endian float32 stored in the file --- disabled cause didn't work ;'(
    file.read((char*)buf, 4);
    //wavenum1 = readFloat(buf, bigEndian);
    memcpy(&wavenum1, &buf, 4);
    file.read((char*)buf, 4);
    //wavenum2 = readFloat(buf, bigEndian);
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
        //flag = readUInt16(shortbuf, bigEndian);
        memcpy(&flag, &shortbuf, 2);
    }

    file.read((char*)shortbuf, 2);
    //offset = readUInt16(shortbuf, bigEndian);
    memcpy(&offset, &shortbuf, 2);

    file.seekg(offset, ios::beg);

    returnData.xData.reserve(pointsCount);
    returnData.yData.reserve(pointsCount);

    // read intensity values in memory
    // now, reading the whole block in a single shot will give better performance but
    // doing so we'd drop endianness check, so we'll read them one by one, sigh :(

    // at least we can use the same for loop to store X data :D

    // nevermind, I dropped endianness check so I'm ready to have fun writing one big read instruction for my own pleasure >:)

#ifdef _MSC_VER
    // MSVC Compiler doesn't support array size not being know at compile time... hence we have to use a vector
    std::vector<float> ints_vec;
    ints_vec.reserve(pointsCount);

    for(size_t b_read = 0; b_read<pointsCount*4; b_read += 4) {
        float d;
        file.read((char*)(&d), 4);
        ints_vec.emplace_back(d);
    }
    float* intensities = ints_vec.data();
#else
    float intensities[pointsCount];
    memset(intensities, 0, pointsCount*4);

    file.read /* oooh I'm coming */ ((char*)intensities, pointsCount*4); /* yeah baby that was awesome, sry if I was too quick */
#endif

    for(size_t c = 0; c < pointsCount; c++)
    {
        returnData.yData.emplace_back(intensities[c]);
        /*float value;
        file.read((char*)buf, 4);
        value = readFloat(buf, bigEndian);

        returnData.yData.emplace_back(value);*/
        returnData.xData.emplace_back(wavenum1 - (wavenum1-wavenum2)*c / pointsCount);
    }

    return returnData;
}

const ParsedData SpaFileParser::fromText(QString fileContent) const
{
    throw UnsupportedActionException("Unsupported method. Can't parse from string, only from binary data.");
}
