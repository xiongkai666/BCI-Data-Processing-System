
#include <iostream>
#include "datafile.h"


DataFile::DataFile(const QString& fileName_) :
    fileName(fileName_)
{
    file = nullptr;
    dataStream = nullptr;

    file = new QFile(fileName);
    if (!file->open(QIODevice::ReadOnly)) {
        open = false;
        cerr << "DataFile: Cannot open file " << fileName.toStdString() << " for reading: " <<
                qPrintable(file->errorString()) << '\n';
    } else {
        open = true;
    }
    dataStream = new QDataStream(file);

    // Maintain bit-level compatibility with existing code.
    dataStream->setVersion(QDataStream::Qt_5_11);

    // Set to little endian mode for compatibilty with MATLAB, which is little endian on all platforms.
    dataStream->setByteOrder(QDataStream::LittleEndian);
}

DataFile::~DataFile()
{
    close();
}

void DataFile::close()
{
    if (!file) return;
    file->close();
    if (dataStream) {
        delete dataStream;
        dataStream = nullptr;
    }
    delete file;
    file = nullptr;
}
