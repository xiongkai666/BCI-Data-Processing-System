
#ifndef FILEPERSIGNALTYPEMANAGER_H
#define FILEPERSIGNALTYPEMANAGER_H

#include <QFile>
#include <QString>
#include <vector>
#include "datafilemanager.h"
#include "datafile.h"

using namespace std;

class FilePerSignalTypeManager : public DataFileManager
{
public:
    FilePerSignalTypeManager(const QString& fileName_, IntanHeaderInfo* info_, bool& canReadFile, QString& report,
                             DataFileReader* parent);
    ~FilePerSignalTypeManager();

    int64_t jumpToTimeStamp(int64_t target) override;
    void loadDataFrame() override;
    QFile* openLiveNotes();
    int64_t blocksPresent() override;

private:
    DataFile* timeFile;
    DataFile* amplifierFile;
    DataFile* dcAmplifierFile;
    DataFile* stimFile;
    DataFile* auxInputFile;
    DataFile* supplyVoltageFile;
    DataFile* analogInFile;
    DataFile* analogOutFile;
    DataFile* digitalInFile;
    DataFile* digitalOutFile;
    bool auxInAmplifier;
};

#endif // FILEPERSIGNALTYPEMANAGER_H
