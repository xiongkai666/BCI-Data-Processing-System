
#include "xpucontroller.h"

XPUController::XPUController(SystemState *state_, bool useOpenCL_, QObject *parent) :
    QObject(parent),
    state(state_),
    usedXPUIndex(-1),
    useOpenCL(useOpenCL_)
{
    state->writeToLog("Entered XPUController ctor");
    connect(state, SIGNAL(stateChanged()), this, SLOT(updateFromState()));

    gpuInterface = new GPUInterface(state, this);
    state->writeToLog("Created GPUInterface");
    cpuInterface = new CPUInterface(state, this);
    state->writeToLog("Created CPUInterface");

    activeInterface = cpuInterface;
}

XPUController::~XPUController()
{
    delete gpuInterface;
    delete cpuInterface;
}

void XPUController::resetPrev()
{
    activeInterface->resetPrev();
}

void XPUController::processDataBlock(uint16_t *data, uint16_t *lowChunk, uint16_t *wideChunk,
                                          uint16_t *highChunk, uint32_t *spikeChunk, uint8_t *spikeIDChunk)
{
    activeInterface->processDataBlock(data, lowChunk, wideChunk, highChunk, spikeChunk, spikeIDChunk);
}

void XPUController::updateNumStreams(int numStreams)
{
    cpuInterface->updateNumStreams(numStreams);
    gpuInterface->updateNumStreams(numStreams);
}

void XPUController::runDiagnostic()
{

    state->gpuList.clear();

    cpuInterface->speedTest();
    if (useOpenCL) {
        gpuInterface->speedTest();
    }
    compare();
}

void XPUController::compare()
{
    // Compare times of each CPU and each entry of gpuList, and update their ranking.
    float prevBestTime = -1.0f;
    int rankIndex = 1;

    int bestIndex = -1;

    while (rankIndex <= state->gpuList.size() + 1) {
        float bestTime = std::numeric_limits<float>::max();
        if (state->cpuInfo.diagnosticTime < bestTime && state->cpuInfo.diagnosticTime > prevBestTime) {
            bestTime = state->cpuInfo.diagnosticTime;
            bestIndex = 0;
        }
        for (int j = 0; j < state->gpuList.size(); j++) {
            if (state->gpuList[j].diagnosticTime < bestTime && state->gpuList[j].diagnosticTime > prevBestTime) {
                bestTime = state->gpuList[j].diagnosticTime;
                bestIndex = j + 1;
            }
        }
        if (bestIndex == 0) {
            state->cpuInfo.rank = rankIndex++;
            if (state->cpuInfo.rank == 1) {
                state->cpuInfo.used = true;
            }
            prevBestTime = state->cpuInfo.diagnosticTime;
        } else {
            state->gpuList[bestIndex - 1].rank = rankIndex++;
            if (state->gpuList[bestIndex - 1].rank == 1) {
                state->gpuList[bestIndex - 1].used = true;
            }
            prevBestTime = state->gpuList[bestIndex - 1].diagnosticTime;
        }
    }

    updateFromState();
}

void XPUController::updateFromState()
{
    // If used XPU has changed in state, then reflect that here.
    if (state->usedXPUIndex() != usedXPUIndex) {
        activeInterface->cleanupMemory();
        usedXPUIndex = state->usedXPUIndex();
        activeInterface = (usedXPUIndex == 0) ? activeInterface = cpuInterface : activeInterface = gpuInterface;
        activeInterface->setupMemory();
    }
    activeInterface->updateFromState();
}
