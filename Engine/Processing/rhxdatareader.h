
#ifndef RHXDATAREADER_H
#define RHXDATAREADER_H

#include <cstdint>
#include "rhxdatablock.h"

class RHXDataReader
{
public:
    RHXDataReader(ControllerType type_, int numDataStreams_, const uint16_t* start_, int numSamples_);

    void setNumDataStreams(int numDataStreams_);
    void setStart(const uint16_t* start_) { start = start_; }
    void setNumSamples(int numSamples_) { numSamples = numSamples_; }

    int readTimeStampData(uint32_t* buffer) const;
    void readAmplifierData(float* buffer, int stream, int channel) const;
    void readDcAmplifierData(float* buffer, int stream, int channel) const;
    void readAuxInData(float* buffer, int stream, int auxChannel);
    void readSupplyVoltageData(float* buffer, int stream) const;
    void readBoardAdcData(float* buffer, int channel) const;
    void readBoardDacData(float* buffer, int channel) const;

    void readDigInData(float* buffer, int channel) const;   // Read individual digital input.
    void readDigOutData(float* buffer, int channel) const;  // Read individual digital output.

    void readDigInData(uint16_t* buffer) const;             // Read all 16 digital inputs at once.
    void readDigOutData(uint16_t* buffer) const;            // Read all 16 digital outputs at once.

    // Read stim parameters for individual channels.
    void readComplianceLimitData(uint16_t* buffer, int stream, int channel) const;
    void readStimOnData(uint16_t* buffer, int stream, int channel) const;
    void readStimPolData(uint16_t* buffer, int stream, int channel) const;
    void readAmpSettleData(uint16_t* buffer, int stream, int channel) const;
    void readChargeRecovData(uint16_t* buffer, int stream, int channel) const;

    // Read stim parameters for all 16 channels in each data stream.
    void readComplianceLimitData(uint16_t* buffer, int stream) const;
    void readStimOnData(uint16_t* buffer, int stream) const;
    void readStimPolData(uint16_t* buffer, int stream) const;
    void readAmpSettleData(uint16_t* buffer, int stream) const;
    void readChargeRecovData(uint16_t* buffer, int stream) const;

    // Read ALL stim parameters for individual channels.
    void readStimParamData(uint16_t* buffer, int stream, int channel) const;

private:
    ControllerType type;
    int numDataStreams;
    const uint16_t* start;
    int numSamples;
    int dataFrameSizeInWords;
    int channelsPerStream;
    int numAuxChannels;
    int auxChFrameOffset;
};

#endif // RHXDATAREADER_H
