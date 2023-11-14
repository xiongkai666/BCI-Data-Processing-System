
#ifndef ABSTRACTXPUINTERFACE_H
#define ABSTRACTXPUINTERFACE_H

#include <QObject>
#ifdef __APPLE__
    #include <OpenCL/opencl.h>
#else
    #include <CL/cl.h>
#endif
#include <mutex>
#include "systemstate.h"
#include "filter.h"

#define MAX_SOURCE_SIZE (0x100000) // memory allocated for kernel.cl source code

typedef struct _HoopInfo
{
    cl_float tA;
    cl_float yA;
    cl_float tB;
    cl_float yB;
} HoopInfoStruct;

typedef struct _UnitHoops
{
    HoopInfoStruct hoopInfo[4];
} UnitHoopsStruct;

typedef struct _Channel_Hoops
{
    UnitHoopsStruct unitHoops[4];
    cl_float threshold;
    cl_char useHoops; // Ideally would be bool, but bool can't be passed to OpenCL. 1 = true, 0 = false
} ChannelHoopsStruct;

typedef struct _FilterIterationParams
{
    cl_float b2;
    cl_float b1;
    cl_float b0;
    cl_float a2;
    cl_float a1;
} FilterIterationParamStruct;

typedef struct _GlobalParamStruct
{
    cl_ushort wordsPerFrame;
    cl_char type;
    cl_char numStreams;
    cl_char snippetSize;
    cl_float sampleRate;
    cl_float spikeMax;
    cl_char spikeMaxEnabled;
} GlobalParamStruct;

typedef struct _FilterParams
{
    cl_char lowOrder;
    cl_char highOrder;

    FilterIterationParamStruct notchParams;
    FilterIterationParamStruct lowParams[4];
    FilterIterationParamStruct highParams[4];
} FilterParamStruct;

class AbstractXPUInterface : public QObject
{
    Q_OBJECT
public:
    explicit AbstractXPUInterface(SystemState* state_, QObject *parent = nullptr);

    void resetPrev();
    virtual void processDataBlock(uint16_t* data, uint16_t* lowChunk, uint16_t* wideChunk,
                                  uint16_t* highChunk, uint32_t* spikeChunk, uint8_t* spikeIDChunk) = 0;
    void updateNumStreams(int numStreams_);
    void updateFromState();
    virtual void speedTest() = 0;
    virtual bool setupMemory() = 0;
    virtual bool cleanupMemory() = 0;

protected:
    virtual void updateMemory();
    void runDiagnostic(int XPUIndex);
    void updateFilters();
    virtual void updateHoopsVariables();
    virtual void updateFilterConstArray();
    virtual void updateConstChars();
    virtual void updateConstFloats();
    mutex filterMutex;

    bool allocated;
    double sampleRate;
    SystemState* state;
    int numStreams;
    ControllerType type;
    static const int DiagnosticBlocks = 300;
    const int SnippetsPerBlock = (int) (ceil((double) FramesPerBlock / (double) SnippetSize) + 1.0);
    int totalSnippetsPerBlock;
    int wordsPerFrame;
    int channelsPerStream;
    int wordsPerBlock;
    int totalSamplesPerBlock;
    GlobalParamStruct globalParameters;
    FilterParamStruct filterParameters;
    int channels;

    uint32_t* spike;
    uint8_t* spikeIDs;
    float* prevLast2;
    uint16_t* startSearchPos;
    ChannelHoopsStruct* hoops;

    uint16_t* parsedPrevHighOriginal;
    uint16_t* parsedPrevHigh;
    uint64_t* inputIndex, outputIndex, spikeIndex;

private:
    void calculateNotchConstants();
    void calculateLowConstants();
    void calculateHighConstants();
};

#endif //ABSTRACTXPUINTERFACE_H
