
#ifndef TCPDATAOUTPUTTHREAD_H
#define TCPDATAOUTPUTTHREAD_H

#include <QThread>
#include <stdint.h>

#include "systemstate.h"
#include "waveformfifo.h"
#include "tcpcommunicator.h"

using namespace std;

class TCPDataOutputThread : public QThread
{
    Q_OBJECT
public:
    explicit TCPDataOutputThread(WaveformFifo *waveformFifo_, const double sampleRate_, SystemState *state_, QObject *parent = nullptr);
    ~TCPDataOutputThread();

    void run() override; // QThread 'run()' method that is called when thread is started
    void startRunning(); // Enter run loop.
    void stopRunning(); // Exit run loop.
    bool isActive() const; // Is this thread running?
    void closeExternal(); // Close thread from outside this thread.

    void prepareToClose();
    bool isReadyToClose();

signals:
    void outputData(QByteArray *array, qint64 len);

private:
    void closeInternal(); // Close thread from inside this thread.
    void updateEnabledChannels();

    TCPCommunicator *tcpWaveformDataCommunicator;
    TCPCommunicator *tcpSpikeDataCommunicator;

    vector<string> channelNames;
    QVector<QString> enabledChannelNames;
    QVector<QString> enabledStimChannelNames;

    QStringList previousEnabledBands;

    int totalEnabledBands;
    int numAuxChannels;
    int numVddChannels;
    int numAdcChannels;
    int numDacChannels;
    int numDigitalInChannels;
    int numDigitalOutChannels;

    uint16_t* previousSample;

    int digInWordPresent;
    int digOutWordPresent;
    int numBytesPerFrame;
    int numBytesPerDataBlock;

    QByteArray waveformArray;
    qint64 waveformArrayIndex;

    QByteArray spikeArray;
    qint64 spikeArrayIndex;

    int numBytesPerSpikeChunk;
    int maxChunksPerDataBlock;

    WaveformFifo *waveformFifo;

    SignalSources *signalSources;

    double sampleRate;

    vector<uint8_t> posStimAmplitudes;
    vector<uint8_t> negStimAmplitudes;

    bool closeRequested;
    bool closeCompleted;

    volatile bool keepGoing;
    volatile bool running;
    volatile bool stopThread;

    QObject *parentObject;

    bool connected;

    SystemState* state;
};

#endif // TCPDATAOUTPUTTHREAD_H
