
#ifndef DATAFILEMANAGER_H
#define DATAFILEMANAGER_H

#include <QString>
#include <vector>
#include <map>

using namespace std;

struct IntanHeaderInfo;
class DataFileReader;

class DataFileManager
{
public:
    DataFileManager(const QString& fileName_, IntanHeaderInfo* info_, DataFileReader* parent);
    virtual ~DataFileManager();

    int64_t getFirstTimeStamp() const { return firstTimeStamp; }
    virtual int64_t getLastTimeStamp() { return lastTimeStamp; }
    //int64_t getLastTimeStamp() const { return lastTimeStamp; }
    int64_t getCurrentTimeStamp() const { return readIndex + firstTimeStamp; }
    int64_t getTotalNumSamples() const { return totalNumSamples; }

    QString timeString(int64_t samples);

    bool liveNotesLoaded() const { return !liveNotes.empty(); }
    QString getLastLiveNote();

    virtual long readDataBlocksRaw(int numBlocks, uint8_t* buffer);
    virtual int64_t jumpToTimeStamp(int64_t target) = 0;
    virtual void loadDataFrame() = 0;
    void readLiveNotes(QFile* liveNotesFile);

    virtual QString currentFileName() const { return fileName; }

    struct StimData {
        StimData() : amplitude(0), stimOn(0), stimPol(0), ampSettle(0), chargeRecov(0), complianceLimit(0) {}
        uint16_t amplitude;
        uint16_t stimOn;
        uint16_t stimPol;
        uint16_t ampSettle;
        uint16_t chargeRecov;
        uint16_t complianceLimit;
        void clear() { amplitude = 0; stimOn = 0; stimPol = 0; ampSettle = 0; chargeRecov = 0; complianceLimit = 0; }
    };

    virtual int64_t blocksPresent() = 0;

protected:
    QString fileName;
    IntanHeaderInfo* info;
    DataFileReader* dataFileReader;

    vector<vector<bool> > amplifierWasSaved;
    vector<vector<bool> > dcAmplifierWasSaved;
    vector<vector<bool> > stimWasSaved;
    vector<vector<bool> > auxInputWasSaved;
    vector<bool> supplyVoltageWasSaved;
    vector<bool> analogInWasSaved;
    vector<bool> analogOutWasSaved;
    vector<bool> digitalInWasSaved;
    vector<bool> digitalOutWasSaved;

    int64_t totalNumSamples;
    int64_t readIndex;
    int64_t firstTimeStamp;
    int64_t lastTimeStamp;

    // Single data frame
    int32_t timeStamp;
    vector<vector<uint16_t> > amplifierData;
    vector<vector<uint16_t> > dcAmplifierData;
    vector<vector<StimData> > stimData;
    vector<vector<bool> > posStimAmplitudeFound;
    vector<vector<bool> > negStimAmplitudeFound;
    vector<vector<uint16_t> > auxInputData;
    vector<uint16_t> supplyVoltageData;
    vector<uint16_t> analogInData;
    vector<uint16_t> analogOutData;
    uint16_t digitalInData;
    uint16_t digitalOutData;

    // Live notes
    map<string, string> liveNotes;
    QString lastLiveNote;
};

#endif // DATAFILEMANAGER_H
