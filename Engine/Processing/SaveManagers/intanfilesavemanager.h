
#ifndef INTANFILESAVEMANAGER_H
#define INTANFILESAVEMANAGER_H

#include "waveformfifo.h"
#include "systemstate.h"
#include "savemanager.h"

// Intan save file format (*.rhd, *.rhs)
class IntanFileSaveManager : public SaveManager
{
public:
    IntanFileSaveManager(WaveformFifo* waveformFifo_, SystemState* state_);
    ~IntanFileSaveManager();

    bool openAllSaveFiles() override;
    int64_t writeToSaveFiles(int numSamples, int timeIndex = 0) override;
    void closeAllSaveFiles() override;
    bool mustSaveCompleteDataBlocks() const override { return true; }
    int maxSamplesInFile() const override;
    double bytesPerMinute() const override;

private:
    SaveFile* saveFile;

    QString subdirName;
};

#endif // INTANFILESAVEMANAGER_H
