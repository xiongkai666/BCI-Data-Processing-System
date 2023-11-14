
#ifndef FILEPERCHANNELSAVEMANAGER_H
#define FILEPERCHANNELSAVEMANAGER_H

#include "waveformfifo.h"
#include "systemstate.h"
#include "savemanager.h"

// One file per channel file format
class FilePerChannelSaveManager : public SaveManager
{
public:
    FilePerChannelSaveManager(WaveformFifo* waveformFifo_, SystemState* state_);
    ~FilePerChannelSaveManager();

    bool openAllSaveFiles() override;
    int64_t writeToSaveFiles(int numSamples, int timeIndex = 0) override;
    void closeAllSaveFiles() override;
    double bytesPerMinute() const override;

private:
    SaveFile* infoFile;
    SaveFile* timeStampFile;
    vector<SaveFile*> amplifierFiles;
    vector<SaveFile*> lowpassAmplifierFiles;
    vector<SaveFile*> highpassAmplifierFiles;
    vector<SaveFile*> spikeFiles;
    vector<SaveFile*> auxInputFiles;
    vector<SaveFile*> supplyVoltageFiles;
    vector<SaveFile*> dcAmplifierFiles;
    vector<SaveFile*> stimFiles;
    vector<SaveFile*> analogInputFiles;
    vector<SaveFile*> analogOutputFiles;
    vector<SaveFile*> digitalInputFiles;
    vector<int> digitalInputFileIndices;
    vector<SaveFile*> digitalOutputFiles;
    vector<int> digitalOutputFileIndices;

    bool saveSpikeSnapshot;
    int samplesPreDetect;
    int samplesPostDetect;

    int *spikeCounter;

    int *mostRecentSpikeTimestamp;
    int tenthOfSecondTimestamps;
    int *lastForceFlushTimestamp;
};

#endif // FILEPERCHANNELSAVEMANAGER_H
