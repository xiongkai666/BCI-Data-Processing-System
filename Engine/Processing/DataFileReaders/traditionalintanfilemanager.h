
#ifndef TRADITIONALINTANFILEMANAGER_H
#define TRADITIONALINTANFILEMANAGER_H

#include <QFile>
#include <QString>
#include <vector>
#include "datafilemanager.h"
#include "datafile.h"

using namespace std;

class TraditionalIntanFileManager : public DataFileManager
{
public:
    TraditionalIntanFileManager(const QString& fileName_, IntanHeaderInfo* info_, bool &canReadFile, QString& report,
                                DataFileReader* parent);
    ~TraditionalIntanFileManager();

    int64_t jumpToTimeStamp(int64_t target) override;
    void loadDataFrame() override;
    void loadNextDataBlock();
    QFile* openLiveNotes();

    QString currentFileName() const override;

    struct consecutiveFile {
        QString fileName;
        int64_t numSamplesInFile;
    };

    int64_t blocksPresent() override;

private:
    DataFile* dataFile;
    vector<consecutiveFile> consecutiveFiles;
    int consecutiveFileIndex;
    bool atEndOfCurrentFile;
    int samplesPerDataBlock;
    int positionInDataBlock;

    //  Buffers for loading entire data block into memory.
    vector<int32_t> timeStampBuffer;
    vector<uint16_t> amplifierDataBuffer;
    vector<uint16_t> dcAmplifierDataBuffer;
    vector<uint16_t> stimDataBuffer;
    vector<uint16_t> auxInputDataBuffer;
    vector<uint16_t> supplyVoltageDataBuffer;
    vector<uint16_t> analogInDataBuffer;
    vector<uint16_t> analogOutDataBuffer;
    vector<uint16_t> digitalInDataBuffer;
    vector<uint16_t> digitalOutDataBuffer;
    vector<int16_t> tempSensorBuffer;
};

#endif // TRADITIONALINTANFILEMANAGER_H
