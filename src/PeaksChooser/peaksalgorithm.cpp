#include "peaksalgorithm.h"

//TODO: Improve algorithm, now it finds every fucking small piece of shitty peak even the fucking random noise in the line

PeaksAlgorithm::PeaksAlgorithm(std::vector<double> x, std::vector<double> y)
    : x(x), y(y)
{

}

std::vector<PeaksAlgorithm::Peak> PeaksAlgorithm::findAll()
{
    std::vector<Peak> result;
    if(std::min(x.size(), y.size()) > 2)
    {
                                    // -1   --> descending
                                    // 0    --> horizontal
                                    // +1   --> ascending
        int prevInclination = -2;
        double prevAverage = 0;
        int i = 0;
        while (i < std::min(x.size(), y.size()))
        {
            double average = 0;
            for(int n = i; n < i+sensitivity; n++)
            {
                average += y[n];
            }
            average /= sensitivity;

            int thisInclination = getInclination(average, prevAverage);

            if(prevInclination != -2)
            {
                if(isPeak(prevInclination, thisInclination))
                {
                    result.emplace_back(findMaxInRange(x, y, i-sensitivity, i));
                }
            }

            prevAverage = average;
            prevInclination = thisInclination;

            i += sensitivity;
        }
        /*for(int i = 2; i < ); i++)
        {
            int thisInclination = getInclination(y[i], y[i-1]);
            if(isPeak(prevInclination, thisInclination))
                result.emplace_back(Peak(x[i-1], y[i-1]));
            prevInclination = thisInclination;
        }*/
    }
    return result;
}

std::vector<PeaksAlgorithm::Peak> PeaksAlgorithm::findInRange(double x_min, double x_max)
{
    std::vector<double> r_x, r_y;
    for(int i = 2; i < std::min(x.size(), y.size()); i++)
    {
        if(x[i] >= x_min && x[i] <= x_max)
        {
            r_x.emplace_back(x[i]);
            r_y.emplace_back(y[i]);
        }
    }

    std::vector<Peak> result;

    if(r_x.size() > 2)
    {
        int prevInclination = -2;
        double prevAverage = 0;
        int i = 0;
        while (i < std::min(r_x.size(), r_y.size()))
        {
            double average = 0;
            for(int n = i; n < i+sensitivity; n++)
            {
                average += r_y[n];
            }
            average /= sensitivity;

            int thisInclination = getInclination(average, prevAverage);

            if(prevInclination != -2)
            {
                if(isPeak(prevInclination, thisInclination))
                {
                    result.emplace_back(findMaxInRange(r_x, r_y, i-sensitivity, i));
                }
            }

            prevAverage = average;
            prevInclination = thisInclination;

            i += sensitivity;
        }
    }
    return result;
}

std::vector<PeaksAlgorithm::Peak> PeaksAlgorithm::findAboveTreshold(double yt)
{
    std::vector<Peak> result;
    if(std::min(x.size(), y.size()) > 2)
    {
        int prevInclination = -2;
        double prevAverage = 0;
        int i = 0;
        while (i < std::min(x.size(), y.size()))
        {
            double average = 0;
            for(int n = i; n < i+sensitivity; n++)
            {
                average += y[n];
            }
            average /= sensitivity;

            int thisInclination = getInclination(average, prevAverage);

            if(prevInclination != -2)
            {
                if(overTreshold(prevAverage, yt) && isPeak(prevInclination, thisInclination))
                {
                    result.emplace_back(findMaxInRange(x, y, i-sensitivity, i));
                }
            }

            prevAverage = average;
            prevInclination = thisInclination;

            i += sensitivity;
        }
    }
    return result;
}

int PeaksAlgorithm::getInclination(double v1, double v0)
{
    if(v1>v0)
        return 1;
    else if (v1<v0)
        return -1;
    else
        return 0;
}

bool PeaksAlgorithm::isPeak(int prevInclination, int thisInclination)
{
    if(method == PeaksMethod::MAXIMUM)
    {
        if(prevInclination == 1 && thisInclination == -1)
            return true;
    } else if (method == PeaksMethod::MINIMUM)
    {
        if(prevInclination == -1 && thisInclination == 1)
            return true;
    }
    return false;
}

bool PeaksAlgorithm::overTreshold(double value, double treshold)
{
    if(method == PeaksMethod::MAXIMUM)
        return value >= treshold;
    else if (method == PeaksMethod::MINIMUM)
        return value <= treshold;
}

PeaksAlgorithm::Peak PeaksAlgorithm::findMaxInRange(std::vector<double>& x, std::vector<double>& y, int starti, int endi)
{
    int imax = starti;
    double maxy = y[starti];
    for(int i = starti; i< endi; i++)
    {
        if((method==PeaksMethod::MAXIMUM && y[i] > maxy) || (method==PeaksMethod::MINIMUM && y[i] < maxy))
        {
            maxy = y[i];
            imax = i;
        }
    }
    return Peak(x[imax], y[imax]);
}
