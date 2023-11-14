
#ifndef SPIKEPLOT_H
#define SPIKEPLOT_H

#define SPIKEPLOT_X_SIZE 480
#define SPIKEPLOT_Y_SIZE 481

#include <QtWidgets>
#include <deque>
#include <vector>
#include <map>
#include "systemstate.h"
#include "plotutilities.h"
#include "waveformfifo.h"

using namespace std;

struct SpikePlotHistory
{
    deque<vector<float> > snippets;
    deque<int> spikeIds;

    deque<vector<float> > snapshotSnippets;
    deque<int> snapshotSpikeIds;
};


class SpikePlot : public QWidget
{
    Q_OBJECT
public:
    explicit SpikePlot(SystemState* state_, QWidget *parent = nullptr);
    ~SpikePlot();

    void setWaveform(const string& waveName);
    QString getWaveform();
    bool updateWaveforms(WaveformFifo* waveformFifo, int numSamples);
    void clearSpikes();

    void takeSnapshot();
    void clearSnapshot();

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

public slots:
    void updateFromState();

protected:
    void paintEvent(QPaintEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    SystemState* state;
    Channel* channel;
    SpikePlotHistory* history;
    int samplesPreDetect;
    int samplesPostDetect;
    double tStepMsec;

    QRect scopeFrame;
    QImage image;

    map<string, SpikePlotHistory*> spikeHistoryMap;

    const QColor SnapshotColor = QColor(140, 83, 25);

    double latestRmsCalculation;
    int latestSpikeRateCalculation;

    CoordinateTranslator ct;

    void updateCoordinateTranslator();
};

#endif // SPIKEPLOT_H
