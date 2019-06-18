#ifndef PEAKSALGORITHM_H
#define PEAKSALGORITHM_H

#include <vector>
#include <algorithm>

class PeaksAlgorithm
{
public:
    class Peak
    {
    public:
        Peak(double x, double y) : x(x), y(y) {}
        const double getX() const { return x; }
        const double getY() const { return y; }
        void setX(double x) { this->x = x; }
        void setY(double y) { this->y = y; }
    private:
        double x, y;
    };
    enum PeaksMethod {
        MAXIMUM,
        MINIMUM
    };

    PeaksAlgorithm(std::vector<double> x, std::vector<double> y);
    std::vector<Peak> findAll();
    std::vector<Peak> findInRange(double xi, double xf);
    std::vector<Peak> findAboveTreshold(double yt);
    void setMethod(PeaksMethod peaksMethod) { method = peaksMethod; }
    void setSensitivity(int sens) { sensitivity = sens; }
    const int getSensitivity() const { return sensitivity; }
private:
    std::vector<double> x,y;
    int getInclination(double v1, double v0);
    bool isPeak(int prevInclination, int thisInclination);
    bool overTreshold(double value, double treshold);
    Peak findMaxInRange(std::vector<double>& x, std::vector<double>& y, int starti, int endi);
    PeaksMethod method = PeaksMethod::MAXIMUM;
    int sensitivity = 1;
};

#endif // PEAKSALGORITHM_H
