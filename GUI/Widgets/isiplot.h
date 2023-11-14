
#ifndef ISIPLOT_H
#define ISIPLOT_H

#define ISIPLOT_X_SIZE 600
#define ISIPLOT_Y_SIZE 450

#include <QtWidgets>
#include <vector>
#include "systemstate.h"
#include "plotutilities.h"
#include "waveformfifo.h"
#include "rhxglobals.h"

using namespace std;

class ISIPlot : public QWidget
{
    Q_OBJECT
public:
    explicit ISIPlot(SystemState* state_, QWidget *parent = nullptr);

    void setWaveform(const string& waveName_);
    QString getWaveform() const { return QString::fromStdString(waveName); }
    bool updateWaveforms(WaveformFifo* waveformFifo, int numSamples);
    void resetISI();

    bool saveMatFile(const QString& fileName) const;
    bool saveCsvFile(QString fileName) const;
    bool savePngFile(const QString& fileName) const;

    QSize minimumSizeHint() const override { return QSize(ISIPLOT_X_SIZE, ISIPLOT_Y_SIZE); }
    QSize sizeHint() const override { return QSize(ISIPLOT_X_SIZE, ISIPLOT_Y_SIZE); }

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

    vector<int> isiCount;
    vector<float> timeScaleISI;
    int largestISIrecorded;
    int numISIsRecorded;
    uint32_t lastTimeStamp;

    vector<float> histogram;
    vector<float> histogramTScale;
    QImage histogramImage;

    double isiMean;
    double isiStdDev;

    int timeSpan;
    int binSize;
    double maxValueHistogram;
    double minNonZeroValueHistogram;

    bool lastMouseWasInFrame;
    QRect histogramFrame;

    QImage image;

    int numBins() const { return timeSpan / binSize; }
    int numTStepsPerBin() const { return qRound(binSize * state->sampleRate->getNumericValue() / 1000.0); }
    void calculateHistogram();
    void calculateISIStatistics();
};

#endif // ISIPLOT_H
