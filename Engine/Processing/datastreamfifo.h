
#ifndef DATASTREAMFIFO_H
#define DATASTREAMFIFO_H

#include "semaphore.h"

class DataStreamFifo
{
public:
    DataStreamFifo(int bufferSize_, int maxReadLength_ = 0);
    ~DataStreamFifo();

    bool writeToBuffer(const uint8_t* dataSource, int numWords);
    bool dataAvailable(unsigned int numWords) const;

    bool readFromBuffer(uint16_t *dataSink, int numWords);
    uint16_t* pointerToData(int numWordsToBeRead_);
    void freeData();

    void resetBuffer();
    int wordsAvailable() const;
    double percentFull() const;

    bool memoryWasAllocated(double& memoryRequestedGB) const { memoryRequestedGB += memoryNeededGB; return memoryAllocated; }

private:
    uint16_t* buffer;
    int bufferSize;
    int maxReadLength;
    int numWordsToBeRead;
    Semaphore freeWords;
    Semaphore usedWords;
    int bufferWriteIndex;
    int bufferReadIndex;

    bool memoryAllocated;
    double memoryNeededGB;
};

#endif // DATASTREAMFIFO_H
