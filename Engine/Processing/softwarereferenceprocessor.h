
#ifndef SOFTWAREREFERENCEPROCESSOR_H
#define SOFTWAREREFERENCEPROCESSOR_H

#include <cstdint>
#include <vector>
#include "signalsources.h"
#include "abstractrhxcontroller.h"
#include "rhxdatablock.h"

struct SignalWithSoftwareReference
{
    StreamChannelPair address;
    int referenceIndex;
};


class SoftwareReferenceProcessor
{
public:
    SoftwareReferenceProcessor(ControllerType type_, int numDataStreams_, int numSamples_, SystemState* state_);
    ~SoftwareReferenceProcessor();

    void updateReferenceInfo(const SignalSources* signalSources);
    void applySoftwareReferences(uint16_t* start);

private:
    ControllerType type;
    int numDataStreams;
    int numSamples;
    int dataFrameSizeInWords;
    int misoWordSize;

    SystemState* state;

    // Reference signals consisting of a single channel.
    vector<SignalWithSoftwareReference> signalListSingleReference;
    vector<StreamChannelPair> singleReferenceList;
    vector<int*> singleReferenceData;

    // Reference signals consisting of an average of multiple channels.
    vector<SignalWithSoftwareReference> signalListMultiReference;
    vector<vector<StreamChannelPair> > multiReferenceList;
    vector<int*> multiReferenceData;

    int findSingleReference(StreamChannelPair singleRef, const vector<StreamChannelPair>& singleRefList) const;
    int findMultiReference(const vector<StreamChannelPair>& multiRef, const vector<vector<StreamChannelPair> >& multiRefList) const;
    void calculateReferenceSignals(const uint16_t* start);
    void readReferenceSignal(StreamChannelPair address, int* destination, const uint16_t* start);
    void addReferenceSignal(StreamChannelPair address, int* destination, const uint16_t* start);
    void subtractReferenceSignal(StreamChannelPair address, const int* refSignal, uint16_t* start);
    void readReferenceSamples(vector<StreamChannelPair> &addresses, int t, vector<int> &destination, const uint16_t* start);
    int calculateMedian(vector<int> &data);
    void deleteDataArrays();

};

#endif // SOFTWAREREFERENCEPROCESSOR_H
