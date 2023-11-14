
#ifndef WAVEFORMDISPLAYMANAGER_H
#define WAVEFORMDISPLAYMANAGER_H

#include <map>
#include <string>
#include "minmax.h"
#include "waveformfifo.h"
#include "systemstate.h"

using namespace std;

const float ScaleFactorY = 10.0F;

enum YScaleType {
    WidebandYScale,
    LowpassYScale,
    HighpassYScale,
    DCYScale,
    AuxInputYScale,
    SupplyVoltageYScale,
    AnalogIOYScale,
    DigitalIOYScale,
    RasterYScale,
    UnknownYScale
};

struct YScaleUsed
{
public:
    YScaleUsed() :
        widepassYScaleUsed(false),
        lowpassYScaleUsed(false),
        highpassYScaleUsed(false),
        auxInputYScaleUsed(false),
        dcYScaleUsed(false),
        analogIOYScaleUsed(false)
    {}

    bool widepassYScaleUsed;
    bool lowpassYScaleUsed;
    bool highpassYScaleUsed;
    bool auxInputYScaleUsed;
    bool dcYScaleUsed;
    bool analogIOYScaleUsed;
};

struct WaveformDisplayDataStore
{
public:
    WaveformDisplayDataStore() :
        hasStimFlags(false),
        isRaster(false),
        yScaleType(UnknownYScale)
    {}

    // Internal state
    bool hasStimFlags;
    bool isRaster;
    YScaleType yScaleType;
    bool hasAlreadyLoaded;
    bool isOutOfDate;

    // Data stores: raw y coordinates in sequence
    vector<MinMax<float> > yMinMaxData;
    vector<float> yData;
    vector<uint16_t> stimFlags;
    vector<uint16_t> rasterData;

    // Data stores: screen coordinates
    vector<QLineF> verticalLines;
    vector<QPointF> points;
};

class WaveformDisplayManager
{
public:
    WaveformDisplayManager(SystemState* state_, int maxWidthInPixels_, int numRefreshZones_);
    ~WaveformDisplayManager();

    bool addWaveform(const QString& waveName, bool isStim = false, bool isRaster = false);  // Return false if waveName is already in waveform list.
    bool removeWaveform(const QString& waveName);  // Returns false if waveName is not in waveform list.
    inline void removeAllWaveforms() { data.clear(); }

    inline void setMaxWidthInPixels(int maxWidthInPixels_) { maxWidthInPixels = maxWidthInPixels_; calculateParameters(); }
    inline void setTScaleInMsec(int tScaleInMsec_, int numRefreshZones_ = 1) { tScaleInMsec = tScaleInMsec_;
                                                                               numRefreshZones = numRefreshZones_;
                                                                               calculateParameters(); }
    void resetAll();

    void prepForLoadingNewData();
    void prepForLoadingOldData(int startTime);
    void prepForLoadingDataDirect();
    void loadNewData(const WaveformFifo* waveformFifo, const QString& waveName) const;
    void loadOldData(const WaveformFifo* waveformFifo, const QString& waveName, int startTime) const;
    void loadDataDirect(QVector<double> &ampData, const QString& waveName);
    YScaleUsed finishLoading();

    float getYScaleFactor(YScaleType yScaleType) const;
    float getYScaleFactor(const QString& waveName) const;

    void clearActiveSectionOfRect(QPainter &painter, QRect fullRect);

    void draw(QPainter &painter, const QString& waveName, QPoint position, QColor color);
    void drawDivider(QPainter &painter, int yPos, int xStart, int xEnd);

    inline int getWidthInPixels() const { return widthInPixels; }
    int getRefreshXPosition() const;
    int getValidDataXPosition() const;

    inline int getSamplesPerRefresh() const { return samplesPerZone; }
    inline int getSamplesPerRefresh(int tScaleInMsec_, int numRefreshZones_) const
        { return round(sampleRate * ((double)tScaleInMsec_ / 1000.0) / (double)numRefreshZones_); }

    inline int getSamplesPerFullRefresh() const { return samplesPerZone * numRefreshZones; }
//    inline int getSamplesPerFullRefresh(int tScaleInMsec_, int numRefreshZones_) const
//        { int samplesPerZone_ = round(sampleRate * ((double)tScaleInMsec_ / 1000.0) / (double)numRefreshZones_);
//          return samplesPerZone_* numRefreshZones_; }

    void singlePlotFullRedrawFinished();
    void singlePlotFullResetFinished();

    bool needsFullRedraw;
    bool needsFullReset;
    int numColumns;

private:
    SystemState *state;

    int finishedRedraws;
    int finishedResets;

    // Input parameters
    int maxWidthInPixels;
    int numRefreshZones;
    double sampleRate;
    int tScaleInMsec;

    // Calculated display data parameters
    int zoneWidthInPixels;
    int widthInPixels;
    int samplesPerZone;
    float pixelsPerSample;
    bool useVerticalLines;
    int length;
    int zoneLength;

    // State while running
    bool oldDataPresent;
    bool sweepFirstTime;
    int validDataIndex;

    // Waveform data mapped to waveform name
    map<string, WaveformDisplayDataStore*> data;

    const QColor StimColor = QColor(255, 155, 155);
    const QColor ComplianceLimitColor = QColor(255, 0, 0);
    const QColor AmpSettleColor = QColor(255, 255, 215);
    const QColor ChargeRecovColor = QColor(215, 255, 215);
    QColor stimFlagsColor(uint16_t stimFlags, QColor backgroundColor) const;
    QColor supplyVoltageColor(MinMax<float> yMinMax) const;

    void calculateParameters();

    void getMinMaxData(MinMax<float> &init, QVector<double> &ampData, int timeIndex, int samples) const;

    void loadDataSegment(const WaveformFifo* waveformFifo, const QString& waveName,  WaveformDisplayDataStore* ds,
                         int displayStartPos, int displayEndPos, int startTime) const;

    void loadDataSegmentDirect(QVector<double> &ampData, WaveformDisplayDataStore* ds);
    void reset(WaveformDisplayDataStore* ds);
};

#endif // WAVEFORMDISPLAYMANAGER_H
