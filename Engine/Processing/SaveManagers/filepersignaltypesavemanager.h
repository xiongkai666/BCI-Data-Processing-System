
#ifndef FILEPERSIGNALTYPESAVEMANAGER_H
#define FILEPERSIGNALTYPESAVEMANAGER_H

#include "waveformfifo.h"
#include "systemstate.h"
#include "savemanager.h"

// One file per signal type file format
class FilePerSignalTypeSaveManager : public SaveManager
{
public:
    FilePerSignalTypeSaveManager(WaveformFifo* waveformFifo_, SystemState* state_);
    ~FilePerSignalTypeSaveManager();

    bool openAllSaveFiles() override;
    int64_t writeToSaveFiles(int numSamples, int timeIndex = 0) override;
    void closeAllSaveFiles() override;
    double bytesPerMinute() const override;

private:
    SaveFile* infoFile;
    SaveFile* timeStampFile;
    SaveFile* amplifierFile;
    SaveFile* lowpassAmplifierFile;
    SaveFile* highpassAmplifierFile;
    SaveFile* spikeFile;
    SaveFile* auxInputFile;
    SaveFile* supplyVoltageFile;
    SaveFile* dcAmplifierFile;
    SaveFile* stimFile;
    SaveFile* analogInputFile;
    SaveFile* analogOutputFile;
    SaveFile* digitalInputFile;
    SaveFile* digitalOutputFile;

    bool saveAuxInsWithAmps;
    bool saveSpikeSnapshot;
    int samplesPreDetect;
    int samplesPostDetect;

    int spikeCounter;

    int mostRecentSpikeTimestamp;
    int tenthOfSecondTimestamps;
    int lastForceFlushTimestamp;
};

#endif // FILEPERSIGNALTYPESAVEMANAGER_H
