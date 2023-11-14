
#ifndef CPUINTERFACE_H
#define CPUINTERFACE_H

#include "abstractxpuinterface.h"

typedef struct _UnitDetection
{
    bool hoops[4];
} HoopDetectionStruct;

typedef struct _ChannelDetection
{
    HoopDetectionStruct units[4];
    bool maxSurpassed;
} ChannelDetectionStruct;

class CPUInterface : public AbstractXPUInterface
{
    Q_OBJECT
public:
    explicit CPUInterface(SystemState* state_, QObject *parent = nullptr);
    ~CPUInterface();

    void processDataBlock(uint16_t* data, uint16_t* lowChunk, uint16_t* wideChunk,
                          uint16_t* highChunk, uint32_t* spikeChunk, uint8_t* spikeIDChunk) override;
    void speedTest() override;
    bool setupMemory() override;
    bool cleanupMemory() override;

private:
    void initializeMemory();
    void freeMemory();
};

#endif // CPUINTERFACE_H
