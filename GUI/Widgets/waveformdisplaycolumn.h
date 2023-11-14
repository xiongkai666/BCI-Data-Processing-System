
#ifndef WAVEFORMDISPLAYCOLUMN_H
#define WAVEFORMDISPLAYCOLUMN_H

#include "multiwaveformplot.h"
#include <QtWidgets>

using namespace std;

class MultiColumnDisplay;

class WaveformDisplayColumn : public QWidget
{
    Q_OBJECT
public:
    explicit WaveformDisplayColumn(int columnIndex_, WaveformDisplayManager* waveformManager,
                                   ControllerInterface* controllerInterface_, SystemState *state_,
                                   MultiColumnDisplay *parent_);
    ~WaveformDisplayColumn();

    void setIndex(int columnIndex_) { columnIndex = columnIndex_; waveformPlot->setIndex(columnIndex_); }
    void enableHideAndDelete(bool enable);
    void enableMoveLeft(bool enable) { moveLeftButton->setEnabled(enable); }
    void enableMoveRight(bool enable) { moveRightButton->setEnabled(enable); }

    bool isColumnVisible() const { return visible; }

    bool groupIsPossible() const { return waveformPlot->groupIsPossible(); }
    bool ungroupIsPossible() const { return waveformPlot->ungroupIsPossible(); }
    void group() { waveformPlot->group(); }
    void ungroup() { waveformPlot->ungroup(); }

    void setWaveformWidth(int width);
    void updateNow() { waveformPlot->updateNow(); }

    inline void loadWaveformData(WaveformFifo* waveformFifo) { waveformPlot->loadWaveformData(waveformFifo); }
    inline void loadWaveformDataFromMemory(WaveformFifo* waveformFifo, int startTime, bool loadAll = false)
        { waveformPlot->loadWaveformDataFromMemory(waveformFifo, startTime, loadAll); }
    inline void loadWaveformDataDirect(QVector<QVector<QVector<double>>> &ampData, QVector<QVector<QString>> &ampChannelNames)
        { waveformPlot->loadWaveformDataDirect(ampData, ampChannelNames); }

    QString getSelectedPort() const { return portComboBox->currentText().section(" (", 0, 0); }
    void setSelectedPort(const QString& portName);
    int numPorts() const { return portComboBox->count(); }
    int currentPortIndex() const { return portComboBox->currentIndex(); }

    QStringList getPinnedWaveNames() const { return waveformPlot->getPinnedWaveNames(); }
    void setPinnedWaveforms(const QStringList& pinnedWaveNames) { waveformPlot->setPinnedWaveforms(pinnedWaveNames); }
    bool arePinnedShown() const { return pinnedShown; }
    void setShowPinnedWaveforms(bool show);

    void enableSelectedWaveforms(bool enable) { waveformPlot->enableSelectedWaveforms(enable); }

    void hideColumn();
    void showColumn();

    void updateForRun();
    void updateForStop();

    inline ScrollBarState getScrollBarState() const { return waveformPlot->getScrollBarState(); }
    inline void restoreScrollBarState(const ScrollBarState& state) { waveformPlot->restoreScrollBarState(state); }

    void updatePortSelectionBox(bool switchToFirstPort = false);

    QString getColumnSettingsString() const;
    void restoreFromSettingsString(const QString& settings);

public slots:
    void showPinnedWaveformsSlot();

private slots:
    void showColumnSlot();
    void hideColumnSlot();
    void addColumn();
    void deleteColumn();
    void moveColumnLeft();
    void moveColumnRight();

private:
    WaveformDisplayColumn(const WaveformDisplayColumn&);  // Copying not allowed.
    WaveformDisplayColumn& operator=(const WaveformDisplayColumn&);  // Copying not allowed.

    MultiColumnDisplay* parent;
    int columnIndex;
    ControllerInterface* controllerInterface;
    SystemState* state;
    bool visible;
    bool pinnedShown;
    bool deleteButtonEnabled;

    MultiWaveformPlot* waveformPlot;

    QComboBox* portComboBox;

    QToolButton* hideColumnButton;
    QToolButton* showColumnButton;
    QToolButton* moveLeftButton;
    QToolButton* moveRightButton;
    QToolButton* addColumnButton;
    QToolButton* deleteColumnButton;
    QToolButton* pinWaveformButton;
    QToolButton* lessSpacingButton;
    QToolButton* moreSpacingButton;

    QCheckBox* showPinnedCheckBox;

    QSpacerItem* verticalSpacer;
};

#endif // WAVEFORMDISPLAYCOLUMN_H
