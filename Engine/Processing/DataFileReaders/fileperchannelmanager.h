
#ifndef FILEPERCHANNELMANAGER_H
#define FILEPERCHANNELMANAGER_H

#include <QFile>
#include <QString>
#include <vector>
#include "datafilemanager.h"
#include "datafile.h"

using namespace std;

class SystemState;


class FilePerChannelManager : public DataFileManager
{
public:
    FilePerChannelManager(const QString& fileName_, IntanHeaderInfo* info_, bool& canReadFile, QString& report,
                          DataFileReader* parent);
    ~FilePerChannelManager();

    long readDataBlocksRaw(int numBlocks, uint8_t* buffer);
    int64_t getLastTimeStamp() override;
    int64_t jumpToTimeStamp(int64_t target) override;
    void loadDataFrame() override;
    QFile* openLiveNotes();
    int64_t blocksPresent() override;

private:
    DataFile* timeFile;
    vector<vector<DataFile*> > amplifierFiles;
    vector<vector<DataFile*> > dcAmplifierFiles;
    vector<vector<DataFile*> > stimFiles;
    vector<vector<DataFile*> > auxInputFiles;
    vector<DataFile*> supplyVoltageFiles;
    vector<DataFile*> analogInFiles;
    vector<DataFile*> analogOutFiles;
    vector<DataFile*> digitalInFiles;
    vector<DataFile*> digitalOutFiles;

    void updateEndOfData();
};

#endif // FILEPERCHANNELMANAGER_H
