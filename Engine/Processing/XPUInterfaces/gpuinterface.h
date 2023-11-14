
#ifndef GPUINTERFACE_H
#define GPUINTERFACE_H

#include <QMessageBox>

#include "abstractxpuinterface.h"

class GPUInterface : public AbstractXPUInterface
{
    Q_OBJECT
public:
    explicit GPUInterface(SystemState* state_, QObject *parent = nullptr);
    ~GPUInterface();

    // Called within class in runDiagnostic(), and externally in waveformprocessorthread
    void processDataBlock(uint16_t* data, uint16_t* lowChunk, uint16_t* wideChunk,
                          uint16_t* highChunk, uint32_t* spikeChunk, uint8_t* spikeIDChunk) override;
    bool setupMemory() override;
    bool cleanupMemory() override;
    void speedTest() override;

private:
    bool findPlatformDevices();
    void initializeKernelMemory();
    bool createKernel(int devIndex);
    void freeKernelMemory();
    void gpuErrorMessage(const QString& errorMessage);

    cl_platform_id* platformIds;
    cl_device_id* deviceIds;
    cl_int ret;
    cl_uint numPlatforms;
    cl_uint numDevices;
    cl_bool deviceAvailable;
    cl_device_id id;
    cl_context context;
    cl_command_queue commandQueue;
    cl_program program;
    cl_kernel kernel;

    cl_mem globalParametersHandle;
    cl_mem filterParametersHandle;
    cl_mem gpuHoopsHandle;
    cl_mem gpuDatablockBuffHandle;
    cl_mem gpuPrevLast2BuffHandle;
    cl_mem gpuPrevHighHandle;
    cl_mem gpuLowBuffHandle;
    cl_mem gpuWideBuffHandle;
    cl_mem gpuHighBuffHandle;
    cl_mem gpuSpikeBuffHandle;
    cl_mem gpuSpikeIDsHandle;
    cl_mem gpuStartSearchPosHandle;
};

#endif // GPUINTERFACE_H
