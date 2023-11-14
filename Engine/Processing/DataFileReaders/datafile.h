
#ifndef DATAFILE_H
#define DATAFILE_H

#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QDataStream>
#include <QString>

using namespace std;

class DataFile
{
public:
    DataFile(const QString& fileName_);
    ~DataFile();

    QString getFileName() const { return QFileInfo(fileName).baseName(); }
    int64_t fileSize() const { return file->size(); }
    int64_t pos() const { return file->pos(); }
    void seek(int64_t pos) { file->seek(pos); }
    bool isOpen() const { return open; }
    bool atEnd() const { return file->atEnd(); }
    uint16_t readWord() const { uint16_t word; *dataStream >> word; return word; }
    int16_t readSignedWord() const { int16_t word; *dataStream >> word; return word; }
    int32_t readTimeStamp() const { int32_t timeStamp; *dataStream >> timeStamp; return timeStamp; }
    void close();

private:
    QString fileName;
    QFile* file;
    QDataStream* dataStream;
    bool open;
};

#endif // DATAFILE_H
