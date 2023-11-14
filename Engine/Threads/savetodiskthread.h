
#ifndef SAVETODISKTHREAD_H
#define SAVETODISKTHREAD_H

#include <QObject>
#include <QThread>
#include <atomic>
#include "waveformfifo.h"
#include "systemstate.h"
#include "signalsources.h"
#include "rhxdatablock.h"
#include "savemanager.h"

using namespace std;

class SaveToDiskThread : public QThread
{
    Q_OBJECT
public:
    explicit SaveToDiskThread(WaveformFifo *waveformFifo_, SystemState *state_, QObject *parent = nullptr);
    ~SaveToDiskThread();

    void run() override;
    void startRunning();
    void stopRunning();
    bool isActive() const;
    void close();

    int64_t getTotalRecordedSamples() const { return totalRecordedSamples; }

    enum FindTriggerMode {
        FindTriggerBegin,
        FindTriggerEnd
    };

signals:
    void setStatusBar(QString);
    void setTimeLabel(QString);
    void sendSetCommand(QString, QString);
    void error(QString);

public slots:
    void saveLiveNote(const QString& note);
    void setPosStimAmplitude(int stream, int channel, int amplitude);
    void setNegStimAmplitude(int stream, int channel, int amplitude);

private:
    WaveformFifo* waveformFifo;
    SystemState* state;
    SaveManager* saveManager;

    volatile bool keepGoing;
    volatile bool running;
    volatile bool stopThread;

    vector<float*> boardAdcWaveform;
    uint16_t* boardDigitalInWaveform;

    bool digitalTrigger;
    int triggerChannel;
    bool triggerOnHigh;
    float analogTriggerThreshold;

    atomic<int64_t> totalRecordedSamples;

    int findTrigger(int numSamples, FindTriggerMode mode);
    void setStatusBarRecording(double bytesPerMinute, const QString& dateTimeStamp, int64_t totalBytesSaved);
    void setStatusBarWaitForTrigger();
};

#endif // SAVETODISKTHREAD_H
