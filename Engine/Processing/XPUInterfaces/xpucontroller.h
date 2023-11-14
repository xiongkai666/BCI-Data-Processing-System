
#ifndef XPUCONTROLLER_H
#define XPUCONTROLLER_H
#include <QObject>

#include "systemstate.h"
#include "signalsources.h"
#include "cpuinterface.h"
#include "gpuinterface.h"

class XPUController  : public QObject
{
    Q_OBJECT
public:
    explicit XPUController(SystemState* state_, bool useOpenCL_, QObject *parent = nullptr);
    ~XPUController();

    void resetPrev();
    void processDataBlock(uint16_t* data, uint16_t* lowChunk, uint16_t* wideChunk,
                          uint16_t* highChunk, uint32_t* spikeChunk, uint8_t* spikeIDChunk);
    void updateNumStreams(int numStreams);
    void runDiagnostic();

private slots:
    void updateFromState();

private:
    void compare();

    bool useOpenCL;

    SystemState* state;
    CPUInterface *cpuInterface;
    GPUInterface *gpuInterface;
    AbstractXPUInterface* activeInterface;
    int usedXPUIndex;
};

#endif // XPUCONTROLLER_H
