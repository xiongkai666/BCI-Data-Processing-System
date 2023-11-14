
#ifndef USBDATATHREAD_H
#define USBDATATHREAD_H

#include <QObject>
#include <QThread>
#include "rhxdatablock.h"
#include "abstractrhxcontroller.h"
#include "datastreamfifo.h"

const int BufferSizeInBlocks = 32;

class USBDataThread : public QThread
{
    Q_OBJECT
public:
    explicit USBDataThread(AbstractRHXController* controller_, DataStreamFifo* usbFifo_,  QObject *parent = nullptr);
    ~USBDataThread();

    bool errorChecking;

    void run() override;
    void startRunning();
    void stopRunning();
    bool isActive() const;
    void close();
    void setNumUsbBlocksToRead(int numUsbBlocksToRead_);
    void setErrorCheckingEnabled(bool enabled);

    bool memoryWasAllocated(double& memoryRequestedGB) const { memoryRequestedGB += memoryNeededGB; return memoryAllocated; }

signals:
    void hardwareFifoReport(double percentFull);

private:
    AbstractRHXController* controller;
    DataStreamFifo* usbFifo;
    volatile bool keepGoing;
    volatile bool running;
    volatile bool stopThread;
    volatile int numUsbBlocksToRead;

    uint8_t* usbBuffer;
    int bufferSize;
    int usbBufferIndex;

    bool memoryAllocated;
    double memoryNeededGB;
};

#endif // USBDATATHREAD_H
