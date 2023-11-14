
#ifndef RANDOMNUMBER_H
#define RANDOMNUMBER_H

class QRandomGenerator;

class RandomNumber
{
public:
    RandomNumber();
    ~RandomNumber();
    double randomUniform();
    double randomUniform(double min, double max);
    double randomLogUniform(double min, double max);
    double randomGaussian();
    void setGaussianAccuracy(int n);

private:
    int gaussianN;
    double gaussianScaleFactor;

    QRandomGenerator* generator;
};

#endif // RANDOMNUMBER_H
