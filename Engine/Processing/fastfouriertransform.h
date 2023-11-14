
#ifndef FASTFOURIERTRANSFORM_H
#define FASTFOURIERTRANSFORM_H

class FastFourierTransform
{
public:
    enum WindowFunction {
        WindowRectangular,
        WindowTriangular,
        WindowHann,
        WindowHamming
    };

    FastFourierTransform(float sampleRate_, unsigned int length_ = 1024, WindowFunction function_ = WindowHamming);
    ~FastFourierTransform();

    void setLength(int length_);
    static void complexInputFft(float *data, unsigned int n);
    static void realInputFft(float *data, unsigned int n);
    float* logSqrtPowerSpectralDensity(float *data);
    float getFrequency(int index) const;

private:
    float sampleRate;
    unsigned int length;
    WindowFunction function;

    float *window;
    float *logPsd;
    float *frequency;

    void createWindow();
    void createPsdVector();
    void createFrequencyVector();
};

#endif // FASTFOURIERTRANSFORM_H
