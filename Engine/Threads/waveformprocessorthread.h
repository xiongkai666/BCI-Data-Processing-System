
#ifndef WAVEFORMPROCESSORTHREAD_H
#define WAVEFORMPROCESSORTHREAD_H

#include <QObject>
#include <QThread>
#include <vector>
#include "datastreamfifo.h"
#include "waveformfifo.h"
#include "systemstate.h"
#include "xpucontroller.h"

using namespace std;

class WaveformProcessorThread : public QThread
{
    Q_OBJECT
public:
    explicit WaveformProcessorThread(SystemState* state_, int numDataStreams_, double sampleRate_,
                                     DataStreamFifo* usbFifo_, WaveformFifo* waveformFifo_,
                                     XPUController* xpuController_, QObject *parent = nullptr);

    void run() override;
    void startRunning(int numDataStreams_);
    void stopRunning();
    bool isActive() const;
    void close();

signals:
    void cpuLoadPercent(double percent);

private:
    SystemState* state;
    SignalSources* signalSources;
    ControllerType type;
    double sampleRate;
    DataStreamFifo* usbFifo;
    WaveformFifo* waveformFifo;
    int numDataStreams;

    vector<double> cpuLoadHistory;

    XPUController* xpuController;

    volatile bool keepGoing;
    volatile bool running;
    volatile bool stopThread;
};

#endif // WAVEFORMPROCESSORTHREAD_H
