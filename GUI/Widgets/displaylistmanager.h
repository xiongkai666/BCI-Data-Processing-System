
#ifndef DISPLAYLISTMANAGER_H
#define DISPLAYLISTMANAGER_H

#include "systemstate.h"
#include "displayedwaveform.h"

using namespace std;

const int MaxNumWaveformsInGroup = 4;

struct WaveIndex {
    int index;
    bool inPinned;
};

class DisplayListManager
{
public:
    DisplayListManager(QList<DisplayedWaveform>& displayList_, QList<DisplayedWaveform>& pinnedList_, SystemState* state_);

    void populateDisplayList(const QStringList& displayWaveforms, const QStringList& auxInputWaveforms,
                             const QStringList& supplyVoltageWaveforms, const QStringList& baseWaveforms);
    void addPinnedWaveform(const QString& waveName);
    void pinSelectedWaveforms();
    void unpinSelectedWaveforms();
    void unpinAllWaveforms();
    bool groupSelectedWaveforms(bool group, int numFiltersDisplayed, bool arrangeByFilter);
    bool selectedWaveformsCanBeGrouped(int numFiltersDisplayed, bool arrangeByFilter) const;
    bool selectedWaveformsCanBeUngrouped() const;
    int findSelectedWaveform(const QList<DisplayedWaveform>& list, int y) const;

    DisplayedWaveform* displayedWaveform(WaveIndex waveIndex);
    DisplayedWaveform* displayedWaveform(int index, bool inPinned);

    int numDisplayedWaveforms(bool inPinned = false) const;
    int numSelectedWaveforms(bool inPinned = false) const;
    int numSelectedAmplifierChannels(int numFiltersDisplayed, bool arrangeByFilter) const;
    int numSelectedVisibleAmplifierChannels(int numFiltersDisplayed, bool arrangeByFilter) const;
    int sectionIDOfSelectedWaveforms() const;
    bool selectedWaveformsAreAmplifiers() const;

    void enableSelectedWaveforms(bool enable);
    void toggleSelectedWaveforms();

    bool isValidDragTarget(WaveIndex target, int numFiltersDisplayed, bool arrangeByFilter) const;

    bool moveSelectedWaveforms(QList<DisplayedWaveform> &list, int position);
    bool moveSelectedWaveformsArrangedByFilter(QList<DisplayedWaveform> &list, int position, int numFilters);
    int numWaveformsInFirstSection(const QList<DisplayedWaveform> &list) const;

    int calculateYCoords(QList<DisplayedWaveform>& list, int y, int labelHeight, double zoomFactor, int& minSpacing);
    void addYOffset(QList<DisplayedWaveform>& list, int yOffset);

    void selectSingleWaveform(WaveIndex waveIndex);
    void selectAdjacentWaveforms(WaveIndex waveIndex, int sectionExtent = -1);
    void selectNonAdjacentWaveforms(WaveIndex waveIndex, int numFiltersDisplayed, bool arrangeByFilter);
    bool selectNextWaveform() { return selectNextOrPreviousWaveform(true); }
    bool selectPreviousWaveform() { return selectNextOrPreviousWaveform(false); }

    vector<bool> selectionRecord() const;
    bool selectionRecordsAreEqual(const vector<bool>& a, const vector<bool>& b) const;

    // These functions update the system state intelligently, and automatically trigger a state change if anything changed.
    void updateOrderInState(const QString& portName, int numFiltersDisplayed, bool arrangeByFilter);

private:
    QList<DisplayedWaveform>& displayList;
    QList<DisplayedWaveform>& pinnedList;
    SystemState* state;

    void cleanUpDisplayList();

    DisplayedWaveform displayedWaveformFromName(const QString& waveName) const;
    DisplayedWaveform waveformDivider() const { return DisplayedWaveform("", WaveformDivider, nullptr); }

    bool selectedWaveformsAreEnabled() const;

    // Must manually trigger a state change after calling these functions.
    void deselectAllWaveforms();
    void selectWaveform(const QString& waveName, bool select = true);
    bool selectNextOrPreviousWaveform(bool selectNext);
};

#endif // DISPLAYLISTMANAGER_H
