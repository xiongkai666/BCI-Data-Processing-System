
#ifndef SPECTROGRAMPLOT_H
#define SPECTROGRAMPLOT_H

#define SPECPLOT_X_SIZE 600
#define SPECPLOT_Y_SIZE 550

#include <QtWidgets>
#include <vector>
#include <deque>
#include "systemstate.h"
#include "plotutilities.h"
#include "waveformfifo.h"
#include "rhxglobals.h"
#include "fastfouriertransform.h"

using namespace std;

class SpectrogramPlot : public QWidget
{
    Q_OBJECT
public:
    explicit SpectrogramPlot(SystemState* state_, QWidget *parent = nullptr);
    ~SpectrogramPlot();

    void setWaveform(const string& waveName_);
    QString getWaveform() const;
    bool updateWaveforms(WaveformFifo* waveformFifo, int numSamples);
    void resetSpectrogram();

    double getDeltaTimeMsec() const { return 1000.0 * tStep; }
    double getDeltaFreqHz() const { return frequencyScale[1]; }

    bool saveMatFile(const QString& fileName) const;
    bool saveCsvFile(QString fileName) const;
    bool savePngFile(const QString& fileName) const;

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

public slots:
    void updateFromState();

protected:
    void mouseMoveEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    SystemState* state;
    string waveName;

    deque<float> amplifierWaveformQueue;
    deque<float> amplifierWaveformRecordQueue;
    deque<uint16_t> digitalWaveformQueue;
    deque<uint32_t> waveformTimeStampQueue;

    FastFourierTransform* fftEngine;
    int fftSize;

    double tScale;
    int tSize;
    int tIndex;
    int numValidTStepsInSpectrogram;
    bool spectrogramFull;
    double tStep;

    float* fftInputBuffer;
    vector<float> frequencyScale;
    int fMinIndex;
    int fMaxIndex;
    vector<float> timeScale;
    vector<float> psdSpectrum;
    vector<vector<float> > psdSpectrogram;
    QImage psdRawImage;

    double psdScaleMin;
    double psdScaleMax;
    ColorScale* colorScale;
    QImage image;
    QRect scopeFrame;
    bool lastMouseWasInFrame;

    QString psdUnitsMicro;

    void setNewFftSize(int fftSize_);
    void updateFMinMaxIndex();
    void setNewTimeScale(double tScale_);
};

#endif // SPECTROGRAMPLOT_H
