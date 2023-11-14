
#ifndef MULTICOLUMNDISPLAY_H
#define MULTICOLUMNDISPLAY_H

#include <QtWidgets>
#include "waveformdisplaymanager.h"
#include "waveformdisplaycolumn.h"

class MultiColumnDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit MultiColumnDisplay(ControllerInterface* controllerInterface_, SystemState *state_, QWidget *parent = nullptr);
    ~MultiColumnDisplay();

    inline int numColumns() const { return (int) displayColumns.size(); }
    int numVisibleColumns() const;
    inline int maxNumColumns() const { return MaxNumColumns; }
    QString getSelectedPort(int column) const { return displayColumns[column]->getSelectedPort(); }
    void setSelectedPort(int column, const QString& portName) { displayColumns[column]->setSelectedPort(portName); }

    bool addColumn(int position);
    bool deleteColumn(int position, bool silent = false);
    bool moveColumnLeft(int position);
    bool moveColumnRight(int position);

    void updateHideAndDeleteButtons();

    void setWaveformWidth(int width);

    YScaleUsed loadWaveformData(WaveformFifo* waveformFifo);
    YScaleUsed loadWaveformDataFromMemory(WaveformFifo* waveformFifo, int startTime, bool loadAll = false);
    YScaleUsed loadWaveformDataDirectAmp(QVector<QVector<QVector<double>>> &ampData, QVector<QVector<QString>> &ampChannelNames);
    YScaleUsed loadWaveformDataDirectAmpDC(QVector<QVector<QVector<double>>> &ampData, QVector<QVector<QString>> &ampChannelNames,
                                      QVector<QVector<QVector<double>>> &dcData, QVector<QVector<QString>> &dcChannelNames);
    void reset();

    inline int getSamplesPerRefresh() const { return waveformManager->getSamplesPerRefresh(); }
    int getMaxSamplesPerRefresh() const;

    inline int getSamplesPerFullRefresh() const { return waveformManager->getSamplesPerFullRefresh(); }

    bool groupIsPossible() const;
    bool ungroupIsPossible() const;

    void enableSelectedChannels(bool enabled);
    void group();
    void ungroup();

    void updateForRun();
    void updateForLoad();
    void updateForStop();
    void updateForRescan();

    void addWaveforms();

    QStringList getPinnedWaveNames(int column) const { return displayColumns[column]->getPinnedWaveNames(); }
    void setPinnedWaveforms(int column, const QStringList& pinnedWaveNames) { displayColumns[column]->setPinnedWaveforms(pinnedWaveNames); }

    bool arePinnedShown(int column) const { return displayColumns[column]->arePinnedShown(); }
    void setShowPinned(int column, bool showPinned);

    bool isColumnVisible(int column) const { return displayColumns[column]->isColumnVisible();}
    void setColumnVisible(int column, bool visible);

    inline ScrollBarState getScrollBarState(int column) const { return displayColumns[column]->getScrollBarState(); }
    inline void restoreScrollBarState(int column, const ScrollBarState& state) { displayColumns[column]->restoreScrollBarState(state); }

    void updatePortSelectionBoxes(bool switchToFirstPort = false);

    QString getDisplaySettingsString() const;
    void restoreFromDisplaySettingsString(const QString& settings);

public slots:
    void updateFromState();

private:
    ControllerInterface* controllerInterface;
    SystemState* state;

    WaveformDisplayManager* waveformManager;
    vector<int> numRefreshZones;

    //static const int MaxNumColumns = 10;
    static const int MaxNumColumns = 16;
    QList<WaveformDisplayColumn*> displayColumns;

    int tScaleFormerIndex;
    bool rollModeFormerValue;

    void updateColumnIndices();
    void updateLayout();
};

#endif // MULTICOLUMNDISPLAY_H
